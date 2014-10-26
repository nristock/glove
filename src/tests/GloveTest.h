#pragma once

#include <bits/shared_ptr.h>
#include "tests/gtest/gtest.h"

#include "core/GloveCore.h"

namespace glove {

class GloveTest : public ::testing::Test {
public:
    GloveTest() {
        char* gloveInitArgs[] = {"", "--init-rendering=false", "--init-scripting=false"};

     //   gloveCore = std::make_shared<GloveCore>();
      //  gloveCore->Init(3, gloveInitArgs);
    }

protected:
    //GloveCorePtr gloveCore;
};

}