#include "functions.h"

int main(void)
{
    sample* samples = NULL;
    int maximum = 0;
    int minimum = maximum;
    int numOfSamples = 0;

    read(&samples, &maximum, &minimum, &numOfSamples);

    printf("samples read: %d\n", numOfSamples);
    printf("sepLen\tsepWid\tpetLen\tpetWid\n");
    for (int i = 0; i < numOfSamples; i++)
    {
        printf("%.1f\t%.1f\t%.1f\t%.1f\t%d\n", samples[i].sepal.length, samples[i].sepal.width, samples[i].petal.length, samples[i].petal.width, samples[i].species);
    }

    return 0;
}