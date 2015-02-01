#include "UnbufferedFileReader.hpp"
#include "core/GloveException.h"
#include "core/filesystem/exceptions/FileNotFoundException.hpp"
#include "core/filesystem/exceptions/StreamErrorException.hpp"

namespace glove {

UnbufferedFileReader::UnbufferedFileReader(const File& file) : rawStream(file.GetFilesystem()->CreateFileReadStream(file.GetPath())) {
    if(!file.Exists()) {
        GLOVE_THROW(FileNotFoundException, file);
    }
}

void UnbufferedFileReader::Read(void* destination, std::size_t size) {
    if(!rawStream->good()) {
        GLOVE_THROW(StreamErrorException, "Stream error");
    }

    rawStream->read(reinterpret_cast<char*>(destination), size);
}

UnbufferedFileReader::~UnbufferedFileReader() {
}
}