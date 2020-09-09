#include "frame.hpp"

#include <iostream>

Frame::Frame(size_t height, size_t width, double *frame)
:mHeight(height), mWidth(width)
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

	std::copy(frame.mFrame, frame.mFrame+mSize, mFrame);
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
