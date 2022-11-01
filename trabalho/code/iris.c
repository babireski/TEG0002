#include "iris.h"

sample createSample()
{
	sample sample;

	sample.petal.length = 0;
	sample.sepal.length = 0;
	sample.petal.width = 0;
	sample.sepal.width = 0;
	sample.species = -1;

	return sample;
}
