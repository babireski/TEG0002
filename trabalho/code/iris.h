#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SETOSA 1
#define VERSICOLOUR 2
#define VIRGINICA 3

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