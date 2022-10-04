#include "functions.h"
#include <stdlib.h>

float distance(sample p, sample q)
{
	float square = 0;
	square = square + (p.petal.length + q.petal.length) * (p.petal.length + q.petal.length);
	square = square + (p.sepal.length + q.sepal.length) * (p.sepal.length + q.sepal.length);
	square = square + (p.petal.width + q.petal.width) * (p.petal.width + q.petal.width);
	square = square + (p.sepal.width + q.sepal.width) * (p.sepal.width + q.sepal.width);

	return sqrt(square);
}

float normalize(float x, float maximum, float minimum)
{
	return (x - minimum) / (maximum - minimum);
}

void table(graph *descriptor)
{
	int m = descriptor -> order;
	float distances[m][m];

	float d = distance(descriptor -> nodes[0].sample, descriptor -> nodes[0].sample);
	float maximum = d;
	float minimum = d;

	for(int i = 0; i < m; i++)
	{
		for(int j = i + 1; j < m; j++)
		{
			d = distance(descriptor -> nodes[i].sample, descriptor -> nodes[j].sample);
			
			if(d > maximum) maximum = d;
			if(d < minimum) minimum = d;
			
			distances[i][j] = d;
			distances[j][i] = d;
		}
	}

	for(int i = i; i < m; i++)
	{
		for(int j = i; j < m; j++)
		{
			float n = normalize(distances[i][j], maximum, minimum);
			
			distances[i][j] = n;
			distances[j][i] = n;
		}
	}
}

void link(graph *descriptor, float **distances)
{
	int m = descriptor -> order;

	for(int i = 0; i < m; i++)
	{
		for(int j = i + 1; j < m; j++)
		{
			if(distances[i][j] < bound)
			{
				add_edge(descriptor, i, j);
				add_edge(descriptor, j, i);
			}
		}
	}
}

void plot(graph *descriptor)
{
	FILE *plot = fopen("data/iris.gv", "w+");
	if (plot == NULL) {
		printf("Erro ao carregar iris.gv\n");
		exit(-1);
	}

	fprintf(plot, "graph iris");
	fprintf(plot, "\n");
	fprintf(plot, "{");
	fprintf(plot, "\n");

	char *colors[3];
	colors[SETOSA] = "gold";
	colors[VERSICOLOUR] = "green";
	colors[VIRGINICA] = "dodgerblue";

	for(int i = 0; i < descriptor -> order; i++)
	{
		fprintf(plot, "\n");
		if(descriptor -> nodes[i].sample.species == SETOSA) fprintf(plot, "node [shape = circle style = filled, color %s; %i;", colors[SETOSA], i);
		else if(descriptor -> nodes[i].sample.species == VERSICOLOUR) fprintf(plot, "node [shape = circle style = filled, color %s; %i;", colors[VERSICOLOUR], i);
		else if(descriptor -> nodes[i].sample.species == VIRGINICA) fprintf(plot, "node [shape = circle style = filled, color %s; %i;", colors[VIRGINICA], i);
	}

	fprintf(plot, "\n");

	for(int i = 0; i < descriptor -> order; i++)
	{
		for(edge *navigator = descriptor -> nodes[i].edges; navigator != NULL; navigator = navigator -> next)
		{
			if(navigator -> node > i)
			{
				fprintf(plot, "\n");
				fprintf(plot, "%i -- %i", i, navigator -> node);
			}
		}
	}

	fprintf(plot, "\n");
	fprintf(plot, "}");

	fclose(plot);
}

sample* newSamples()
{
	sample* samples = (sample *) malloc(numSamples * sizeof(sample));

	return samples;
}

// All the samples read will be stored in samples pointer, which
// will be changed by reference, and while reading the database,
void readCsv(sample **samples)
{
	*samples = newSamples();
	FILE *dataset = fopen("data/dataset.csv", "r");

	if(dataset == NULL)
	{
		printf("Erro ao carregar dataset.csv\n");
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
	FILE *fptr = fopen("data/graph.txt", "w+");
	if (fptr == NULL)
	{
		printf("Erro ao carregar graph.txt.\n");
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
