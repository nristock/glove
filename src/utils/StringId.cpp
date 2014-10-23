#include "utils/StringId.h"

#include "core/GloveFwd.h"
#include "utils/StringIdDatabase.h"

namespace glove {

StringId::StringId(size_t hashId) : hashId(hashId) {
}

StringId::StringId(const StringIdDatabasePtr& stringDb, const char* string)
        : StringId(StringIdDatabase::HashString(string)) {
    Resolve(stringDb);

    if (message.empty()) {
        stringDb->RegisterString(string);
    }
}

StringId::~StringId() {

}


void StringId::Resolve(const std::shared_ptr<StringIdDatabase>& stringDb) {
    if (message.empty()) {
        message = stringDb->GetString(hashId);
    }
}
}