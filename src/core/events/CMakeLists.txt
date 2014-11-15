set(gc_events_src
   type/CorePreInitEvent.cc
   type/KeyEvent.cc
   type/MouseMoveEvent.cc
   type/MouseMoveEvent.cc
   type/PreExtensionLoadEvent.cc
   type/NativeExtensionLoadedEvent.cc
   type/NativeExtensionsLoadedEvent.cc
   type/PreSubsystemCreateEvent.cc
   type/SubsystemCreatedEvent.cc

   EventBus.cc
)

add_library(gc_events STATIC ${gc_events_src})