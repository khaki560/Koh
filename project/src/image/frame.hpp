#ifndef FRAME_HPP
#define FRAME_HPP

#include <algorithm>
#include <iostream>

class Frame
{
private:
	size_t mHeight;
	size_t mWidth;
	size_t mSize;
	double* mFrame;
	int mCurrentIndex;
public:
	Frame();
	Frame(size_t height, size_t width, double *frame);
	Frame(const Frame& frame);
	Frame(Frame&& frame);
	~Frame();

	Frame operator=(Frame frame);
	friend void swap(Frame& first, Frame& second);


	size_t getSize() const;
	size_t getHeight() const;
	size_t getWidth() const;
	double operator[] (int idx) const;
	friend std::ostream& operator<<(std::ostream& os, const Frame& frame);
	double next();
	int nextI();
	void reset();
};

#endif //FRAME_HPP
