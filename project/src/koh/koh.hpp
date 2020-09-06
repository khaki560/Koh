#ifndef KOH_HPP
#define KOH_HPP

#include "image.hpp"
#include "utils.hpp"

class Koh
{
private:
public:
	Koh(Vector2d<unsigned int>, double learningRate, unsigned int epochs, unsigned int numberOfInputs);
	void train(Image image, unsigned int numberOfSamples);
	Image convert(Image image);
};

#endif //NEURON_HPP
