#include "tests/gtest/gtest.h"
#include "utils/StringIdDatabase.h"


#include "tests/GloveTest.h"

namespace glove {
	class StringIdDatabaseTest : public GloveTest {
	protected:
		const char* testString = "My cool string";
		const char* testString2 = "My cool string 2";
		const char* testString3 = "My cool string 3";

		StringIdDatabase stringDb;
	public:
		StringIdDatabaseTest() {
		}
	};

	TEST_F(StringIdDatabaseTest, InitialDbIsEmpty) {
		ASSERT_EQ(0, stringDb.GetRegisteredStringCount());
	}

	TEST_F(StringIdDatabaseTest, StringRegistrationReturnsHashId) {
		size_t hashId = stringDb.RegisterString(testString);

		ASSERT_NE(0, hashId);
	}

	TEST_F(StringIdDatabaseTest, CanGetRegisteredStringByHash) {
		size_t hashId = stringDb.RegisterString(testString);
		
		ASSERT_STREQ(testString, stringDb.GetCString(hashId));
		ASSERT_STREQ(testString, stringDb.GetString(hashId).c_str());
	}

	TEST_F(StringIdDatabaseTest, ReportsNumberOfRegisteredStings) {
		ASSERT_EQ(0, stringDb.GetRegisteredStringCount());
		stringDb.RegisterString(testString);
		ASSERT_EQ(1, stringDb.GetRegisteredStringCount());
		stringDb.RegisterString(testString2);
		ASSERT_EQ(2, stringDb.GetRegisteredStringCount());
		stringDb.RegisterString(testString3);
		ASSERT_EQ(3, stringDb.GetRegisteredStringCount());
	}

	TEST_F(StringIdDatabaseTest, CanResetStringIdDatabase) {
		ASSERT_EQ(0, stringDb.GetRegisteredStringCount());
		stringDb.RegisterString(testString);
		ASSERT_EQ(1, stringDb.GetRegisteredStringCount());
		stringDb.Reset();
		ASSERT_EQ(0, stringDb.GetRegisteredStringCount());
	}

}