#include <chrono>
#include <fstream>
#include <cstring>

#include <tclap/CmdLine.h>

#include <zlib.h>
#include <png.h>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/version.hpp>

#include "GloveConfig.h"

#include "glove/GloveCore.hpp"
#include "glove/GloveEnvironment.hpp"
#include "glove/GloveException.hpp"
#include "glove/events/EventBus.hpp"
#include "glove/input/InputManager.hpp"
#include "glove/events/type/CorePreInitEvent.hpp"
#include "glove/rendering/IRenderer.hpp"
#include "glove/utils/RuntimePathInfo.hpp"
#include "glove/natex/IExtensionSearcher.hpp"
#include "glove/natex/ISubsystemDefinition.hpp"
#include "glove/natex/ISubsystemFactory.hpp"
#include "glove/natex/DirectoryExtensionSearcher.hpp"
#include "glove/natex/GloveSubsystemDefinitionRegistry.hpp"
#include "glove/events/type/PreExtensionLoadEvent.hpp"
#include "glove/events/type/NativeExtensionLoadedEvent.hpp"
#include "glove/events/type/NativeExtensionsLoadedEvent.hpp"
#include "glove/events/type/PreSubsystemCreateEvent.hpp"
#include "glove/events/type/SubsystemCreatedEvent.hpp"
#include "glove/natex/GloveSubsystemInstanceRegistry.hpp"

namespace sc = std::chrono;

namespace glove {

GloveCore::GloveCore(int argc, const char** argv) : frameCounter(0), exitRequested(false) {
    auto constructionStartTime = sc::steady_clock::now();

    LOG(logger, info, (boost::format("Creating GloveCore version %1%") % GLOVE_VERSION_STRING).str());

    gEnv = std::make_shared<GloveEnvironment>();

    GetExecutionPathInfo(gEnv->executablePath, gEnv->executableName);
    LOG(logger, info, "Running from " << gEnv->executablePath);

    LOG(logger, info, "Using ZLIB " << ZLIB_VERSION);
    LOG(logger, info, "Using libPng " << PNG_LIBPNG_VER_STRING);
    LOG(logger, info, "Using Boost " << (BOOST_VERSION / 100000) << "." << ((BOOST_VERSION / 100) % 1000) << "." << (BOOST_VERSION % 100));

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
                                             gEnv->MakeDataPath("data/glove.yaml"), "path", cmd);
            SwitchArg skipNatexLoading("", "no-natex", "Skip native extension loading", cmd);
            cmd.parse(argc, argv);

            // Load configuration
            LoadConfiguration(configFile.getValue());

            Configuration& engineConfig = gEnv->engineConfiguration;

            if (skipNatexLoading.isSet()) {
                engineConfig.engine.loadNativeExtensions = false;
            }
        } catch (ArgException& ex) {
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

void GloveCore::Init(int argc, const char** argv) {
    initializationTime = sc::steady_clock::now();

    CorePreInitEvent preInitEvent;
    eventBus->Publish(preInitEvent);

    Configuration& config = gEnv->engineConfiguration;

    if (config.engine.loadNativeExtensions) {
        ISubsystemDefinitionRegistryPtr subsystemDefinitionRegistry =
                std::make_shared<GloveSubsystemDefinitionRegistry>();

        try {
            DirectoryExtensionSearcher extensionSearcher("data/natex");

            for (auto extension : extensionSearcher.GetExtensions()) {
                try {
                    PreExtensionLoadEvent preloadEvent;
                    eventBus->Publish(preloadEvent);

                    ISystemExtensionPtr systemExtension = bifrostLoader.LoadSystemExtension(extension);
                    systemExtension->RegisterSubsystems(subsystemDefinitionRegistry);

                    NativeExtensionLoadedEvent postloadEvent;
                    eventBus->Publish(postloadEvent);
                } catch (GloveException& ex) {
                    LOG(logger, error, ex.what());
                }
            }
        } catch (GloveException& ex) {
            LOG(logger, error, (boost::format("Failed to load native extensions: %1%") % ex.what()).str());
        }

        {
            NativeExtensionsLoadedEvent allExtensionsLoadedEvent;
            eventBus->Publish(allExtensionsLoadedEvent);
        }

        subsystemInstanceRegistry = std::make_shared<GloveSubsystemInstanceRegistry>(eventBus, shared_from_this());
        subsystemInstanceRegistry->InstantiateDefinitionRegistry(subsystemDefinitionRegistry);
    }

    try {
        inputManager = InputManagerPtr(new InputManager(eventBus));

        TimePoint initializationDone = sc::steady_clock::now();
        auto timeSpan = sc::duration_cast<std::chrono::milliseconds>(initializationDone - initializationTime);
        LOG(logger, info, "Engine initialization took " << timeSpan.count() << "ms");
    } catch (const GloveException& ex) {
        LOG(logger, error, (boost::format("Engine initialization failed: %1%") % ex.what()).str());
    }
}

void GloveCore::EnterMainLoop(ScenegraphHandle scenegraph) {
    TimePoint start = std::chrono::steady_clock::now();
    TimePoint end = std::chrono::steady_clock::now();

    while (!IsExitRequested()) {
        end = std::chrono::steady_clock::now();
        lastFrameTime = sc::duration_cast<std::chrono::duration<double>>(end - start);
        start = std::chrono::steady_clock::now();

        frameData.frameId++;
        frameData.deltaTime = lastFrameTime.count();

        Update();
//        Render(scenegraph);
    }
}

void GloveCore::Update() {
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

//    primaryScenegraph->IterateGameObjects([&](GameObjectPtr gameObject) {
//        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
//            gameComponent->SyncEarlyUpdate();
//        });
//
//        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
//            try {
//                gameComponent->SyncUpdate();
//            } catch (boost::python::error_already_set) {
//                //                pythonEngine->HandleError();
//            }
//        });
//
//        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
//            gameComponent->AsyncUpdate();
//        });
//
//        gameObject->IterateComponents([&](const GameComponentPtr& gameComponent) {
//            gameComponent->SyncLateUpdate();
//        });
//    });

    inputManager->SyncUpdate();
}

//void GloveCore::Render(ScenegraphPointer scenegraph) {
    //    renderer->ClearBuffers();
    //    renderer->RenderScene(scenegraph, frameData);
    //    renderer->SwapBuffers();
//}

void GloveCore::LoadConfiguration(const std::string& configPath) {
    Configuration& engineConfig = gEnv->engineConfiguration;
    engineConfig.LoadDefaults();

    if (!boost::filesystem::exists(configPath)) {
        engineConfig.SaveToFile(configPath);
        return;
    }

    try {
        engineConfig.LoadFromFile(configPath);
    } catch (GloveException& ex) {
        LOG(logger, error, (boost::format("Failed to load glove.yaml: \n%1%") % ex.what()).str());
    }
}
} /* namespace glove */
