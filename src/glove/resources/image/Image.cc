#include "glove/resources/image/Image.hpp"

namespace BlueDwarf {
Image::Image(unsigned int width, unsigned int height, ImageFormat format, unsigned char bitDepth)
    : width(width), height(height), format(format), bitDepth(bitDepth),
      imageData(width * height * static_cast<int>(format) * (bitDepth/8)) {
}

const std::vector<unsigned char>& Image::GetImageData() const {
    return imageData;
}

unsigned int Image::GetHeight() const {
    return height;
}

unsigned int Image::GetWidth() const {
    return width;
}

Image::ImageFormat Image::GetImageFormat() const {
    return format;
}

unsigned char Image::GetBitDepth() const {
    return bitDepth;
}
}