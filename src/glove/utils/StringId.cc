#include "glove/utils/StringId.hpp"

#include <ostream>

namespace BlueDwarf {
StringIdDatabase<Hash::Fnv1a> g_StringIdDatabase;


StringId::StringId(const std::string& str) : StringId(g_StringIdDatabase.GetId(str)) {

}

StringId::StringId(uint64 hash) : hash(hash) {

}

bool StringId::operator==(const StringId& other) const {
    return hash == other.hash;
}

bool StringId::operator!=(const StringId& other) const {
    return hash != other.hash;
}


std::string StringId::Resolve() const {
    return g_StringIdDatabase.Resolve(*this);
}

uint64 StringId::GetHash() const {
    return hash;
}

std::ostream& operator<<(std::ostream& stream, const StringId& stringId) {
    return stream << "StringId{hash: " << std::hex << stringId.hash << ", str: \"" << stringId.Resolve() << "\"}";
}
}