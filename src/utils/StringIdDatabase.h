#pragma once

#include <map>

#include <pitamem/MemoryProfile.h>
#include <log/Log.h>

namespace glove {

class StringIdDatabase : public std::enable_shared_from_this<StringIdDatabase> {
Profilable();
public:
    StringIdDatabase() : EnableProfilable() {
    }

    virtual ~StringIdDatabase() {
    }

    std::size_t RegisterString(const char* string);

    const char* GetCString(std::size_t id);

    const std::string& GetString(std::size_t id);

    void Reset();

    std::size_t GetRegisteredStringCount() const {
        return stringMap.size();
    }

    static std::size_t HashString(const char* string) {
        return std::hash<const char*>()(string);
    }

private:
    typedef std::map<std::size_t, std::string> StringMap;
    typedef std::pair<std::size_t, std::string> Entry;

    logging::GloveLogger logger;

    std::map<std::size_t, std::string> stringMap;
};

} /* namespace glove */