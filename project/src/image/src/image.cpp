#include <algorithm>
#include <iostream>

#include "image.hpp"


#include <iostream>
Image::Image()
:mImageHeight(0), mImageWidth(0), mImage(nullptr), mImageRows(nullptr)
{
	std::cout << "Image - empty" << std::endl;
}

Image::Image(Vector2d<size_t> imageSize, double* image)
{
	std::cout << "Image - 2args" << std::endl;
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
	std::cout << "Image - copy" << std::endl;
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
	std::cout << "Image - move" << std::endl;
	swap(*this, image);
}

Image::~Image()
{
	delete[] mImageRows;
	delete[] mImage;
}

Image Image::operator=(Image image)
{
	std::cout << "Image assigment" << std::endl;
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
