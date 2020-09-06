#ifndef PNG_READER_HPP
#define PNG_READER_HPP


#include "pngMode.hpp"
#include "image.hpp"

class PngReader
{
private:
public:
	void open(std::string path);
	void open(std::string path, PngMode mode);
	void open(unsigned char path[]);
	void open(unsigned char path[], PngMode mode);

	Image getImage(Vector2d<unsigned int> frameSize);
	PngMode GetMode();
};


#endif //PNG_READER_HPP
