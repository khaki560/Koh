#include "image.hpp"

#include <algorithm>

Image::Image()
:mImageHeight(0), mImageWidth(0), mImage(nullptr), mImageRows(nullptr)
{
}

Image::Image(Vector2d<size_t> imageSize, double* image)
{
	mImageHeight = imageSize.el1;
	mImageWidth = imageSize.el2;

	mImageSize = mImageHeight * mImageWidth;

	mImage = new double[mImageSize];
	mImageRows = new double*[mImageHeight];

	std::copy(image, image + mImageSize, mImage);
	for(int y = 0; y < mImageHeight; y++)
	{
		mImageRows[y] = &mImage[y*mImageWidth];
	}
}


Image::Image(const Image& image)
{
	mImageHeight = image.mImageHeight;
	mImageWidth = image.mImageWidth;
	mImageSize = mImageHeight * mImageWidth;
	mImage = new double[mImageSize];
	mImageRows = new double*[mImageHeight];

	std::copy(image.mImage, image.mImage + mImageSize, mImage);

	for(int y = 0; y < mImageHeight; y++)
	{
		mImageRows[y] = &mImage[y*mImageWidth];
	}
}

Image::Image(Image&& image)
:Image()
{
	swap(*this, image);
}

Image::~Image()
{
	delete[] mImageRows;
	delete[] mImage;
}

Image Image::operator=(Image image)
{
	return Image(image);
}

void swap(Image& first, Image& second)
{
	using std::swap;
	swap(first.mImageHeight, second.mImageHeight);
	swap(first.mImageWidth, second.mImageWidth);
	swap(first.mImage, second.mImage);
	swap(first.mImageRows, second.mImageRows);
	swap(first.mImageSize, second.mImageSize);
}

double* Image::getImage()
{
	return mImage;
}

Vector2d<size_t> Image::getSize()
{
	return Vector2d<size_t>(mImageHeight, mImageWidth);
}



void Image::printImage()
{
	for(int y = 0; y < mImageHeight; y++)
	{
		for(int x = 0; x < mImageWidth; x++)
		{
			std::cout << mImageRows[y][x] << ", ";
		}
		std::cout << std::endl;
	}
}

void Image::printFlat()
{
	for(int i = 0; i < mImageHeight*mImageWidth; i++)
	{
		std::cout << mImage[i] << ", ";
	}
	std::cout << std::endl;
}
