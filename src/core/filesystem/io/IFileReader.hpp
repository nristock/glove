#pragma once

namespace glove {

class IFileReader {
public:
    virtual ~IFileReader() = default;

    virtual void Read(void* destination, std::size_t size) = 0;
};

} /* namespace glove */