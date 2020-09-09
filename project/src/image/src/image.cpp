#include <algorithm>
#include <iostream>

#include "image.hpp"

Image::Image(Vector2d<size_t> imageSize, Vector2d<size_t> frameSize, double* image)
{

	mWidth = imageSize.x;
	mHeight = imageSize.y;
	size_t imageSize2 = mHeight * mWidth;

	mImage = new double[imageSize2];
	mImageRows = new double*[mHeight];

	std::copy(image, image + imageSize2, mImage);
	for(int y = 0; y < mHeight; y++)
	{
		mImageRows[y] = &mImage[y*mWidth];
	}

	mFrameHeight = frameSize.x;
	mFrameWidth = frameSize.y;
	size_t frameSize_2 = mFrameHeight * mFrameWidth;


	if(mWidth % mFrameWidth != 0 || mHeight % mFrameHeight != 0)
	{
		std::cerr << "Wrong frameSize" << std::endl;
	}

	int numberOfFramesX = mWidth / mFrameWidth;
	int numberOfFramesY = mHeight / mFrameHeight;


	for(int i = 0; i < numberOfFramesY; i++)
	{
		std::vector<Frame> tmp;
		mFrames.push_back(tmp);
	}

	double tempArr[frameSize_2];
	for(int y = 0; y < numberOfFramesY; y++)
	{
		for(int x = 0; x < numberOfFramesX; x++)
		{
			for(int i = 0; i < mFrameHeight; i++)
			{
				for(int j = 0; j < mFrameWidth; j++)
				{
					std::cout << i+y*mFrameHeight << "," << j+x*mFrameWidth << std::endl;
					std::cout << "tempArr" << i*mFrameWidth+j << std::endl;
					tempArr[i*mFrameWidth+j] = mImageRows[i+y*mFrameHeight][j+x*mFrameWidth];
				}
			}
			auto frameTemp = Frame(mFrameHeight, mFrameWidth, tempArr);
			std::cout << "dupa:" << y << std::endl;
			mFrames[y].push_back(frameTemp);
		}
	}
}


// Image::Image(Vector2d<size_t> framesize, double** image)
// {
// 	mHeight = framesize.x;
// 	mHeight = framesize.y;
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

Frame Image::getFrame(int y, int x)
{
	auto a = mFrames[y];
	return a[x];
}

double* Image::getImage()
{

}

Vector2d<size_t> Image::getSize()
{

}

Vector2d<size_t> Image::getFrameSize()
{
	return Vector2d<size_t>(mHeight / mFrameHeight,  mWidth / mFrameWidth);
}

void Image::printImage()
{
	for(int y = 0; y < mHeight; y++)
	{
		for(int x = 0; x < mWidth; x++)
		{
			std::cout << mImageRows[y][x] << ", ";
		}
		std::cout << std::endl;
	}
}

void Image::printFlat()
{
	for(int i = 0; i < mHeight*mWidth; i++)
	{
		std::cout << mImage[i] << ", ";
	}
	std::cout << std::endl;
}



int main()
{
	double a[16] {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

	Vector2d<size_t> frameSize(4,1);
	Vector2d<size_t> imageSize(4,4);
	Image image(imageSize, frameSize, a);

	image.printImage();
	image.printFlat();

	std::cout << "=================================\n";
	auto h = image.getFrameSize().x;
	auto w = image.getFrameSize().y;
	std::cout <<  h << ", " << w << std::endl;

	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			std::cout << image.getFrame(i,j) << std::endl;
		}
	}

}
