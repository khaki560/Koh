#include <string>
#include <iostream>


#include "koh.hpp"
#include "pngWriter.hpp"
#include "pngReader.hpp"
#include "pngMode.hpp"
#include "image.hpp"
#include "utils.hpp"


struct Parameters
{
	std::string path;
	std::string outPath;
	Vector2d<size_t> size;
	double learningRate;
	unsigned int epochs;
	Vector2d<size_t> frameSize;
	unsigned int numberOftrainSamples; // or percentage
};

Parameters parseArgs(int args, char argv[]);


int main(int args, char* argv[])
{
	int *a = nullptr;
	std::cout << "HellowWord" << std::endl;

	// Parse arguments
	// Parameters params = parseArgs(args, argv);

	Parameters params;

	params.path = "..\\images\\lena.png";
	params.outPath = "a.png";
	Vector2d<size_t> b(4,4);
	// params.frameSize = a;

	// Read Png
	PngMode mode = PngMode::GREY;
	PngReader pngReader = PngReader();
	// std::cout << (pngReader.open(params.path) ? "hura" : "nie dziala") << std::endl;
	if(pngReader.open(params.path))
	{
		FrameImage startImage = pngReader.getImage(b);
		std::cout << startImage.getImage()[0];

		// // training Kohonen network
		// auto numberOfInputs = params.frameSize.x + params.frameSize.y;
		// Koh koh = Koh(params.koh.size, params.koh.learningRate, params.koh.epochs, numberOfInputs);
		// koh.train(startImage, params.numberOftrainSamples);
		// Image newImage = koh.convert(startImage);
		FrameImage newImage = std::move(startImage);


		// //saving png created by kohonen
		PngWriter pngWriter = PngWriter();
		pngWriter.save(params.outPath, newImage, mode);
	}
	else
	{
		std::cout << "Coudn't open " << params.path;
	}


	return 0;
}
