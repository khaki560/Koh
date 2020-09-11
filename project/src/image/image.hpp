#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "frame.hpp"
#include "utils.hpp"
#include <vector>

class Image
{
protected:
	size_t mImageHeight;
	size_t mImageWidth;
	double *mImage;
	double **mImageRows;


public:
	Image(Vector2d<size_t> imageSize, double* image);
	// Image(Vector2d<size_t> frameSize, double** image);
	Image(const Image& image);
	Image(Image&& image);
	~Image();

	Vector2d<size_t> getSize();
	double* getImage();


	void printImage();
	void printFlat();

};

#endif //IMAGE_HPP
