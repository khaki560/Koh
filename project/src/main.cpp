#include <string>
#include <iostream>


#include "koh.hpp"
#include "pngWriter.hpp"
#include "pngReader.hpp"
#include "pngMode.hpp"
#include "image.hpp"
#include "utils.hpp"



struct KohParameters
{
	Vector2d<unsigned int> size;
	double learningRate;
	unsigned int epochs;
};

struct Parameters
{
	std::string path;
	std::string outPath;
	KohParameters koh;
	Vector2d<unsigned int> frameSize;
	unsigned int numberOftrainSamples; // or percentage
};

Parameters parseArgs(int args, char argv[]);


int main(int args, char* argv[])
{
	int *a = nullptr;
	std::cout << "HellowWord" << std::endl;

	// Parse arguments
	// Parameters params = parseArgs(args, argv);

	// // Read Png
	// PngMode mode = PngMode::GREY;
	// PngReader pngReader = PngReader();
	// pngReader.open(params.path, mode);
	// Image startImage = pngReader.getImage(params.frameSize);

	// // training Kohonen network
	// auto numberOfInputs = params.frameSize.x + params.frameSize.y;
	// Koh koh = Koh(params.koh.size, params.koh.learningRate, params.koh.epochs, numberOfInputs);
	// koh.train(startImage, params.numberOftrainSamples);
	// Image newImage = koh.convert(startImage);


	// //saving png created by kohonen
	// PngWriter pngWriter = PngWriter();
	// pngWriter.save(params.outPath, newImage, mode);

	return 0;
}
