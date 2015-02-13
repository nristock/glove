#pragma once

#include "glove/GloveApi.hpp"
#include "glove/filesystem/Filesystem.hpp"
#include "glove/resources/Resources.hpp"

namespace glove {

class GLOVE_API_EXPORT ResourceLoader {
  public:
    static ImageHandle LoadPngImage(IFileReader& reader);
};

} /* namespace glove */