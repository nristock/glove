#include "glove/filesystem/io/IFileReader.hpp"
#include "glove/filesystem/io/UnbufferedFileReader.hpp"
#include "glove/resources/loader/ResourceLoader.hpp"
#include "glove/resources/image/PngImage.hpp"

namespace {
}

namespace glove {

ImageHandle ResourceLoader::LoadPngImage(IFileReader& reader) {
    return PngImage::Load(reader);
}
}
