#include "GloveCore.h"

#include <chrono>
#include <fstream>
#include <cstring>

#include <tclap/CmdLine.h>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include <core/GloveEnvironment.h>
#include <core/GloveException.h>
#include <pitamem/MemoryProfile.h>
#include "graph/Scenegraph.h"
#include "graph/GameObject.h"
#include "graph/GameComponent.h"
#include "core/PluginLoader.h"
#include "scripting/GlovePythonEngine.h"
#include "shader/pyshed/PyShedLoader.h"
#include <core/events/EventBus.h>
#include "input/InputManager.h"
#include "pitamem/MemoryProfiler.h"
#include <core/events/type/CorePreInitEvent.h>
#include <core/rendering/IRenderer.h>

#include "GloveConfig.h"

#include <utils/RuntimePathInfo.h>

#include <vendor/json/json.h>
#include <core/natex/IExtensionSearcher.h>
#include <core/natex/ISubsystemDefinition.h>
#include <core/natex/ISubsystemFactory.h>
#include <core/natex/DirectoryExtensionSearcher.h>
#include <core/natex/GloveSubsystemDefinitionRegistry.h>
#include <core/events/type/PreExtensionLoadEvent.h>
#include <core/events/type/NativeExtensionLoadedEvent.h>
#include <core/events/type/NativeExtensionsLoadedEvent.h>
#include <core/events/type/PreSubsystemCreateEvent.h>
#include <core/events/type/SubsystemCreatedEvent.h>
#include <core/natex/GloveSubsystemInstanceRegistry.h>

namespace sc = std::chrono;

namespace glove {

GloveCore::GloveCore(int argc, const char** argv) : frameCounter(0), exitRequested(false), EnableProfilable() {
    auto constructionStartTime = sc::steady_clock::now();

    LOG(logger, info, (boost::format("Creating GloveCore version %1%") % GLOVE_VERSION_STRING).str());

    gEnv = std::make_shared<GloveEnvironment>();

    GetExecutionPathInfo(gEnv->executablePath, gEnv->executableName);
    LOG(logger, info, "Running from " << gEnv->executablePath);

    // Command line arguments
    {
        using namespace TCLAP;

        try {
            CmdLine cmd("Glove Engine", ' ', GLOVE_VERSION_STRING);

            ValueArg<int> windowWidth("", "window-width", "Main window's width", false, 800, "int", cmd);
            ValueArg<int> windowHeight("", "window-height", "Main window's height", false, 600, "int", cmd);
            ValueArg<int> openGlVersionMajor("", "opengl-version-major", "OpenGL major version to request", false, 3,
                                             "int", cmd);
            ValueArg<int> openGlVersionMinor("", "opengl-version-minor", "OpenGL minor version to request", false, 3,
                                             "int", cmd);
            ValueArg<std::string> configFile("c", "config", "Path to engine configuration", false,
                                             gEnv->MakeDataPath("data/glove.json"), "path", cmd);
            ValueArg<bool> initRendering("", "init-rendering", "Init rendering system", false, true, "true/false", cmd);
            ValueArg<bool> initScripting("", "init-scripting", "Init scripting system", false, true, "true/false", cmd);
            cmd.parse(argc, argv);

            // Load configuration
            LoadConfiguration(configFile.getValue());

            Configuration& engineConfig = gEnv->engineConfiguration;

            if (!initRendering.getValue()) {
                auto iter = std::find(engineConfig.engine.subsystemInitList.begin(),
                                      engineConfig.engine.subsystemInitList.end(), "rendering");

                if (iter != engineConfig.engine.subsystemInitList.end()) {
                    engineConfig.engine.subsystemInitList.erase(iter);
                }
            }
            if (!initScripting.getValue()) {
                auto iter = std::find(engineConfig.engine.subsystemInitList.begin(),
                                      engineConfig.engine.subsystemInitList.end(), "scripting");

                if (iter != engineConfig.engine.subsystemInitList.end()) {
                    engineConfig.engine.subsystemInitList.erase(iter);
                }
            }
        }
        catch (ArgException& ex) {
            // Failing to parse the command line is a recoverable error so don't bubble up the exception and continue as
            // usual
            LOG(logger, error, (boost::format("Failed to parse command line: %1%") % ex.error()).str());
        }
    }

    // Event bus
    { eventBus = std::make_shared<EventBus>(); }

    auto constructionEndTime = sc::steady_clock::now();

    LOG(logger, info, (boost::format("GloveCore created in %1%ms") %
                       sc::duration_cast<sc::milliseconds>(constructionEndTime - constructionStartTime).count()).str());
}

GloveCore::~GloveCore() {}

void GloveCore::Init(int argc, const char** argv) {
    initializationTime = sc::steady_clock::now();

    CorePreInitEvent preInitEvent;
    eventBus->Publish(preInitEvent);

    Configuration& config = gEnv->engineConfiguration;

    DirectoryExtensionSearcher extensionSearcher("data/natex");
    ISubsystemDefinitionRegistryPtr subsystemDefinitionRegistry = std::make_shared<GloveSubsystemDefinitionRegistry>();

    for (auto extension : extensionSearcher.GetExtensions()) {
        try {
            PreExtensionLoadEvent preloadEvent;
            eventBus->Publish(preloadEvent);

            ISystemExtensionPtr systemExtension = bifrostLoader.LoadSystemExtension(extension);
            systemExtension.lock()->RegisterSubsystems(subsystemDefinitionRegistry);

            NativeExtensionLoadedEvent postloadEvent;
            eventBus->Publish(postloadEvent);
        }
        catch (GloveException& ex) {
            LOG(logger, error, ex.what());
        }
    }

    {
        NativeExtensionsLoadedEvent allExtensionsLoadedEvent;
        eventBus->Publish(allExtensionsLoadedEvent);
    }

    ISubsystemInstanceRegistryPtr subsystemInstanceRegistry = std::make_shared<GloveSubsystemInstanceRegistry>(eventBus);
    subsystemInstanceRegistry->InstantiateDefinitionRegistry(subsystemDefinitionRegistry);

    try {
        Configuration& engineConfig = gEnv->engineConfiguration;

        auto subsystemInitListBegin = engineConfig.engine.subsystemInitList.begin();
        auto subsystemInitListEnd = engineConfig.engine.subsystemInitList.end();

        if (std::find(subsystemInitListBegin, subsystemInitListEnd, "rendering") != subsystemInitListEnd) {
            InitializeRenderingSystem(800, 600);
            primaryScenegraph = ScenegraphPtr(new Scenegraph());

            inputManager = InputManagerPtr(new InputManager(eventBus));
        }

        if (std::find(subsystemInitListBegin, subsystemInitListEnd, "scripting") != subsystemInitListEnd) {
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
    // renderer = RendererPtr(new GLRenderer(eventBus));

    try {
        renderer->Init();
        renderer->CreateRenderWindow(windowWidth, windowHeight, 3, 3);
    }
    catch (const GloveException& e) {
        LOG(logger, error, "Exception while initializing rendering subsystem:" << std::endl << e.what());
    }

    //    gpuBufferManager = GpuBufferManagerPtr(new GpuBufferManager());
}

void GloveCore::InitializeScripting() {
    pythonEngine = GlovePythonEnginePtr(new GlovePythonEngine(gEnv->executablePath));

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
        memoryDump << (boost::format("[GLOVE HEAP (P: %1%B, U: %2%B, O: %3%)]\n\n") %
                       MemoryProfiler::GetProfilerInstance()->GetPeakMemoryUsage() %
                       MemoryProfiler::GetProfilerInstance()->GetCurrentMemoryUsage() %
                       MemoryProfiler::GetProfilerInstance()->GetRegisteredObjectCount()).str();

        MemoryProfiler::GetProfilerInstance()->IterateRegisteredObjects([&](MemoryProfile* profilable) {
            memoryDump << (boost::format("[%1%]\n @+%2% : %3%\n") % profilable->GetTypeName() %
                           profilable->GetMemoryRoot() % profilable->GetSizeInBytes()).str();

            auto siblingIter = profilable->GetSiblings();
            while (!siblingIter.IsEnd()) {
                memoryDump << (boost::format("|--[%1%]: %2%\n") % (*siblingIter)->GetTypeName() %
                               (*siblingIter)->GetSizeInBytes()).str();
                ++siblingIter;
            }

            memoryDump << "\n";
        });

        LOG(logger, info, memoryDump.str());
    }

    if (inputManager->IsKeyPressed(KC_F6)) {
        LOG(logger, info, (boost::format("Last Update Time: %1%ms") %
                           std::chrono::duration_cast<std::chrono::milliseconds>(lastFrameTime).count()).str());
    }

    if (inputManager->IsKeyPressed(KC_F7)) {
        LOG(logger, info, (boost::format("Shift: %1%\nAlt: %2%\nControl: %3%\nX: %4%\nY: %5%") %
                           inputManager->IsKeyDown(KC_LEFT_SHIFT) % inputManager->IsKeyDown(KC_LEFT_ALT) %
                           inputManager->IsKeyDown(KC_LEFT_CONTROL) % inputManager->GetMousePositionRef().x %
                           inputManager->GetMousePositionRef().y).str());
    }

    primaryScenegraph->IterateGameObjects([&](GameObjectPtr gameObject) {
        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) { gameComponent->SyncEarlyUpdate(); });

        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
            try {
                gameComponent->SyncUpdate();
            }
            catch (boost::python::error_already_set) {
                pythonEngine->HandleError();
            }
        });

        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) { gameComponent->AsyncUpdate(); });

        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) { gameComponent->SyncLateUpdate(); });
    });

    inputManager->SyncUpdate();
}

void GloveCore::Render(ScenegraphPointer scenegraph) {
    renderer->ClearBuffers();
    renderer->RenderScene(scenegraph, frameData);
    renderer->SwapBuffers();
}

void GloveCore::LoadConfiguration(const std::string& configPath) {
    using namespace Json;

    Configuration& engineConfig = gEnv->engineConfiguration;
    engineConfig.LoadDefaults();

    if (!boost::filesystem::exists(configPath)) {
        engineConfig.SaveToFile(configPath);
        return;
    }

    try {
        engineConfig.LoadFromFile(configPath);
    }
    catch (GloveException& ex) {
        LOG(logger, error, (boost::format("Failed to load glove.json: \n%1%") % ex.what()).str());
    }
}
} /* namespace glove */
