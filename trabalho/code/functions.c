#include "functions.h"

float distance(sample p, sample q)
{
    return sqrt(pow((p.petal.length - q.petal.length), 2) + pow((p.petal.width - q.petal.width), 2) + pow((p.sepal.length - q.sepal.length), 2) + pow((p.sepal.width - q.sepal.width), 2));
}

float normalize(float x, float maximum, float minimum)
{
	return (x - minimum) / (maximum - minimum);
}

float **table(graph *descriptor)
{
	int m = descriptor -> order;
	float **distances = (float **) malloc(m * sizeof(float *));
	for(int i = 0; i < m; i++) distances[i] = (float *) malloc(m * sizeof(float));

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

	return distances;
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
				addEdge(descriptor, i, j);
				addEdge(descriptor, j, i);
			}
		}
	}
}

void superLink(graph *descriptor)
{
	int m = descriptor -> order;
	float distances[150][150];

	float d = distance(descriptor -> nodes[0].sample, descriptor -> nodes[1].sample);
	float maximum = d;
	float minimum = d;

	for(int i = 0; i < m; i++)
	{
		for(int j = i + 1; j < m; j++)
		{
			d = distance(descriptor -> nodes[i].sample, descriptor -> nodes[j].sample);
			
			if(d > maximum) maximum = d;
			if(d < minimum) minimum = d;
			
			distances[i][j] = distances[j][i] = d;
			distances[j][i] = d;
		}
	}

	for(int i = 0; i < m; i++)
	{
		for(int j = i; j < m; j++)
		{
			float n = normalize(distances[i][j], maximum, minimum);
			
			distances[i][j] = n;
			distances[j][i] = n;
		}
	}

	for(int i = 0; i < m; i++)
	{
		for(int j = i + 1; j < m; j++)
		{
			if(distances[i][j] < bound)
			{
				addEdge(descriptor, i, j);
				addEdge(descriptor, j, i);
			}
		}
	}
}

void read(graph *descriptor)
{
	FILE *dataset = fopen("data/dataset.csv", "r");

	if(!dataset)
	{
		printf("Erro ao carregar arquivo.\n");
		exit(-1);
	}

	char* species = (char*) malloc(sizeof(char*));
	char* trash = (char*) malloc(sizeof(char) * 100);

	fgets(trash, 100, dataset);
	free(trash);

	while(!feof(dataset))
	{
		sample s = createSample();
		fscanf(dataset, "%f,%f,%f,%f,%s\n", &s.sepal.length, &s.sepal.width, &s.petal.length, &s.petal.width, species);

		if (strcmp(species, "\"Setosa\"") == 0)
		{
			s.species = SETOSA;
		}

		else if (strcmp(species, "\"Versicolor\"") == 0)
		{
			s.species = VERSICOLOUR;
		}

		else if (strcmp(species, "\"Virginica\"") == 0)
		{
			s.species = VIRGINICA;
		}

		else
		{
			printf("Especie nao reconhecida. Abortando.\n");
			exit(-1);
		}

		addNode(descriptor, s);
	}

	fclose(dataset);
	free(species);
}

void print(graph* graph)
{
	printf("%i\n", graph->order);

	for(int i = 0; i < graph -> order; i++)
	{
		for(edge *navigator = graph -> nodes[i].edges; navigator != NULL; navigator = navigator -> next)
		{
			if(navigator -> node > i)
			{
				printf("%i -- %i", i, navigator -> node);
				printf("\n");
			}
		}
	}
}

void saveTxt(graph* graph)
{
	FILE *fptr = fopen("data/graph.txt", "w+");
	if (fptr == NULL)
	{
		printf("Erro ao carregar arquivo.\n");
		exit(-1);
	}
	fprintf(fptr, "%d\n", graph->order);

	for(int i = 0; i < graph -> order; i++)
	{
		for(edge *navigator = graph -> nodes[i].edges; navigator != NULL; navigator = navigator -> next)
		{
			if(navigator -> node > i)
			{
				fprintf(fptr, "%d %d\n", i, navigator -> node);
			}
		}
	}
	fclose(fptr);
}

void plot(graph *descriptor)
{
	FILE *plot = fopen("data/iris.dot", "w+");

	fprintf(plot, "graph iris\n{");

	char *colors[3];
	colors[SETOSA] = "gold";
	colors[VERSICOLOUR] = "green";
	colors[VIRGINICA] = "dodgerblue";

	for(int i = 0; i < descriptor -> order; i++)
	{
		fprintf(plot, "\n\tnode [shape = circle, style = filled, color = ");
		if(descriptor -> nodes[i].sample.species == SETOSA) fprintf(plot, "%s", colors[SETOSA]);
		else if(descriptor -> nodes[i].sample.species == VERSICOLOUR) fprintf(plot, "%s", colors[VERSICOLOUR]);
		else if(descriptor -> nodes[i].sample.species == VIRGINICA) fprintf(plot, "%s", colors[VIRGINICA]);
		fprintf(plot, "]; %i;", i);
	}

	fprintf(plot, "\n");

	for(int i = 0; i < descriptor -> order; i++)
	{
		for(edge *navigator = descriptor -> nodes[i].edges; navigator != NULL; navigator = navigator -> next)
		{
			if(navigator -> node > i)
			{
				fprintf(plot, "\n");
				fprintf(plot, "\t%i -- %i", i, navigator -> node);
			}
		}
	}

	fprintf(plot, "\n");
	fprintf(plot, "}");

	fclose(plot);
}