#include "utils/StringIdDatabase.h"


namespace glove {
size_t StringIdDatabase::RegisterString(const char* string) {
    size_t stringId = HashString(string);
    stringMap.insert(Entry(stringId, std::string(string)));

    return stringId;
}

const char* StringIdDatabase::GetCString(size_t id) {
    if (stringMap.find(id) == stringMap.end()) {
        return "";
    }

    return stringMap[id].c_str();
}

const std::string& StringIdDatabase::GetString(size_t id) {
    if (stringMap.find(id) == stringMap.end()) {
        return "";
    }

    return stringMap[id];
}

void StringIdDatabase::Reset() {
#if !defined(GLOVE_TESTS_BUILD)
    LOG(logger, info, "StringID Database has been reset");
#endif
    stringMap.clear();
}
}