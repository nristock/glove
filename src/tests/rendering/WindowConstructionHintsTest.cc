#include <random>
#include <chrono>

#include <gmock/gmock.hpp>

#include <glove/rendering/WindowConstructionHints.hpp>

namespace glove {
TEST(WindowConstructionHintsTest, ConstructorSotresLocationTitleAndPosition) {
    std::default_random_engine generator(
        static_cast<ulong>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> distribution(0, 1000);

    int windowPosX = distribution(generator);
    int windowPosY = distribution(generator);
    int windowWidth = distribution(generator);
    int windowHeight = distribution(generator);

    WindowConstructionHints constructionHints(ScreenPoint(windowPosX, windowPosY),
                                              ScreenDimensions(windowWidth, windowHeight), "My cool title");

    EXPECT_EQ(windowPosX, constructionHints.GetPositionX());
    EXPECT_EQ(windowPosY, constructionHints.GetPositionY());
    EXPECT_EQ(windowWidth, constructionHints.GetWidth());
    EXPECT_EQ(windowHeight, constructionHints.GetHeight());
    EXPECT_EQ("My cool title", constructionHints.GetTitle());
}
}