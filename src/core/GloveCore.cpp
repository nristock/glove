#include "GloveCore.h"

#include <chrono>
#include <fstream>
#include <cstring>

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#elif defined(__unix__) || defined(__unix)

#include <unistd.h>
#include <cstdlib>

#endif

#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include <core/GloveEnvironment.h>
#include <core/GloveException.h>
#include <pitamem/MemoryProfile.h>
#include "graph/Scenegraph.h"
#include "graph/GameObject.h"
#include "graph/GameComponent.h"
#include "rendering/opengl/GLRenderer.h"
#include "core/GpuBufferManager.h"
#include "core/PluginLoader.h"
#include "scripting/GlovePythonEngine.h"
#include "shader/pyshed/PyShedLoader.h"
#include "event/EventBus.h"
#include "input/InputManager.h"
#include "pitamem/MemoryProfiler.h"

namespace sc = std::chrono;

namespace glove {
	
GloveCore::GloveCore() :
          frameCounter(0),
          exitRequested(false),
          EnableProfilable() {
    gEnv = std::make_shared<GloveEnvironment>();

    frameData.frameId = 0;
    frameData.viewProjectionMatrix = glm::mat4();
    frameData.deltaTime = 0;

#if defined(_WIN32) || defined(WIN32)
	int bufferSize = 4096;
	char* moduleName = reinterpret_cast<char*>(std::malloc(sizeof(char) * bufferSize));
	GetModuleFileName(NULL, moduleName, bufferSize);

	while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		std::free(moduleName);
		bufferSize += 64;
		moduleName = reinterpret_cast<char*>(std::malloc(sizeof(wchar_t) * bufferSize));

		GetModuleFileName(NULL, moduleName, bufferSize);
	}

	executableName = moduleName;
	std::free(moduleName);
#elif defined(__unix__) || defined(__unix)
    std::size_t bufferSize = 1024;
    char* linkName = new char[bufferSize];
    ssize_t charsWritten = readlink("/proc/self/exe", linkName, bufferSize);

    while (charsWritten == bufferSize) {
        delete[] linkName;
        bufferSize += 64;
        linkName = new char[bufferSize];
        charsWritten = readlink("/proc/self/exe", linkName, bufferSize);
    }

    linkName[charsWritten] = '\0';

    executableName = linkName;
    delete[]linkName;
#endif
    executablePath = executableName.substr(0, executableName.find_last_of("\\/"));

    gEnv->executablePath = executablePath;

    LOG(logger, info, "Running from " << executablePath);
    LOG(logger, info, "GloveCore created");
}

GloveCore::~GloveCore() {
}

void GloveCore::Init(int argc, char** argv) {
    initializationTime = sc::steady_clock::now();

    namespace bpo = boost::program_options;
    try {
        bool initRenderingSystem = true;
        bool initScripting = true;
        int windowWidth = 800;
        int windowHeight = 600;

        bpo::options_description coreOptions("Core Options");
        coreOptions.add_options()
                           ("help", "prints help message")
                           ("init-rendering", bpo::value<bool>(&initRenderingSystem)->default_value(true), "initialize rendering system")
                           ("init-scripting", bpo::value<bool>(&initScripting)->default_value(true), "initialize scripting system")
                           ("window-width,w", bpo::value<int>(&windowWidth)->default_value(800), "main window's width")
                           ("window-height,h", bpo::value<int>(&windowHeight)->default_value(600), "main window's height")
                           ("opengl-version-major", bpo::value<int>()->default_value(3), "OpenGL major version to request")
                           ("opengl-version-minor", bpo::value<int>()->default_value(3), "OpenGL minor version to request");

        bpo::options_description commandLineOptions;
        commandLineOptions.add(coreOptions);

        std::ifstream settingsFile("glove.cfg");

        bpo::store(bpo::parse_command_line(argc, argv, commandLineOptions), parsedArguments);
        bpo::store(bpo::parse_config_file(settingsFile, commandLineOptions), parsedArguments);
        bpo::notify(parsedArguments);
		
        eventBus = EventBusPtr(new EventBus());

        if (initRenderingSystem) {
            InitializeRenderingSystem(800, 600);
            primaryScenegraph = ScenegraphPtr(new Scenegraph());

            inputManager = InputManagerPtr(new InputManager());
            eventBus->Subscribe(inputManager);
        }

        if (initScripting) {
            InitializeScripting();
            InitializeResourceLoaders();
        }

        TimePoint initializationDone = sc::steady_clock::now();
        auto timeSpan = sc::duration_cast<std::chrono::milliseconds>(initializationDone - initializationTime);
        LOG(logger, info, "Engine initialization took " << timeSpan.count() << "ms");
    }
    catch (const GloveException& ex) {
        LOG(logger, error, (boost::format("Engine initialization failed: %1%") % ex.what()).str());
    }

}

void GloveCore::InitializeRenderingSystem(int windowWidth, int windowHeight) {
    renderer = RendererPtr(new GLRenderer(eventBus));

    try {
        renderer->Init();
        renderer->CreateRenderWindow(windowWidth, windowHeight, parsedArguments["opengl-version-major"].as<int>(), parsedArguments["opengl-version-minor"].as<int>());
    }
    catch (const GloveException& e) {
        LOG(logger, error, "Exception while initializing rendering subsystem:" << std::endl << e.what());
    }

    gpuBufferManager = GpuBufferManagerPtr(new GpuBufferManager());
}

void GloveCore::InitializeScripting() {
    pythonEngine = GlovePythonEnginePtr(new GlovePythonEngine(executablePath));

    try {
        namespace bpy = boost::python;
        bpy::object mainNs = pythonEngine->GetBuiltins();

        mainNs["g_Core"] = bpy::object(shared_from_this());
        mainNs["g_Scenegraph"] = bpy::object(primaryScenegraph);
    }
    catch (boost::python::error_already_set const&) {
        pythonEngine->HandleError();

        throw GLOVE_EXCEPTION("Failed to expose global scripting objects");
    }
}

void GloveCore::InitializeResourceLoaders() {
    pyshedLoader = PyShedLoaderPtr(new PyShedLoader(pythonEngine));
    pluginLoader = PluginLoaderPtr(new PluginLoader(pythonEngine));

    pluginLoader->DiscoverPlugins();
    pluginLoader->LoadPlugins();
}

void GloveCore::EnterMainLoop() {
    TimePoint start = std::chrono::steady_clock::now();
    TimePoint end = std::chrono::steady_clock::now();

    while (!IsExitRequested()) {
        end = std::chrono::steady_clock::now();
        lastFrameTime = sc::duration_cast<std::chrono::duration<double>>(end - start);
        start = std::chrono::steady_clock::now();

        frameData.frameId++;
        frameData.deltaTime = lastFrameTime.count();

        Update();
        Render(primaryScenegraph);
    }
}

void GloveCore::Update() {
    renderer->PollSystemEvents();

    if (inputManager->IsKeyPressed(KC_F5)) {
        std::stringstream memoryDump;
        memoryDump << (boost::format("[GLOVE HEAP (P: %1%B, U: %2%B, O: %3%)]\n\n")
                % MemoryProfiler::GetProfilerInstance()->GetPeakMemoryUsage()
                % MemoryProfiler::GetProfilerInstance()->GetCurrentMemoryUsage()
                % MemoryProfiler::GetProfilerInstance()->GetRegisteredObjectCount()
        ).str();

        MemoryProfiler::GetProfilerInstance()->IterateRegisteredObjects([&](MemoryProfile* profilable) {
            memoryDump << (boost::format("[%1%]\n @+%2% : %3%\n")
                    % profilable->GetTypeName()
                    % profilable->GetMemoryRoot()
                    % profilable->GetSizeInBytes()
            ).str();

            auto siblingIter = profilable->GetSiblings();
            while (!siblingIter.IsEnd()) {
                memoryDump << (boost::format("|--[%1%]: %2%\n")
                        % (*siblingIter)->GetTypeName()
                        % (*siblingIter)->GetSizeInBytes()
                ).str();
                ++siblingIter;
            }

            memoryDump << "\n";
        });

        LOG(logger, info, memoryDump.str());
    }

    if (inputManager->IsKeyPressed(KC_F6)) {
        LOG(logger, info, (boost::format("Last Update Time: %1%ms") % std::chrono::duration_cast<std::chrono::milliseconds>(lastFrameTime).count()).str());
    }

    if (inputManager->IsKeyPressed(KC_F7)) {
        LOG(logger, info, (boost::format("Shift: %1%\nAlt: %2%\nControl: %3%\nX: %4%\nY: %5%") % inputManager->IsKeyDown(KC_LEFT_SHIFT) % inputManager->IsKeyDown(KC_LEFT_ALT) % inputManager->IsKeyDown(KC_LEFT_CONTROL) % inputManager->GetMousePositionRef().x % inputManager->GetMousePositionRef().y).str());
    }

    primaryScenegraph->IterateGameObjects([&](GameObjectPtr gameObject) {
        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
            gameComponent->SyncEarlyUpdate();
        });

        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
            try {
                gameComponent->SyncUpdate();
            } catch (boost::python::error_already_set) {
                pythonEngine->HandleError();
            }
        });

        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
            gameComponent->AsyncUpdate();
        });

        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
            gameComponent->SyncLateUpdate();
        });
    });

    inputManager->SyncUpdate();
}

void GloveCore::Render(ScenegraphPointer scenegraph) {
    renderer->ClearBuffers();
    renderer->RenderScene(scenegraph, frameData);
    renderer->SwapBuffers();
}

} /* namespace glove */
