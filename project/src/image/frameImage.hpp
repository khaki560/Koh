#ifndef IMAGE_FRAME_HPP
#define IMAGE_FRAME_HPP

#include "image.hpp"
#include "frame.hpp"
#include "utils.hpp"

#include <vector>

class FrameImage: public Image
{
private:
	size_t mFrameHeight;
	size_t mFrameWidth;
	size_t mFrameSize;
	size_t mNumberOfFramesX;
	size_t mNumberOfFramesY;
	std::vector<std::vector<Frame>> mFrames;


public:
	FrameImage(Vector2d<size_t> imageSize, Vector2d<size_t> frameSize, double* image);

	FrameImage(const FrameImage& image);
	FrameImage(FrameImage&& image);
	~FrameImage();

	Vector2d<size_t> getFrameSize();
	Vector2d<size_t> getNumberOfFrames();
	Frame getFrame(int y, int x);
};

#endif //IMAGE_FRAME_HPP
