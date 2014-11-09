#include <vendor/gtest/gtest.h>
#include "utils/StringIdDatabase.h"
#include "utils/StringId.h"

#include "core/GloveCore.h"

namespace glove {
	class StringIdTest : public ::testing::Test {
	protected:
		size_t hashId;
		const char* testString = "My cool string";
		const char* testString2 = "Another cool string";

		StringIdDatabasePtr stringDb;
	public:
		StringIdTest() {
			stringDb = std::make_shared<StringIdDatabase>();
			hashId = StringIdDatabase::HashString(testString);

			stringDb->RegisterString(testString);
		}
	};

	TEST_F(StringIdTest, CanCreateByHashId) {
		StringId stringId(hashId);
		stringId.Resolve(stringDb->shared_from_this());

		ASSERT_STREQ(testString, stringId.GetMessage().c_str());
	}

	TEST_F(StringIdTest, AutomaticallyRegistersUnowknStringsToDatabase) {
		StringId stringId(stringDb, testString2);
		stringId.Resolve(stringDb);

		ASSERT_STREQ(testString2, stringDb->GetCString(stringId.GetHashId()));
	}

	TEST_F(StringIdTest, GetMessageAutomaticallyResolvesMessage) {
		StringId stringId(hashId);

		ASSERT_STREQ(testString, stringId.GetMessage(stringDb->shared_from_this()).c_str());
	}
}