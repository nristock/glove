#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/CommonTypes.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {
namespace Hash {
struct BD_API_EXPORT Fnv1a {
    static const uint64 prime = 0x100000001B3;
    static const uint64 basisOffset = 0xcbf29ce484222325;

    static uint64 Hash(const uint8* data, uint32 length) {
        uint64 hash = basisOffset;

        for(uint32 i = 0; i < length; ++i) {
            hash ^= data[i];
            hash *= prime;
        }

        return hash;
    }

    static uint64 Hash(const std::string& str) {
        return Hash((const uint8*)str.c_str(), str.length());
    }

    static uint64 Hash(const char* str) {
        return Hash(std::string(str));
    }
};
}
}