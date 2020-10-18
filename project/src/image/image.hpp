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
	size_t mImageSize;
	double *mImage;
	double **mImageRows;

	Image();

public:
	Image(Vector2d<size_t> imageSize, double* image);
	Image(const Image& image);
	Image(Image&& image);
	~Image();


	Image operator=(Image image);
	friend void swap(Image& first, Image& second);


	Vector2d<size_t> getSize();
	double* getImage();
	double* getImageRow(int rowNumber);


	void printImage();
	void printFlat();

};

#endif //IMAGE_HPP
