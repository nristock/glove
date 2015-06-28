#pragma once

#include <cstdint>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
class BD_API_EXPORT BitMask {
public:
    typedef std::uint8_t BitIndex;
    static const std::uint8_t MAX_INDEX;

    BitMask();

    void Set(BitIndex index);
    void Clear(BitIndex index);
    bool IsSet(BitIndex index) const;

    bool Contains(const BitMask& other) const;

    bool operator[](BitIndex index) const;
    std::uint32_t ToInt32() const;

private:
    std::uint32_t mask;
};
}