#include "functions.h"

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

void superlink(graph *descriptor)
{
	int m = descriptor -> order;
	float distances[150][150];

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
				add_edge(descriptor, i, j);
				add_edge(descriptor, j, i);
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
		sample s = create_sample();
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

		add_node(descriptor, s);
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

void plot(graph *descriptor)
{
	FILE *plot = fopen("data/iris.gv", "w+");

	fprintf(plot, "graph iris\n{\n");

	char *colors[3];
	colors[SETOSA] = "gold";
	colors[VERSICOLOUR] = "green";
	colors[VIRGINICA] = "dodgerblue";

	for(int i = 0; i < descriptor -> order; i++)
	{
		fprintf(plot, "\nnode [shape = circle, style = filled, color = ");
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
				fprintf(plot, "%i -- %i", i, navigator -> node);
			}
		}
	}

	fprintf(plot, "\n");
	fprintf(plot, "}");

	fclose(plot);
}
