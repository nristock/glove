#include <stdio.h>

#include <core/GloveCore.h>
#include "gmock/gmock.h"

int main(int argc, char** argv) {
    printf("Running main() from gtest_main.cc\n");

    const char* gloveInitArgs[] = {"", "--init-rendering", "0", "--init-scripting", "0"};

    glove::GloveCorePtr core = glove::GloveCorePtr(new glove::GloveCore(5, gloveInitArgs));
    core->Init(5, gloveInitArgs);

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
