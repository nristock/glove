#include <stdio.h>

#include <glove/GloveCore.h>
#include "gmock/gmock.h"

int main(int argc, char** argv) {
    const char* gloveInitArgs[] = {"", "--no-natex"};

    glove::GloveCorePtr core = glove::GloveCorePtr(new glove::GloveCore(2, gloveInitArgs));
    core->Init(2, gloveInitArgs);

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
