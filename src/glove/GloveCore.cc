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

GloveCore::GloveCore(const Configuration& engineConfig, const EventBusPtr& eventBus,
                     const InputManagerPtr& inputManager,
                     const ISubsystemInstanceRegistryPtr& subsystemInstanceRegistry,
                     const ISystemExtensionLoaderHandle& systemExtensionLoader)
    : engineConfiguration(engineConfig), eventBus(eventBus), inputManager(inputManager),
      subsystemInstanceRegistry(subsystemInstanceRegistry), systemExtensionLoader(systemExtensionLoader) {
    LOG(logger, info, (boost::format("Creating GloveCore version %1%") % GLOVE_VERSION_STRING).str());

    LOG(logger, info, "Using ZLIB " << ZLIB_VERSION);
    LOG(logger, info, "Using libPng " << PNG_LIBPNG_VER_STRING);
    LOG(logger, info, "Using Boost " << (BOOST_VERSION / 100000) << "." << ((BOOST_VERSION / 100) % 1000) << "."
                                     << (BOOST_VERSION % 100));
}
//
// void GloveCore::EnterMainLoop(ScenegraphHandle scenegraph) {
//    TimePoint start = std::chrono::steady_clock::now();
//    TimePoint end = std::chrono::steady_clock::now();
//
//    while (!IsExitRequested()) {
//        end = std::chrono::steady_clock::now();
//        lastFrameTime = sc::duration_cast<std::chrono::duration<double>>(end - start);
//        start = std::chrono::steady_clock::now();
//
//        frameData.frameId++;
//        frameData.deltaTime = lastFrameTime.count();
//
//        Update();
//        //        Render(scenegraph);
//    }
//}

//void GloveCore::Update() {
    //    if (inputManager->IsKeyPressed(KC_F6)) {
    //        LOG(logger, info, (boost::format("Last Update Time: %1%ms") %
    //                           std::chrono::duration_cast<std::chrono::milliseconds>(lastFrameTime).count()).str());
    //    }
    //
    //    if (inputManager->IsKeyPressed(KC_F7)) {
    //        LOG(logger, info, (boost::format("Shift: %1%\nAlt: %2%\nControl: %3%\nX: %4%\nY: %5%") %
    //                           inputManager->IsKeyDown(KC_LEFT_SHIFT) % inputManager->IsKeyDown(KC_LEFT_ALT) %
    //                           inputManager->IsKeyDown(KC_LEFT_CONTROL) % inputManager->GetMousePositionRef().x %
    //                           inputManager->GetMousePositionRef().y).str());
    //    }

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

    //    inputManager->SyncUpdate();
//}

// void GloveCore::Render(ScenegraphPointer scenegraph) {
//    renderer->ClearBuffers();
//    renderer->RenderScene(scenegraph, frameData);
//    renderer->SwapBuffers();
//}

} /* namespace glove */
