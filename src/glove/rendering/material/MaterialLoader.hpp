#pragma once

#include <future>

#include <glove/rendering/Material.hpp>
#include <glove/threading/TaskQueue.hpp>
#include <glove/threading/ThreadPool.hpp>
#include <glove/utils/StringId.hpp>
#include "glove/BlueDwarfApi.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {

class RenderResourceFactory;

struct BD_API_EXPORT MaterialLoadTask : public Task {
  public:
    MaterialLoadTask(StringId materialName, Handle<RenderResourceFactory> resourceFactory) : materialName(materialName), resourceFactory(resourceFactory) {}
    virtual void Execute();

    Material::Handle GetMaterial() const { return material; }

  private:
    StringId materialName;
    Handle<RenderResourceFactory> resourceFactory;
    Material::Handle material;
};

struct BD_API_EXPORT MaterialFuture {
  public:
    MaterialFuture(Handle<MaterialLoadTask> loadTask, Handle<PoolTask> poolTask) : loaderTask(loadTask), poolTask(poolTask) {}
    Material::Handle GetMaterial() {
        poolTask->AwaitCompletion();
        return loaderTask->GetMaterial();
    }

  private:
    Handle<MaterialLoadTask> loaderTask;
    Handle<PoolTask> poolTask;
};

// TODO: This class is currently just a mock which creates a simple position/uv material + shaders
class BD_API_EXPORT MaterialLoader {
  public:
    virtual ~MaterialLoader() = default;

     MaterialFuture Load(StringId materialName, Handle<RenderResourceFactory> resourceFactory);

  private:
    Logger logger{"MaterialLoader"};
};

} /* namespace BlueDwarf */