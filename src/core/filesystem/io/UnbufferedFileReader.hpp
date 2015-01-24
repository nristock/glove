#pragma once

#include <fstream>

#include "core/filesystem/io/IFileReader.hpp"
#include "core/filesystem/io/File.hpp"

namespace glove {

class UnbufferedFileReader : public IFileReader {
public:
    UnbufferedFileReader(const File& file);
    virtual ~UnbufferedFileReader();

    virtual void Read(void* destination, std::size_t size);
    virtual void Close();

private:
    std::ifstream rawStream;
};

} /* namespace glove */