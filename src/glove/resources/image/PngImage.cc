#include "glove/resources/image/PngImage.hpp"
#include "glove/filesystem/io/UnbufferedFileReader.hpp"

namespace {
using BlueDwarf::IFileReader;

void ReadPngData(png_structp png, png_bytep data, png_size_t length) {
    IFileReader* reader = (IFileReader*)png_get_io_ptr(png);
    reader->Read(data, length);
}

bool IsPngFile(IFileReader& reader) {
    std::vector<unsigned char> pngFileHeader(BD_PNG_SIG_LOOKAHEAD);
    reader.Read(pngFileHeader.data(), BD_PNG_SIG_LOOKAHEAD);

    return png_sig_cmp(const_cast<const unsigned char*>(pngFileHeader.data()), 0, BD_PNG_SIG_LOOKAHEAD) == 0;

}

void SetupTransformations(png_structp pngStruct, png_infop pngInfo) {
    if (png_get_color_type(pngStruct, pngInfo) & PNG_COLOR_MASK_PALETTE) {
        png_set_palette_to_rgb(pngStruct);
    }

    if (png_get_bit_depth(pngStruct, pngInfo) < 8) {
        png_set_packing(pngStruct);
    }

    png_read_update_info(pngStruct, pngInfo);
}
}

namespace BlueDwarf {

PngImage::PngImage(unsigned int width, unsigned int height, const Image::ImageFormat& format, unsigned char bitDepth,
                   png_structp pngStruct, png_infop pngInfo)
    : Image(width, height, format, bitDepth) {
    std::size_t bytesPerRow = png_get_rowbytes(pngStruct, pngInfo);
    if(height * bytesPerRow != imageData.size()) {
        imageData.resize(height * bytesPerRow);
    }

    png_bytep pngRows[height];
    for (unsigned int i = 0; i < height; ++i) {
        pngRows[i] = imageData.data() + i * width * (bitDepth / 8) * static_cast<int>(format);
    }

    png_read_image(pngStruct, pngRows);

    png_destroy_info_struct(pngStruct, &pngInfo);
    png_destroy_read_struct(&pngStruct, nullptr, nullptr);
}

ImageHandle PngImage::Load(IFileReader& reader) {
    if(!::IsPngFile(reader)) {
        //TODO: throw
    }

    png_structp pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (pngStruct == nullptr) {
        // TODO: throw
    }

    png_infop pngInfo = png_create_info_struct(pngStruct);
    if (pngInfo == nullptr) {
        png_destroy_read_struct(&pngStruct, nullptr, nullptr);
        // TODO: throw
    }

    png_set_read_fn(pngStruct, &reader, ReadPngData);
    png_set_sig_bytes(pngStruct, BD_PNG_SIG_LOOKAHEAD);

    png_read_info(pngStruct, pngInfo);

    ::SetupTransformations(pngStruct, pngInfo);

    unsigned int width = png_get_image_width(pngStruct, pngInfo);
    unsigned int height = png_get_image_height(pngStruct, pngInfo);
    unsigned char bitDepth = png_get_bit_depth(pngStruct, pngInfo);
    char numChannels = png_get_channels(pngStruct, pngInfo);

    return ImageHandle(new PngImage(width, height,
                                    numChannels == 4 ? PngImage::ImageFormat::RGBA : PngImage::ImageFormat::RGB,
                                    bitDepth, pngStruct, pngInfo));
}
}