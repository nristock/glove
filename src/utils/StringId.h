#pragma once

#include <string>
#include <memory>

#include  "core/GloveException.h"
#include "utils/StringIdDatabase.h"

#define SID(_msg) ::glove::StringId(_msg)

namespace glove {

class StringId {
public:
    StringId(size_t hashId);

    StringId(const StringIdDatabasePtr& stringDb, const char* string);

    virtual ~StringId();

    void Resolve(const std::shared_ptr<StringIdDatabase>& stringDb);

    std::string GetMessage(const std::shared_ptr<StringIdDatabase>& stringDb) {
        if (message.empty()) {Resolve(stringDb);}
        return message;
    }

    std::string GetMessage() {
        if (message.empty()) {throw GLOVE_EXCEPTION("String message has not been resolved.");}
        return message;
    }

    size_t GetHashId() const {
        return hashId;
    }

private:
    std::string message;
    const size_t hashId;
};

} /* namespace glove */