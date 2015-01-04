#pragma once

#include <memory>

namespace glove {

class GameObject;
class IGameObjectFactory;
class GameComponent;
class IGameComponentFactory;
class GraphNode;
class Scenegraph;

typedef std::shared_ptr<GameObject> GameObjectHandle;
typedef std::weak_ptr<GameObject> WeakGameObjectHandle;
typedef std::shared_ptr<IGameObjectFactory> GameObjectFactoryHandle;
typedef std::shared_ptr<GameComponent> SharedGameComponentHandle;
typedef std::weak_ptr<GameComponent> GameComponentHandle;
typedef std::shared_ptr<IGameComponentFactory> GameComponentFactoryHandle;
typedef std::shared_ptr<GraphNode> GraphNodeHandle;
typedef std::shared_ptr<Scenegraph> ScenegraphHandle;

namespace GameComponents {
class CameraBase;
class MeshRenderer;
}

typedef std::shared_ptr<GameComponents::CameraBase> CameraBaseHandle;
typedef std::shared_ptr<GameComponents::MeshRenderer> MeshRendererHandle;
}