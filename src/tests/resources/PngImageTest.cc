#include <gtest/gtest.hpp>

#include <glove/filesystem/inmemory/InMemoryFilesystem.hpp>
#include <glove/filesystem/Filesystem.hpp>
#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/io/File.hpp>
#include <glove/filesystem/io/UnbufferedFileReader.hpp>
#include <glove/resources/image/PngImage.hpp>

#include "tests/filesystem/mock/MockFilesystemAccessor.hpp"

namespace {
const glove::Path rgbaPath("testdata/png_rgba.png");
const glove::Path solidWhitePath("testdata/png_solid_white.png");

const unsigned char rgbaExpectedData[] = {255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 0, 0, 0, 0};
const unsigned int rgbaExpectedWidth = 2;
const unsigned int rgbaExpectedHeight = 2;
const unsigned char rgbaExpectedBitDepth = 8;
const glove::Image::ImageFormat rgbaExpectedImageFormat = glove::Image::ImageFormat::RGBA;

const unsigned char solidWhiteExpectedData[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
const unsigned int solidWhiteExpectedWidth = 2;
const unsigned int solidWhiteExpectedHeight = 2;
const unsigned char solidWhiteExpectedBitDepth = 8;
const glove::Image::ImageFormat solidWhiteExpectedImageFormat = glove::Image::ImageFormat::RGB;
}

namespace glove {

TEST(PngImageTest, CanLoadRgba) {
    File file(::rgbaPath);
    UnbufferedFileReader reader(file);
    ImageHandle image = PngImage::Load(reader);

    EXPECT_EQ(rgbaExpectedWidth, image->GetWidth());
    EXPECT_EQ(rgbaExpectedHeight, image->GetHeight());
    EXPECT_EQ(rgbaExpectedBitDepth, image->GetBitDepth());
    EXPECT_EQ(rgbaExpectedImageFormat, image->GetImageFormat());

    unsigned int bytesTotal =
        rgbaExpectedWidth * rgbaExpectedHeight * (rgbaExpectedBitDepth / 8) * static_cast<int>(rgbaExpectedImageFormat);
    ASSERT_EQ(bytesTotal, image->GetImageData().size());

    for (std::size_t i = 0; i < image->GetImageData().size(); ++i) {
        EXPECT_EQ(rgbaExpectedData[i], image->GetImageData()[i]) << "Image data mismatch at " << i;
    }
}

TEST(PngImageTest, CanLoadSolidWhiteWithoutAlpha) {
    File file(::solidWhitePath);
    UnbufferedFileReader reader(file);
    ImageHandle image = PngImage::Load(reader);

    EXPECT_EQ(solidWhiteExpectedWidth, image->GetWidth());
    EXPECT_EQ(solidWhiteExpectedHeight, image->GetHeight());
    EXPECT_EQ(solidWhiteExpectedBitDepth, image->GetBitDepth());
    EXPECT_EQ(solidWhiteExpectedImageFormat, image->GetImageFormat());

    unsigned int bytesTotal = solidWhiteExpectedWidth * solidWhiteExpectedHeight * (solidWhiteExpectedBitDepth / 8) *
                              static_cast<int>(solidWhiteExpectedImageFormat);
    ASSERT_EQ(bytesTotal, image->GetImageData().size());

    for (std::size_t i = 0; i < image->GetImageData().size(); ++i) {
        EXPECT_EQ(solidWhiteExpectedData[i], image->GetImageData()[i]) << "Image data mismatch at " << i;
    }
}

} /* namespace glove */