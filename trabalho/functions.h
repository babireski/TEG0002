#include "graph.h"
#include <stdio.h>

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

sample* newSamples() {
	sample* samples = (sample *) malloc(sizeof(sample*));

	return samples;
}

// All the samples read will be stored in samples pointer, which
// will be changed by reference, and while reading the database,
// the maximum and minimum will be calculated, and also changed by reference
void read(sample **samples, int *maximum, int *minimum, int *num)
{
	*samples = newSamples();
	FILE *dataset = fopen("dataset.csv", "r");

	if(dataset == NULL)
	{
		printf("Erro ao carregar arquivo.\n");
		exit(-1);
	}

	char* firstLine = (char*) malloc(sizeof(char) * 100);
	char* variety = (char*) malloc(sizeof(char*));
	float sepLen;
	float sepWid;
	float petLen;
	float petWid;

	// Discard first line
	fgets(firstLine, 100, dataset);
	free(firstLine);
	while (!feof(dataset))
	{
		if (*num > 149) {
			return;
		}
		fscanf(dataset, "%f,%f,%f,%f,%s\n", &sepLen, &sepWid, &petLen, &petWid, variety);
		samples[*num] = (sample*) malloc(sizeof(sample));
		(*samples)[*num].sepal.length = sepLen;
		(*samples)[*num].sepal.width = sepWid;
		(*samples)[*num].petal.length = petLen;
		(*samples)[*num].petal.width = petWid;
		if (strcmp(variety, "\"Setosa\"") == 0)
		{
			(*samples)[*num].species = 1;
		}
		else if (strcmp(variety, "\"Versicolor\"") == 0)
		{
			(*samples)[*num].species = 2;
		}
		else if (strcmp(variety, "\"Virginica\"") == 0)
		{
			(*samples)[*num].species = 3;
		}
		else
		{
			printf("Especie nao reconhecida. Abortando\n");
			exit(-1);
		}
		// mallocating a bit wrong, need to find out why.
		// the rest aparently is working fine
		*num = *num + 1;
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