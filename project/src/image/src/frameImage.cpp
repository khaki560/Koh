#include "frameImage.hpp"

#include <algorithm>
#include <iostream>

#include "image.hpp"

#include <stdio.h>
#include <string.h>

FrameImage::FrameImage()
:Image(), mFrameHeight(0), mFrameWidth(0), mFrameSize(0), mNumberOfFramesX(0), mNumberOfFramesY(0)
{
}


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


	for(unsigned int i = 0; i < mNumberOfFramesY; i++)
	{
		std::vector<Frame> tmp;
		mFrames.push_back(tmp);
	}

	const size_t d1 = mNumberOfFramesX*mNumberOfFramesY;
	const size_t d2 = mFrameHeight;
	const size_t d3 = mFrameWidth;
	double *tmp = new double[d1 * d2 * d3];

	for(unsigned int i = 0; i < mImageSize; i++)
	{
		int y = i / mImageWidth;
		int x = i % mImageWidth;

		int frameNumber = (y / mFrameHeight) * mNumberOfFramesX + x / mFrameWidth;
		int frameY = (i / mImageWidth ) %  mFrameHeight;
		int frameX = i % mFrameWidth;


		tmp[frameNumber + d2 * (frameY + d3 * frameX)] = mImageRows[y][x];
	}

	for(unsigned int i = 0; i < mNumberOfFramesX*mNumberOfFramesY; i++)
	{
		auto frameTemp = Frame(mFrameHeight, mFrameWidth, &tmp[i]);
		mFrames[i/mNumberOfFramesX].push_back(frameTemp);
	}
}


FrameImage::FrameImage(std::vector<std::vector<Frame>> frames)
:mFrames(frames)
{
	auto frame = frames[0][0];
	mNumberOfFramesY = frames.size();
	mNumberOfFramesX = frames[0].size();
	mFrameHeight = frame.getHeight();
	mFrameWidth = frame.getWidth();
	mFrameSize = frame.getSize();

	mImageHeight = mNumberOfFramesY * mFrameHeight;
	mImageWidth = mNumberOfFramesX * mFrameWidth;
	mImageSize = mImageHeight * mImageWidth;

	mImage = new double[mImageSize];
	mImageRows = new double*[mImageHeight];
	for(int y = 0; y < mImageHeight; y++)
	{
		mImageRows[y] = &mImage[y*mImageWidth];
	}

	for(int y = 0; y < mImageHeight; y++)
	{
		for(int x = 0; x < mImageWidth; x++)
		{
			int frameY = y / mFrameHeight;
			int frameX = x / mFrameWidth;
			mImageRows[y][x] =  mFrames[frameY][frameX].next();
		}
	}
}

FrameImage::FrameImage(const FrameImage& image)
:Image(image)
{
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
	swap(*this, image);
}

FrameImage FrameImage::operator=(FrameImage image)
{
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

	first.mFrames.swap(second.mFrames);
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

std::vector<std::vector<Frame>>FrameImage::getAllFrames()
{
	return mFrames;
}

Frame FrameImage::getFrame(int y, int x)
{
	auto a = mFrames[y];
	return a[x];
}


// void print(FrameImage* image)
// {
// 	auto h = image->getNumberOfFrames().el1;
// 	auto w = image->getNumberOfFrames().el2;
// 	std::cout << "h = " <<  h << ", w = " << w << std::endl;

// 	for(int i = 0; i < h; i++)
// 	{
// 		for(int j = 0; j < w; j++)
// 		{
// 			std::cout << image->getFrame(i,j) << std::endl;
// 		}
// 	}
// }

// int main()
// {
// 	double a[16] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3};
// 	Vector2d<size_t> b(4,4);
// 	// Vector2d<size_t> b1(2,1);
// 	// Vector2d<size_t> b1(4,1);
// 	// Vector2d<size_t> b1(2,2);
// 	// Vector2d<size_t> b1(1,2);
// 	// Vector2d<size_t> b1(1,4);
// 	// Vector2d<size_t> b1(4,4);
// 	Vector2d<size_t> b1(1,1);

// 	std::cout << "======================= C ===================" << std::endl;
// 	FrameImage c(b, b1, a);
// 	std::cout << "C:" << std::endl;
// 	c.printImage();
// 	print(&c);


// 	FrameImage d(c.getAllFrames());
// 	std::cout << "D:" << std::endl;
// 	d.printImage();
// 	print(&d);


// 	// std::cout << "======================= d ===================" << std::endl;
// 	// FrameImage d(c);
// 	// std::cout << "C:" << std::endl;
// 	// c.printImage();
// 	// print(&c);
// 	// std::cout << "D:" << std::endl;
// 	// d.printImage();
// 	// print(&d);


// 	// std::cout << "======================= E ===================" << std::endl;
// 	// FrameImage e(std::move(c));
// 	// std::cout << "C:" << std::endl;
// 	// c.printImage();
// 	// print(&c);
// 	// std::cout << "D:" << std::endl;
// 	// d.printImage();
// 	// print(&d);
// 	// std::cout << "E:" << std::endl;
// 	// e.printImage();
// 	// print(&e);


// 	// std::cout << "======================= F ===================" << std::endl;
// 	// FrameImage f = d;
// 	// std::cout << "C:" << std::endl;
// 	// c.printImage();
// 	// print(&c);
// 	// std::cout << "D:" << std::endl;
// 	// d.printImage();
// 	// print(&d);
// 	// std::cout << "E:" << std::endl;
// 	// e.printImage();
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
// }
