#include "frameImage.hpp"

#include <algorithm>
#include <iostream>

#include "image.hpp"


FrameImage::FrameImage()
:Image(), mFrameHeight(0), mFrameWidth(0), mFrameSize(0), mNumberOfFramesX(0), mNumberOfFramesY(0)
{
	std::cout << "FrameImage - empty" << std::endl;
}


FrameImage::FrameImage(Vector2d<size_t> imageSize, Vector2d<size_t> frameSize, double* image)
:Image(imageSize, image)
{
	std::cout << "FrameImage - 3args" << std::endl;
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


	double tmp[mNumberOfFramesX*mNumberOfFramesY][mFrameHeight][mFrameWidth];

	for(int i = 0; i < mImageSize; i++)
	{
		int y = i / mImageWidth;
		int x = i % mImageWidth;

		int frameNumber = (y / mFrameHeight) * mNumberOfFramesX + x / mFrameWidth;
		int frameY = (i / mImageWidth ) %  mFrameHeight;
		int frameX = i % mFrameWidth;


		// std::cout << frameNumber << ", " << frameY << "," << frameX << " = " << y << "," << x << std::endl;
		tmp[frameNumber][frameY][frameX] = mImageRows[y][x];
	}

	for(int i = 0; i < mNumberOfFramesX*mNumberOfFramesY; i++)
	{
		auto frameTemp = Frame(mFrameHeight, mFrameWidth, tmp[i][0]);
		mFrames[i/mNumberOfFramesX].push_back(frameTemp);
	}


	// double tempArr[mFrameSize];
	// for(int y = 0; y < mNumberOfFramesY; y++)
	// {
	// 	for(int x = 0; x < mNumberOfFramesX; x++)
	// 	{
	// 		for(int i = 0; i / mFrameHeight; i++)
	// 		{
	// 			for(int j = 0; j < mFrameWidth; j++)
	// 			{
	// 				tempArr[i*mFrameWidth+j] = mImageRows[i+y*mFrameHeight][j+x*mFrameWidth];
	// 			}
	// 		}
	// 		auto frameTemp = Frame(mFrameHeight, mFrameWidth, tempArr);
	// 		mFrames[y].push_back(frameTemp);
	// 	}
	// }
}

FrameImage::FrameImage(const FrameImage& image)
:Image(image)
{
	std::cout << "FrameImage - copy" << std::endl;
	mFrameHeight = image.mFrameHeight;
	mFrameWidth = image.mFrameWidth;
	mFrameSize = image.mFrameSize;
	mNumberOfFramesX = image.mNumberOfFramesX;
	mNumberOfFramesY = image.mNumberOfFramesY;

	for(int i = 0; i < mNumberOfFramesY; i++)
	{
		std::vector<Frame> tmp;
		mFrames.push_back(image.mFrames[i]);
	}
}

FrameImage::FrameImage(FrameImage&& image)
:Image(std::move(image)), mFrameHeight(0), mFrameWidth(0), mFrameSize(0), mNumberOfFramesX(0), mNumberOfFramesY(0)
{
	std::cout << "FrameImage - move" << std::endl;
	swap(*this, image);
}

FrameImage FrameImage::operator=(FrameImage image)
{
	std::cout << "FrameImage - assigment" << std::endl;
	return FrameImage(image);
}

void swap(FrameImage& first, FrameImage& second)
{
	using std::swap;

	swap(first.mFrameHeight, second.mFrameHeight);
	swap(first.mFrameWidth, second.mFrameWidth);
	swap(first.mFrameSize, second.mFrameSize);
	swap(first.mNumberOfFramesX, second.mNumberOfFramesX);
	swap(first.mNumberOfFramesY, second.mNumberOfFramesY);

	for(int i = 0; i < first.mNumberOfFramesY; i++)
	{
		std::vector<Frame> tmp;
		tmp.swap(second.mFrames[i]);
		first.mFrames.push_back(tmp);
	}
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


void print(FrameImage* image)
{
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
}

int main()
{
	double a[16] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3};
	Vector2d<size_t> b(4,4);
	Vector2d<size_t> b1(1,4);

	std::cout << "======================= C ===================" << std::endl;
	FrameImage c(b, b1, a);
	std::cout << "C:" << std::endl;
	c.printImage();
	print(&c);

	// std::cout << "======================= d ===================" << std::endl;
	// FrameImage d(c);
	// std::cout << "C:" << std::endl;
	// c.printImage();
	// print(&c);
	// std::cout << "D:" << std::endl;
	// d.printImage();
	// print(&d);


	// std::cout << "======================= E ===================" << std::endl;
	// FrameImage e(std::move(c));
	// std::cout << "C:" << std::endl;
	// c.printImage();
	// print(&c);
	// std::cout << "D:" << std::endl;
	// d.printImage();
	// print(&d);
	// std::cout << "E:" << std::endl;
	// e.printImage();
	// print(&e);


	// std::cout << "======================= F ===================" << std::endl;
	// FrameImage f = d;
	// std::cout << "C:" << std::endl;
	// c.printImage();
	// print(&c);
	// std::cout << "D:" << std::endl;
	// d.printImage();
	// print(&d);
	// std::cout << "E:" << std::endl;
	// e.printImage();
	// print(&e);
	// std::cout << "F:" << std::endl;
	// f.printImage();
	// print(&f);

	// std::cout << "======================= G ===================" << std::endl;
	// FrameImage g = std::move(d);
	// std::cout << "C:" << std::endl;
	// c.printImage();
	// print(&c);
	// std::cout << "D:" << std::endl;
	// d.printImage();
	// print(&d);
	// std::cout << "E:" << std::endl;
	// e.printImage();
	// print(&e);
	// std::cout << "F:" << std::endl;
	// f.printImage();
	// print(&f);
	// std::cout << "G:" << std::endl;
	// g.printImage();
	// print(&g);
}
