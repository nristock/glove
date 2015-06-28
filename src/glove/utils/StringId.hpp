#pragma once

#include <string>
#include <shared_mutex>
#include <unordered_map>

#include "glove/GloveApi.hpp"
#include "glove/utils/hash/Fnv1a.hpp"

using namespace glove;

namespace BlueDwarf {
struct GLOVE_API_EXPORT StringId {
  public:
    explicit StringId(const std::string& str);
    explicit StringId(uint64 hash);

    std::string Resolve() const;
    uint64 GetHash() const;

    bool operator==(const StringId& other) const;
    bool operator!=(const StringId& other) const;
    friend std::ostream& operator<< (std::ostream& stream, const StringId& stringId);

    struct StdHash {
        std::size_t operator()(const StringId& stringId) const {
            return stringId.hash;
        }
    };

  private:
    const uint64 hash;
};

std::ostream& operator<<(std::ostream& stream, const StringId& stringId);

template<class THasher>
class GLOVE_API_EXPORT StringIdDatabase {
  public:
    StringId GetId(const std::string& str) {
        auto stringId = StringId{hasher.Hash((const uint8*) str.c_str(), str.length())};

        {
            auto readLock = ReadLock{databaseMutex};
            if (strings.count(stringId) > 0) {
                return stringId;
            }
        }

        {
            auto writeLock = WriteLock{databaseMutex};
            if(strings.count(stringId) == 0) {
                strings[stringId] = str;
            }

            return stringId;
        }
    };

    std::string Resolve(const StringId& stringId) {
        auto readLock = ReadLock{databaseMutex};
        return strings[stringId];
    }

  private:
    using ReadLock = std::shared_lock<std::shared_timed_mutex>;
    using WriteLock = std::unique_lock<std::shared_timed_mutex>;

    const THasher hasher = THasher{};
    std::unordered_map<StringId, std::string, StringId::StdHash> strings;
    std::shared_timed_mutex databaseMutex;
};

extern StringIdDatabase<Hash::Fnv1a> g_StringIdDatabase;
}