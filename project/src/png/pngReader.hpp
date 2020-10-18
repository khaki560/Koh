#include "pngMode.hpp"
#include "frameImage.hpp"
#include <png.h>

#ifndef PNG_READER_HPP
#define PNG_READER_HPP

class PngReader
{
private:
	png_bytepp mRows;
	FILE  *mPFile;
	png_structp mPngPtr;
	png_infop mInfoPtr;

	png_uint_32 mHeight;
	png_uint_32 mWidth;
	int mBitDepth;
	int mColorType;
	int mInterlaceType;
	int mCompressionType;
	int mFilterMethod;

	FrameImage createImage(Vector2d<size_t> frameSize, int mode);
	void convert(PngMode mode);
	unsigned int getPixelSize();
public:
	void open(std::string path);
	void open(const char path[]);

	FrameImage getImage(Vector2d<size_t> frameSize, PngMode mode);
	FrameImage getImage(Vector2d<size_t> frameSize);
	PngMode GetMode();
};


#endif //PNG_READER_HPP
