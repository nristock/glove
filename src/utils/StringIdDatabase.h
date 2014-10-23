#pragma once

#include <map>
#include "core/GloveObject.h"
#include "utils/Singleton.h"

namespace glove {

class StringIdDatabase : public GloveObject, public std::enable_shared_from_this<StringIdDatabase> {
Profilable()
public:
    StringIdDatabase() : EnableProfilable() {
    }

    virtual ~StringIdDatabase() {
    }

    size_t RegisterString(const char* string);

    const char* GetCString(size_t id);

    const std::string& GetString(size_t id);

    void Reset();

    size_t GetRegisteredStringCount() const {
        return stringMap.size();
    }

    static size_t HashString(const char* string) {
        return std::hash<const char*>()(string);
    }

private:
    typedef std::map<size_t, std::string> StringMap;
    typedef std::pair<size_t, std::string> Entry;

    std::map<size_t, std::string> stringMap;
};

} /* namespace glove */