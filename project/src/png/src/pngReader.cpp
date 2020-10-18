#include "pngReader.hpp"

void PngReader::open(const char path[])
{
    mPFile = fopen (path, "rb");
    if(mPFile != NULL)
    {
        mPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if(mPngPtr)
        {
            mInfoPtr = png_create_info_struct(mPngPtr);
            if(mInfoPtr)
            {
                png_init_io(mPngPtr, mPFile);
                png_read_png(mPngPtr, mInfoPtr, PNG_TRANSFORM_IDENTITY, NULL);
                mRows = png_get_rows(mPngPtr, mInfoPtr);
                png_get_IHDR(mPngPtr, mInfoPtr, &mHeight, &mWidth, &mBitDepth, &mColorType, &mInterlaceType, &mCompressionType, &mFilterMethod);
                fclose(mPFile);
            }
            else
            {
                png_destroy_read_struct(&mPngPtr, (png_infopp)NULL, (png_infopp)NULL);
            }
        }
    }
}

void PngReader::open(std::string path)
{
    open(path.c_str());
}


unsigned int PngReader::getPixelSize()
{
    switch(mColorType)
    {
        case PNG_COLOR_TYPE_GRAY:
            return 1;
        break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            return 2;
        break;
        case PNG_COLOR_TYPE_RGB:
            return 3;
        break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            return 4;
        break;
    }
    return 0;
}



FrameImage PngReader::createImage(Vector2d<size_t> frameSize, int mode)
{
    png_bytep rows;
    unsigned int size = getPixelSize();
    double* image = new double[mHeight*mWidth];
    double* imageTmp = image;

    for(int y = 0; y < mHeight; y++)
    {
        png_bytep rows = mRows[y];
        for(int x = 0; x < mWidth; x++)
        {
            unsigned int tmp = 0;
            for(int i = 0; i < size; i++)
            {
                unsigned int t = (((*rows) << (size - i - 1) * 8));
                tmp |= t;
                rows++;
            }
            *imageTmp = static_cast<double>(tmp);
            imageTmp++;
        }
    }

    auto b = FrameImage(Vector2d<size_t>(mHeight,mWidth), frameSize, image);
    delete[] image;
    return b;
}

void PngReader::convert(PngMode mode)
{

}


FrameImage PngReader::getImage(Vector2d<size_t> frameSize)
{
    return createImage(frameSize, mColorType);
}
