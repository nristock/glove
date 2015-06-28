#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/filesystem/Filesystem.hpp"
#include "glove/resources/Resources.hpp"

namespace BlueDwarf {

class BD_API_EXPORT ResourceLoader {
  public:
    static ImageHandle LoadPngImage(const Path& filePath);
};

} /* namespace BlueDwarf */