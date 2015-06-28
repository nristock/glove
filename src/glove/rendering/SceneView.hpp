#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glove/BlueDwarfApi.hpp"
#include "glove/CommonTypes.hpp"
#include "glove/world/Transform.hpp"
#include "glove/rendering/RenderTarget.hpp"
#include "glove/rendering/Texture.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {
class SceneProxy;

/**
* A ViewRect is an immutable description of a SceneView's location and size in a SceneViewComposition.
*/
struct ViewRect {
    ViewRect(uint32 x, uint32 y, uint32 width, uint32 height) : x(x), y(y), width(width), height(height) {}

    uint32 GetX() const { return x; }
    uint32 GetY() const { return y; }
    uint32 GetWidth() const { return width; }
    uint32 GetHeight() const { return height; }

  private:
    uint32 x;
    uint32 y;

    uint32 width;
    uint32 height;
};

/**
* ProjectionPolicy which implements perspective projection using field of view (fov), near and far clipping planes.
*/
struct PerspectiveProjectionPolicy {
    PerspectiveProjectionPolicy(float fov, float nearClip, float farClip)
        : fov(fov), nearClip(nearClip), farClip(farClip) {}

    /// Calculates a perspective projection matrix.
    glm::mat4 Calculate(float aspectRatio) const { return glm::perspective(fov, aspectRatio, nearClip, farClip); }

    float fov = 45.0f;
    float nearClip = .1f;
    float farClip = 1000.0f;
};

/**
* ProjectionPolicy which implements orthogonal projection using an orthogonal size.
*/
struct OrthogonalProjectionPolicy {
    OrthogonalProjectionPolicy(float orthoSize) : orthoSize(orthoSize) {}

    /// Calculates a orthogonal projection matrix.
    glm::mat4 Calculate(float aspectRatio) const {
        return glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);
    }

    float orthoSize = 1.0f;
};

/**
* A SceneView represents a view into a Scene.
*
* The rendering thread own state and data of this class once the view's ViewComposition has been submitted.
*/
struct BD_API_EXPORT SceneView {
  public:
    template <class TProjectionPolicy, class... TArgs>
    SceneView(const ViewRect& viewRect, const Transform& viewTransform, TArgs&&... args)
        : viewRect(viewRect), viewTransform(viewTransform),
          projectionPolicy(new ProjectionPolicyHolderImpl<TProjectionPolicy>(std::forward(args)...)) {
        UpdateViewProjectionMatrix();
    }

    template <class TProjectionPolicy>
    SceneView(const ViewRect& viewRect, const Transform& viewTransform, TProjectionPolicy projectionPolicy)
        : viewRect(viewRect), viewTransform(viewTransform),
          projectionPolicy(new ProjectionPolicyHolderImpl<TProjectionPolicy>(projectionPolicy)) {
        UpdateViewProjectionMatrix();
    }

    SceneView(const SceneView& other)
        : viewRect(other.viewRect), viewTransform(other.viewTransform),
          viewProjectionMatrix(other.viewProjectionMatrix), projectionPolicy(other.projectionPolicy->Clone()) {}

    virtual ~SceneView() = default;

    const ViewRect& GetViewRect() const { return viewRect; }
    const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

  protected:
    /// Base for templatized holder implementations.
    struct ProjectionPolicyHolder {
        virtual glm::mat4 CalculateProjectionMatrix(float aspectRatio) = 0;
        virtual std::unique_ptr<ProjectionPolicyHolder> Clone() = 0;
    };

    /// Templatized projection policy holder which is part of the solution to allow value semantics on SceneView.
    template <class TProjectionPolicy> struct ProjectionPolicyHolderImpl : public ProjectionPolicyHolder {
      public:
        template <class... TArgs>
        ProjectionPolicyHolderImpl(TArgs&&... args)
            : projectionPolicy(std::forward<TArgs>(args)...) {}

        virtual glm::mat4 CalculateProjectionMatrix(float aspectRatio) override {
            return projectionPolicy.Calculate(aspectRatio);
        }

        virtual std::unique_ptr<ProjectionPolicyHolder> Clone() override {
            return std::make_unique<ProjectionPolicyHolderImpl<TProjectionPolicy>>(projectionPolicy);
        }

      private:
        /// Policy which calculates the projection matrix
        TProjectionPolicy projectionPolicy;
    };

    void UpdateViewProjectionMatrix() {
        float aspectRatio = viewRect.GetWidth() / viewRect.GetHeight();
        viewProjectionMatrix =
                glm::transpose(viewTransform.ToMatrix()) * projectionPolicy->CalculateProjectionMatrix(aspectRatio);
    }

    /// This view's projection area mapped into the SceneViewComposition
    const ViewRect viewRect;
    /// Position and rotation of the camera
    const Transform viewTransform;
    /// Cached view*projection matrix
    glm::mat4 viewProjectionMatrix;

    const std::unique_ptr<ProjectionPolicyHolder> projectionPolicy;
};

/**
* Helper class which builds scene views.
*/
struct SceneViewBuilder {
  public:
    /// Creates a builder which will use the specified projection policy when instantiating a SceneView.
    template <class TProjectionPolicy, class... TArgs> static SceneViewBuilder CustomProjectionView(TArgs&&... args) {
        std::unique_ptr<Builder> builderImpl =
            std::make_unique<BuilderImpl<TProjectionPolicy>>(std::forward<TArgs>(args)...);
        return SceneViewBuilder(std::move(builderImpl));
    }

    /// Creates a builder which will use the OrthogonalProjectionPolicy when instantiating a SceneView.
    static SceneViewBuilder OrthogonalProjectionView(float orthoSize) {
        return CustomProjectionView<OrthogonalProjectionPolicy>(orthoSize);
    }

    /// Creates a builder which will use the PerspectiveProjectionPolicy when instantiating a SceneView.
    static SceneViewBuilder PerspectiveProjectionView(float fieldOfView, float nearClip, float farClip) {
        return CustomProjectionView<PerspectiveProjectionPolicy>(fieldOfView, nearClip, farClip);
    }

    SceneViewBuilder& SetViewTransform(const Transform& transform) {
        builderImpl->SetViewTransform(transform);
        return *this;
    }

    SceneViewBuilder& SetViewRect(const ViewRect& viewRect) {
        builderImpl->SetViewRect(viewRect);
        return *this;
    }

    SceneView Finalize() { return std::move(builderImpl->Build()); }

  private:
    /// Builder implementation base class. Allows to store an instance of templatized BuilderImpl.
    struct Builder {
      public:
        void SetViewTransform(const Transform& transform) { viewTransform = transform; }
        void SetViewRect(const ViewRect& viewRect) { this->viewRect = viewRect; }
        virtual SceneView Build() = 0;

      protected:
        Transform viewTransform;
        ViewRect viewRect = {0, 0, 0, 0};
    };

    /// ProjectionPolicy-Templatized Builder implementation.
    template <class TProjectionPolicy> struct BuilderImpl : public Builder {
      public:
        template <class... TArgs> BuilderImpl(TArgs&&... args) : projectionPolicy(std::forward<TArgs>(args)...) {}
        virtual SceneView Build() override { return SceneView(viewRect, viewTransform, projectionPolicy); }

      private:
        TProjectionPolicy projectionPolicy;
    };

    SceneViewBuilder(std::unique_ptr<Builder> builderImpl) : builderImpl(std::move(builderImpl)) {}

    /// The actual builder implementation.
    std::unique_ptr<Builder> builderImpl;
};

/**
* A SceneViewComposition is a collection of @link SceneView SceneViews @endlink into a Scene.
*
* It basically composes different views into a single render target, holds common view states and can override
* view-specific rendering settings.
*/
class BD_API_EXPORT SceneViewComposition {
  public:
    SceneViewComposition(const std::vector<SceneView>& views, const RenderTarget& renderTarget)
        : views(views), renderTarget(renderTarget) {
        CalculateFamilySize();

        DebugAssert(compositionWidth >= renderTarget.GetTexture()->GetWidth());
        DebugAssert(compositionHeight >= renderTarget.GetTexture()->GetHeight());
    }
    /// SceneViewComposition constructor accepting a r-value vector of SceneView handles
    SceneViewComposition(std::vector<SceneView>&& views, const RenderTarget& renderTarget)
        : views(views), renderTarget(renderTarget) {
        CalculateFamilySize();

        DebugAssert(compositionWidth >= renderTarget.GetTexture()->GetWidth());
        DebugAssert(compositionHeight >= renderTarget.GetTexture()->GetHeight());
    }

    /**
    * Returns the maximum X of all views in this composition.
    * This is the minimum width the render target should have.
    */
    uint32 GetCompositionWidth() const { return compositionWidth; }

    /**
    * Returns the maximum y of all views in this composition.
    * This is the minimum height the render target should have.
    */
    uint32 GetCompositionHeight() const { return compositionHeight; }

    const std::vector<SceneView>& GetViews() const { return views; }
    const RenderTarget& GetRenderTarget() const { return renderTarget; }

  private:
    void CalculateFamilySize();

    const std::vector<SceneView> views;
    const RenderTarget renderTarget;

    uint32 compositionWidth = 0;
    uint32 compositionHeight = 0;
};

} /* namespace BlueDwarf */