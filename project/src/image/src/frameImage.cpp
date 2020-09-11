#include "frameImage.hpp"

#include <algorithm>
#include <iostream>

#include "image.hpp"

FrameImage::FrameImage(Vector2d<size_t> imageSize, Vector2d<size_t> frameSize, double* image)
:Image(imageSize, image)
{
	mFrameHeight = frameSize.el1;
	mFrameWidth = frameSize.el2;
	mFrameSize = mFrameHeight * mFrameWidth;


	if(mImageWidth % mFrameWidth != 0 || mImageHeight % mFrameHeight != 0)
	{
		std::cerr << "Wrong frameSize" << std::endl;
	}

	mNumberOfFramesY = mImageHeight / mFrameHeight;
	mNumberOfFramesX = mImageWidth / mFrameWidth;


	for(int i = 0; i < mNumberOfFramesY; i++)
	{
		std::vector<Frame> tmp;
		mFrames.push_back(tmp);
	}



	// double tmp[mNumberOfFramesY][mNumberOfFramesX];
	// for(int y = 0; y < mImageHeight; y++)
	// {
	// 	for(int x = 0; x < mImageWidth; x++)
	// 	{
	// 		tmp[]
	// 	}
	// }


	double tempArr[mFrameSize];
	for(int y = 0; y < mNumberOfFramesY; y++)
	{
		for(int x = 0; x < mNumberOfFramesX; x++)
		{
			for(int i = 0; i < mFrameHeight; i++)
			{
				for(int j = 0; j < mFrameWidth; j++)
				{
					tempArr[i*mFrameWidth+j] = mImageRows[i+y*mFrameHeight][j+x*mFrameWidth];
				}
			}
			auto frameTemp = Frame(mFrameHeight, mFrameWidth, tempArr);
			mFrames[y].push_back(frameTemp);
		}
	}
}


FrameImage::FrameImage(const FrameImage& image)
:Image(image)
{

}

FrameImage::FrameImage(FrameImage&& image)
:Image(image)
{

}

FrameImage::~FrameImage()
{
}


Vector2d<size_t> FrameImage::getFrameSize()
{
	return Vector2d<size_t>(mFrameHeight, mFrameWidth);
}

Vector2d<size_t> FrameImage::getNumberOfFrames()
{
	return Vector2d<size_t>(mNumberOfFramesY, mNumberOfFramesX);
}


Frame FrameImage::getFrame(int y, int x)
{
	auto a = mFrames[y];
	return a[x];
}



int main()
{
	double a[16] {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

	Vector2d<size_t> frameSize(4,1);
	Vector2d<size_t> imageSize(4,4);
	FrameImage*  image = new FrameImage(imageSize, frameSize, a);

	image->printFlat();
	std::cout << "=================================\n";
	image->printImage();
	std::cout << "=================================\n";
	auto h = image->getNumberOfFrames().el1;
	auto w = image->getNumberOfFrames().el2;
	std::cout << "h = " <<  h << ", w = " << w << std::endl;

	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			std::cout << image->getFrame(i,j) << std::endl;
		}
	}

	delete image;

}
