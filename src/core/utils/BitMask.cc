#include <elf.h>
#include "BitMask.h"

namespace glove {
const std::uint8_t BitMask::MAX_INDEX = 31;

BitMask::BitMask() : mask(0) {

}

void BitMask::Set(BitMask::BitIndex index) {
    mask |= (1 << index);
}

void BitMask::Clear(BitMask::BitIndex index) {
    mask &= ~(1 << index);
}

bool BitMask::IsSet(BitMask::BitIndex index) const {
    return (mask & (1 << index)) != 0;
}

bool BitMask::operator[](BitMask::BitIndex index) const {
    return IsSet(index);
}

uint32_t BitMask::ToInt32() const {
    return mask;
}

bool BitMask::Contains(const BitMask& other) const {
    return (mask | other.mask) == mask;
}
}