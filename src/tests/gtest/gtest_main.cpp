#include <stdio.h>

#include "core/GloveCore.h"
#include "tests/gmock/gmock.h"

int main(int argc, char** argv) {
    printf("Running main() from gtest_main.cc\n");

    char* gloveInitArgs[] = {"", "--init-rendering=false", "--init-scripting=false"};

    glove::GloveCore* core = new glove::GloveCore();
    core->Init(3, gloveInitArgs);

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
