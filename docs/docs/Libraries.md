# Libraries


## gc_loaders_so

Shared library loader implementation for UNIX based systems (.so files). Only built when cmake detects a UINX OS.

**Directory:** core/internal/so<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** dl (libdl)


## gc_rendering

Rendering stuff. Meant to be used by rendering modules.

**Directory:** core/rendering<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** none


## gc_natex

Everything related to native extensions.

**Directory:** core/natex<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** none


## gc_events

Eventbus and event types.

**Directory:** core/events<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** none

## gc_input

Inputsystem.

**Directory:** core/input<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** gc_events


## gc_log

Logging.

**Directory:** core/log<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** none


## gc_graph

Scenegraph.

**Directory:** core/grpah<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** none


## gc_pitamem

Memory management and tracking.

**Directory:** core/pitamem<br/>
**Linkage:** linked into glove_core library<br/>
**Dependencies:** none