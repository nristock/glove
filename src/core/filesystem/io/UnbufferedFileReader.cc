#include "UnbufferedFileReader.hpp"
#include "core/GloveException.h"
#include "core/filesystem/exceptions/FileNotFoundException.hpp"
#include "core/filesystem/exceptions/StreamErrorException.hpp"

namespace glove {

UnbufferedFileReader::UnbufferedFileReader(const File& file) {
    if(!file.Exists()) {
        GLOVE_THROW(FileNotFoundException, file);
    }

    rawStream.open(file.GetPath().ToString(), std::ifstream::in | std::ifstream::binary);
}

void UnbufferedFileReader::Read(void* destination, std::size_t size) {
    if(!rawStream.good()) {
        GLOVE_THROW(StreamErrorException, "Stream error");
    }

    rawStream.read(reinterpret_cast<char*>(destination), size);
}

void UnbufferedFileReader::Close() {
    rawStream.close();
}

UnbufferedFileReader::~UnbufferedFileReader() {
    Close();
}
}