#include "functions.h"

int main(void)
{
	sample* samples = NULL;
	int maximum = 0;
	int minimum = maximum;

	read(&samples);

	printf("sepLen\tsepWid\tpetLen\tpetWid\n");

	for (int i = 0; i < numSamples; i++)
	{
		printf("%.1f\t%.1f\t%.1f\t%.1f\t%d\n", samples[i].sepal.length, samples[i].sepal.width, samples[i].petal.length, samples[i].petal.width, samples[i].species);
	}
	free(samples);

	return 0;
}