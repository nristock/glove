#pragma once

#include <png.h>

#include "glove/BlueDwarfApi.hpp"
#include "glove/resources/Resources.hpp"
#include "glove/resources/image/Image.hpp"
#include "glove/filesystem/io/File.hpp"
#include "glove/filesystem/io/IFileReader.hpp"

#if !defined(BD_PNG_SIG_LOOKAHEAD)
#define BD_PNG_SIG_LOOKAHEAD 8
#endif

namespace BlueDwarf {

class BD_API_EXPORT PngImage : public Image {
  public:
    static ImageHandle Load(IFileReader& reader);

  private:
    PngImage(unsigned int width, unsigned int height, const ImageFormat& format, unsigned char bitDepth, png_structp pngStruct, png_infop pngInfo);
};

} /* namespace BlueDwarf */