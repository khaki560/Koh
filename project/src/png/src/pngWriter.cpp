#include "pngWriter.hpp"
#include <iostream>

bool PngWriter::convertToGray(FrameImage image)
{
	for(int h = 0; h < mHeight; h++)
	{
		double *imageRow = image.getImageRow(h);
		for(int w = 0; w < mWidth; w+=1)
		{
			mRows[h][w] = static_cast<png_byte>(imageRow[w]);
		}
	}

	mType = PNG_COLOR_TYPE_GRAY;
	return true;
}
bool PngWriter::convertToGrayAlfa(FrameImage image)
{
	for(int h = 0; h < mHeight; h++)
	{
		double *imageRow = image.getImageRow(h);
		for(int w = 0; w < mWidth*2; w+=2)
		{
			long long color = static_cast<unsigned long long>(imageRow[w/3]);
			int gray = (color & 0xFF00) >> 8;
			int apha = (color & 0x00FF);
			mRows[h][w] = gray;
			mRows[h][w+1] = apha;
		}
	}
	mType = PNG_COLOR_TYPE_GRAY_ALPHA;
	return true;
}
bool PngWriter::convertToRgb(FrameImage image)
{
	for(int h = 0; h < mHeight; h++)
	{
		double *imageRow = image.getImageRow(h);
		for(int w = 0; w < mWidth*3; w+=3)
		{
			unsigned long long color = static_cast<unsigned long long>(imageRow[w/3]);
			unsigned int red = (color & 0xFF0000) >> 16;
			unsigned int green = (color & 0x00FF00) >> 8;
			unsigned int blue = color & 0x0000FF;

			mRows[h][w] = static_cast<png_byte>(red);
			mRows[h][w+1] = static_cast<png_byte>(green);
			mRows[h][w+2] = static_cast<png_byte>(blue);
		}
	}
	mType = PNG_COLOR_TYPE_RGB;
	return true;
}
bool PngWriter::convertToRgbAlpha(FrameImage image)
{
	for(int h = 0; h < mHeight; h++)
	{
		double *imageRow = image.getImageRow(h);
		for(int w = 0; w < mWidth*4; w+=4)
		{
			unsigned long long color = static_cast<unsigned long long>(imageRow[w/4]);
			unsigned int red   = (color & 0xFF000000) >> 24;
			unsigned int green = (color & 0x00FF0000) >> 16;
			unsigned int blue  = (color & 0x0000FF00) >> 8;
			unsigned int alpha =  color & 0x000000FF;

			mRows[h][w] = static_cast<png_byte>(red);
			mRows[h][w+1] = static_cast<png_byte>(green);
			mRows[h][w+2] = static_cast<png_byte>(blue);
			mRows[h][w+3] = static_cast<png_byte>(alpha);
		}
	}
	mType = PNG_COLOR_TYPE_RGB_ALPHA;
	return true;
}

bool PngWriter::convertToPngBytes(FrameImage image, PngMode mode)
{
	switch (mode)
	{
	case PngMode::GREY:
		createBytesArray(1);
		return convertToGray(image);
	break;
	case PngMode::GREY_ALPHA:
		createBytesArray(2);
		return convertToGrayAlfa(image);
	break;
	case PngMode::RGB:
		createBytesArray(3);
		return convertToRgb(image);
	break;
	case PngMode::RGB_ALPHA:
		createBytesArray(4);
		return convertToRgbAlpha(image);
	break;
	default:
		std::cout << "error ratuj sie kto moze" << std::endl;
		return false;
	break;
	}
}


void PngWriter::createBytesArray(size_t size)
{
	mRows = new png_bytep[mHeight];
	for( int i = 0; i < mHeight; i++)
	{
		mRows[i] = new png_byte[mWidth*size];
	}
}

void PngWriter::deleteByteArray()
{

	for( int i = 0; i < mHeight; i++)
	{
		delete[] mRows[i];
	}
	delete[] mRows;
}

void PngWriter::save(const char path[], FrameImage image, PngMode mode)
{
	mHeight = image.getSize().el1;
	mWidth  = image.getSize().el2;

	if(convertToPngBytes(image, mode))
	{
		mPFile = fopen (path, "wb");
		if(mPFile != NULL)
		{
			mPngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if(mPngPtr)
			{
				mInfoPtr = png_create_info_struct(mPngPtr);
				if(mInfoPtr)
				{
					png_init_io(mPngPtr, mPFile);
					png_set_IHDR(mPngPtr, mInfoPtr, mWidth, mHeight, mbitDepth, mType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
					png_set_rows(mPngPtr, mInfoPtr, mRows);
					png_write_png(mPngPtr, mInfoPtr, PNG_TRANSFORM_IDENTITY, NULL);
					fclose(mPFile);
					deleteByteArray();
				}
			}
		}
	}
}

void PngWriter::save(std::string path, FrameImage image, PngMode mode)
{
	save(path.c_str(), image, mode);
}
