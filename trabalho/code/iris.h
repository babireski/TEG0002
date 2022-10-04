#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SETOSA 0
#define VERSICOLOUR 1
#define VIRGINICA 2

typedef struct dimensions dimensions;
typedef struct sample sample;

struct dimensions
{
	float length;
	float width;
};

struct sample
{
	dimensions petal;
	dimensions sepal;
	int species;
};

sample createSample();