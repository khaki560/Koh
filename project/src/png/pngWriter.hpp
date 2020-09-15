#ifndef PNG_WRITER_HPP
#define PNG_WRITER_HPP

#include "pngMode.hpp"

class PngWriter
{
private:
public:
	void save(unsigned char path[], Image image, PngMode mode);
	void save(std::string path, Image image, PngMode mode);
};

#endif //PNG_WRITER_HPP
