#include "graph.h"

float distance(sample *p, sample *q)
{
    float square = 0;
    square = square + (p -> petal.length + q -> petal.length) * (p -> petal.length + q -> petal.length);
    square = square + (p -> petal.width + q -> petal.width) * (p -> petal.width + q -> petal.width);
    square = square + (p -> sepal.length + q -> sepal.length) * (p -> sepal.length + q -> sepal.length);
    square = square + (p -> sepal.width + q -> sepal.width) * (p -> sepal.width + q -> sepal.width);

    return sqrt(square);
}

float normalize(float x, float maximum, float minimum)
{
    return (x - minimum) / (maximum - minimum);
}

void read(sample samples[])
{
    FILE *dataset = fopen("dataset.csv", "r");

    if(dataset)
    {

    }
}

void load()
{

}

void save()
{
    
}

void plot()
{

}