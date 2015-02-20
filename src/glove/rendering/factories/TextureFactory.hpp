#pragma once

#include "glove/GloveApi.hpp"
#include "glove/resources/Resources.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT TextureFactory : public BasicService{
public:
    static ServiceType serviceType;

    TextureFactory() : BasicService(serviceType) {}
    virtual ~TextureFactory() = default;

    virtual TextureHandle CreateFromImage(const ImageHandle& image) = 0;
};

}