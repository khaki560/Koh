#include "frame.hpp"
#include <iostream>


Frame::Frame()
:mHeight(0), mWidth(0), mSize(0), mFrame(nullptr), mCurrentIndex(0)
{

}

Frame::Frame(size_t height, size_t width, double *frame)
:mHeight(height), mWidth(width), mCurrentIndex(0)
{
	mSize = mHeight*mWidth;
	mFrame = new double[mSize];
	std::copy(frame, frame+mSize, mFrame);
}

Frame::Frame(const Frame& frame)
{
	mHeight = frame.mHeight;
	mWidth = frame.mWidth;
	mSize = frame.mSize;
	mFrame = new double[mSize];
	mCurrentIndex = frame.mCurrentIndex;
	std::copy(frame.mFrame, frame.mFrame+mSize, mFrame);
}

Frame::Frame(Frame&& frame)
:Frame()
{
	swap(*this, frame);
}

Frame Frame::operator=(Frame frame)
{
	swap(*this, frame);
	return *this;
}

void swap(Frame& first, Frame& second)
{
	using std::swap;

	swap(first.mHeight, second.mHeight);
	swap(first.mWidth, second.mWidth);
	swap(first.mSize, second.mSize);
	swap(first.mFrame, second.mFrame);
	swap(first.mCurrentIndex, second.mCurrentIndex);
}

size_t Frame::getHeight() const
{
	return mHeight;
}
size_t Frame::getWidth() const
{
	return mWidth;
}

Frame::~Frame()
{
	delete[] mFrame;
}

double Frame::operator[](int idx) const
{
	return mFrame[idx];
}

size_t Frame::getSize() const
{
	return mSize;
}

std::ostream& operator<<(std::ostream& os, const Frame& frame)
{
	auto a = frame.getSize();
	for(int i = 0; i < a; i++)
	{
		os << frame[i] << ", ";
	}
	return os;
}

double Frame::next()
{
	int i = mCurrentIndex;
	if(++mCurrentIndex >= mSize)
	{
		mCurrentIndex = 0;
	}
	return mFrame[i];
}

int Frame::nextI()
{
	return mCurrentIndex;
}
void  Frame::reset()
{
	mCurrentIndex = 0;
}
