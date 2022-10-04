#include "graph.h"
#include <stdio.h>
#define numSamples 150

float distance(sample *p, sample *q)
{
	float square = 0;
	square = square + (p -> petal.length + q -> petal.length) * (p -> petal.length + q -> petal.length);
	square = square + (p -> petal.width + q -> petal.width) * (p -> petal.width + q -> petal.width);
	square = square + (p -> sepal.length + q -> sepal.length) * (p -> sepal.length + q -> sepal.length);
	square = square + (p -> sepal.width + q -> sepal.width) * (p -> sepal.width + q -> sepal.width);

	return (square);
}

float normalize(float x, float maximum, float minimum)
{
	return (x - minimum) / (maximum - minimum);
}

sample* newSamples()
{
	sample* samples = (sample *) malloc(numSamples * sizeof(sample));

	return samples;
}

// All the samples read will be stored in samples pointer, which
// will be changed by reference, and while reading the database,
// the maximum and minimum will be calculated, and also changed by reference
void readCsv(sample **samples)
{
	*samples = newSamples();
	FILE *dataset = fopen("dataset.csv", "r");

	if(dataset == NULL)
	{
		printf("Erro ao carregar arquivo.\n");
		exit(-1);
	}

	int num = 0;
	char* firstLine = (char*) malloc(sizeof(char) * 100);
	char* variety = (char*) malloc(sizeof(char*));
	int species;
	float sepLen;
	float sepWid;
	float petLen;
	float petWid;

	// Discard first line
	fgets(firstLine, 100, dataset);
	free(firstLine);
	while (!feof(dataset))
	{
		fscanf(dataset, "%f,%f,%f,%f,%s\n", &sepLen, &sepWid, &petLen, &petWid, variety);
		(*samples)[num].sepal.length = sepLen;
		(*samples)[num].sepal.width = sepWid;
		(*samples)[num].petal.length = petLen;
		(*samples)[num].petal.width = petWid;
		if (strcmp(variety, "\"Setosa\"") == 0)
		{
			species = 1;
		}
		else if (strcmp(variety, "\"Versicolor\"") == 0)
		{
			species = 2;
		}
		else if (strcmp(variety, "\"Virginica\"") == 0)
		{
			species = 3;
		}
		else
		{
			printf("Especie nao reconhecida. Abortando\n");
			exit(-1);
		}
		(*samples)[num].species = species;
		num += 1;
	}
	free(variety);
}

void load()
{

}

void printGraph(graph* graph)
{

	for (int i = 0; i < graph->order; i++)
	{
		printf("v[%d] --> ", i);
		if (graph->nodes[i].edges->next == NULL)
		{
			printf("%d", graph->nodes[i].edges->node);
		}
		printf("%d -->", graph->nodes[i].edges->node);
		printf("\n");
	}
}

void saveTxt(graph* graph)
{
	FILE *fptr = fopen("grafo.txt", "w+");
	if (fptr == NULL)
	{
		printf("Erro ao carregar arquivo.\n");
		exit(-1);
	}
	fprintf(fptr, "%d\n", numSamples);

	for (int i = 0; i < graph->order; i++)
	{
		fprintf(fptr, "%d", i);
		for (int j = i + 1; j < graph->order; j++)
		{
			if (graph->nodes[i].edges->node < graph->nodes[i].edges->next->node) {
				fprintf(fptr, "%d %d\n", graph->nodes[i].edges->node, graph->nodes[i].edges->next->node);
			}
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

void plot()
{

}