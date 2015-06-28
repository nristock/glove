#include "glove/filesystem/io/IFileReader.hpp"
#include "glove/filesystem/io/UnbufferedFileReader.hpp"
#include "glove/resources/loader/ResourceLoader.hpp"
#include "glove/resources/image/PngImage.hpp"

namespace {
}

namespace BlueDwarf {

ImageHandle ResourceLoader::LoadPngImage(const Path& filePath) {
    File file(filePath);
    UnbufferedFileReader reader(file);
    return PngImage::Load(reader);
}
}
