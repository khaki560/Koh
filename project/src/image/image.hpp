#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "frame.hpp"
#include "utils.hpp"
#include <vector>

class Image
{
private:
	size_t mHeight;
	size_t mWidth;
	double *mImage;
	double **mImageRows;


	size_t mFrameHeight;
	size_t mFrameWidth;
	std::vector<std::vector<Frame>> mFrames;



public:
	Image(Vector2d<size_t> imageSize, Vector2d<size_t> frameSize, double* image);
	// Image(Vector2d<size_t> frameSize, double** image);
	Image(const Image& image);
	Image(Image&& image);
	~Image();

	Vector2d<size_t> getFrameSize();
	Frame getFrame(int y, int x);
	double* getImage();

	Vector2d<size_t> getSize();
	void printImage();
	void printFlat();

};

#endif //IMAGE_HPP
