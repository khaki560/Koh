#ifndef PNG_WRITER_HPP
#define PNG_WRITER_HPP

#include<string>
#include<png.h>

#include "pngMode.hpp"
#include "frameImage.hpp"

class PngWriter
{
private:
	png_bytepp mRows;
	FILE  *mPFile;
	png_structp mPngPtr;
	png_infop mInfoPtr;

	size_t mHeight;
	size_t mWidth;

	int mType;
	const int mbitDepth = 8;


	bool convertToPngBytes(FrameImage image, PngMode mode);
	bool convertToGray(FrameImage image);
	bool convertToGrayAlfa(FrameImage image);
	bool convertToRgb(FrameImage image);
	bool convertToRgbAlpha(FrameImage image);


	void createBytesArray(size_t size);
	void deleteByteArray();
public:
	PngWriter() = default;
	~PngWriter() = default;
	PngWriter(const PngWriter &) =delete;
	PngWriter(PngWriter &&) =delete;

	void save(const char path[], FrameImage image, PngMode mode);
	void save(std::string path, FrameImage image, PngMode mode);
};

#endif //PNG_WRITER_HPP
