<<<<<<< HEAD
#include <stdlib.h>
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
=======
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
>>>>>>> f8f5a45ff5cd7c7c22afc6db0006c8a087e20b12
};