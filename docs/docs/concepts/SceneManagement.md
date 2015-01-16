# Scene Management

## Scenegraph

### GameObject vs. GraphNode
A GraphNode is class providing hierarchical business logic (e.g. adding/removing children, parenting). Every graph node 
has a transform which holds the node's location, scale and rotation in parent-local space as well as transformation 
matrices for parent-local and global space.<br>
A GameObject is a GraphNode and also provides GameComponent hosting functionality (e.g. adding/removing/querying 
components).

A scene graph operates on GameObjectS since that's the most common use case and thus reduces the number of dynamic casts
required to access a specific GameObject's components.

### Abstract
The scene graph is responsible for hosting all GameObjects in a scene. It is a container/proxy-factory hybrid and thus 
**not** responsible for actually managing a GameObject's update/render cycle.

### Structure and Object Storage
While the structure of any scene graph is hierarchical the actual object container implementation is arbitrary. This
means that a scene graph implementation is allowed to only store the graph root object and traverse the tree when 
processing search and iteration requests. This does also imply that the order of node iteration can be arbitrary.
Another graph implementation might store all objects in a one dimensional array. - So different implementations
come with different trade-offs.

### Object Creation
The scene graph implementation must expose methods to create GameObjects using a GameObjectFactory. Those creation 
methods must furthermore provide pre-init and post-init callbacks to allow the user to modify the GameObject being 
created before || after it has been created.

### Graph Iteration
Methods accepting a function object and an optional predicate must exist. The order of iteration can be completely 
arbitrary. The iteration methods apply the provided function object to all graph nodes selected by the provided predicate.
An empty (i.e. not provided/default) predicate will select all graph nodes.

## Update/Render Cycle

### Abstract (Update Cycle)
A GameObject can host zero or more GameComponents. Each GameComponent can be updated || rendered at least once a frame. 
Since the Glove Engine puts very strong emphasis on asynchronous processing the order in which GameComponents are 
updated cannot be guaranteed. The GameComponent interface does however provide frame callbacks which impose certain 
happens-before or happens-after constraints. For example SyncUpdate is guaranteed to be called after all SyncEarlyUpdateS
happened. AsyncUpdate on the other hand is not constrained at all. It's even possible that a single component's 
AsyncUpdate is called multiple times per frame.

### Abstract (Render Cycle)
Since Glove is designed to work in an asynchronous manner and the primary render implementation (which is OpenGL) is
not particularly optimized for multi-threaded rendering the render system is single-threaded.
<br>
GameComponentS have a QueueRenderOperation whose parameter is the current rendering queue. When the renderer renders a
scene it first iterates all GameComponentS to populate the queue with RenderOperations. A render operation (called ROp 
from here on) describes what and how something should be rendered. Once a ROp has been queued the rendering thread 
technically owns the ROp and deletes it once it has been processed (it is possible to prevent deletion/deallocation to
allow reusing the same ROp). (**Not implemented warning**) The order in which ROps are processed depends on their 
individual priority. ROps within the same priority class are processed in an arbitrary order.

### Camera Components
A camera is somewhat special. It provides the rendering subsystem with information on how to draw things onto the 
viewport.<br>
The rendering subsystem allows to register one or more camera components and associate render targets with them. A ROp
will be executed for all registered cameras.
//TODO: Layers