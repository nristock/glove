#pragma once

#include <istream>

#include "glove/filesystem/io/IFileReader.hpp"
#include "glove/filesystem/io/File.hpp"

namespace glove {

class UnbufferedFileReader : public IFileReader {
public:
    UnbufferedFileReader(const File& file);
    virtual ~UnbufferedFileReader();

    virtual void Read(void* destination, std::size_t size);

private:
    InputStreamHandle rawStream;
};

} /* namespace glove */