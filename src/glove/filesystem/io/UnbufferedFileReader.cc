#include "glove/filesystem/io/UnbufferedFileReader.hpp"
#include "glove/DwarfException.hpp"
#include "glove/filesystem/exceptions/FileNotFoundException.hpp"
#include "glove/filesystem/exceptions/StreamErrorException.hpp"

namespace BlueDwarf {

UnbufferedFileReader::UnbufferedFileReader(const File& file) : rawStream(file.GetFilesystem()->CreateFileReadStream(file.GetPath())) {
    if(!file.Exists()) {
        DWARF_THROW(FileNotFoundException, file);
    }
}

void UnbufferedFileReader::Read(void* destination, std::size_t size) {
    if(!rawStream->good()) {
        DWARF_THROW(StreamErrorException, "Stream error");
    }

    rawStream->read(reinterpret_cast<char*>(destination), size);
}

UnbufferedFileReader::~UnbufferedFileReader() {
}
}