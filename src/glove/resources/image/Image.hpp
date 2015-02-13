#pragma once

#include <vector>

#include "glove/GloveApi.hpp"

namespace glove {

class GLOVE_API_EXPORT Image {
  public:
    enum class ImageFormat : int {RGB = 3, RGBA = 4};
    Image(unsigned int width, unsigned int height, ImageFormat format, unsigned char bitDepth);

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    ImageFormat GetImageFormat() const;
    unsigned char GetBitDepth() const;
    const std::vector<unsigned char>& GetImageData() const;

  protected:
    unsigned int width;
    unsigned int height;

    ImageFormat format;
    unsigned char bitDepth;

    std::vector<unsigned char> imageData;
};

} /* namespace glove */