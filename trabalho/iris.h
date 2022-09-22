#include <stdio.h>
#include <math.h>

#define SETOSA 1
#define VERSICOLOUR 2
#define VIRGINICA 3

typedef struct dimensions dimensions;
typedef struct sample sample;

struct sample
{
    dimensions petal;
    dimensions sepal;
    int species;
};

struct dimensions
{
    float length;
    float width;
};