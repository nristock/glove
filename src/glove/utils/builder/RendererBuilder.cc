#include "glove/utils/builder/RendererBuilder.hpp"
#include "glove/GloveCore.hpp"
#include "glove/rendering/WindowConstructionHints.hpp"
#include "glove/rendering/IRenderSubsystem.hpp"
#include "glove/rendering/factories/IRendererFactory.hpp"

namespace glove {

RendererBuilder::RendererBuilder(const GloveCorePtr& core) : RendererBuilder(core->GetUniqueSubsystem<IRenderSubsystem>(), core->GetConfig()) {

}

RendererBuilder::RendererBuilder(const IRenderSubsystemPtr& renderSubsystem)
    : windowTitle("Glove Engine"), windowSize(800, 600), windowPosition(0, 0), renderSubsystem(renderSubsystem) {
}

RendererBuilder::RendererBuilder(const IRenderSubsystemPtr& renderSubsystem, const Configuration& configuration)
    : windowTitle("Glove Engine"),
      windowSize(configuration.rendering.window.width, configuration.rendering.window.height), windowPosition(0, 0),
      renderSubsystem(renderSubsystem) {
}

RendererBuilder& RendererBuilder::SetWindowTitle(const std::string& title) {
    windowTitle = title;
    return *this;
}

RendererBuilder& RendererBuilder::SetWindowSize(const ScreenDimensions& size) {
    windowSize = size;
    return *this;
}

RendererBuilder& RendererBuilder::SetWindowSize(int width, int height) {
    windowSize = ScreenDimensions(width, height);
    return *this;
}

RendererBuilder& RendererBuilder::SetWindowPosition(const ScreenPoint& screenPoint) {
    windowPosition = screenPoint;
    return *this;
}

RendererBuilder& RendererBuilder::SetWindowPosition(int x, int y) {
    windowPosition = ScreenPoint(x, y);
    return *this;
}

IRendererPtr RendererBuilder::Finalize() {
    WindowConstructionHints constructionHints(windowPosition, windowSize, windowTitle);
    return renderSubsystem->GetRendererFactory()->CreateRenderer(constructionHints);
}
}