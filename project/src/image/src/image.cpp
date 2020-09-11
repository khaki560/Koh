#include <algorithm>
#include <iostream>

#include "image.hpp"

Image::Image(Vector2d<size_t> imageSize, double* image)
{
	mImageHeight = imageSize.el1;
	mImageWidth = imageSize.el2;

	size_t imageSize2 = mImageHeight * mImageWidth;

	mImage = new double[imageSize2];
	mImageRows = new double*[mImageHeight];

	std::copy(image, image + imageSize2, mImage);
	for(int y = 0; y < mImageHeight; y++)
	{
		mImageRows[y] = &mImage[y*mImageWidth];
	}
}


// Image::Image(Vector2d<size_t> framesize, double** image)
// {
// 	mImageHeight = framesize.x;
// 	mImageHeight = framesize.y;
// }

Image::Image(const Image& image)
{

}

Image::Image(Image&& image)
{

}

Image::~Image()
{
	delete[] mImageRows;
	delete[] mImage;
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
