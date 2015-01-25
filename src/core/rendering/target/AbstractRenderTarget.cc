#include "AbstractRenderTarget.h"

namespace glove {

void AbstractRenderTarget::AddDependency(const RenderTargetHandle& dependency) {
    dependencies.push_back(dependency);
}

std::list<std::weak_ptr<IRenderTarget>> AbstractRenderTarget::GetDependencies() {
    return dependencies;
}
}