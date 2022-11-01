#include "graph.h"

graph* create()
{
	graph *descriptor = (graph *) malloc(sizeof(graph));

	descriptor -> nodes = NULL;
	descriptor -> order = 0;

	return descriptor;
}

void addNode(graph *descriptor, sample sample)
{
	descriptor -> order += 1;
	descriptor -> nodes = (node *) realloc(descriptor -> nodes, descriptor -> order * sizeof(node));
	descriptor -> nodes[descriptor -> order - 1].sample = sample;
	descriptor -> nodes[descriptor -> order - 1].degree = 0;
	descriptor -> nodes[descriptor -> order - 1].edges = NULL;
}

void addEdge(graph *descriptor, int head, int tail)
{
	edge *newEdge = (edge *) malloc(sizeof(edge));
	newEdge -> node = tail;
	newEdge -> next = NULL;

	edge *last = descriptor -> nodes[head].edges;

	if(last)
	{
		for(; last -> next != NULL; last = last -> next);
		last -> next = newEdge;
	}

	else
	{
		descriptor -> nodes[head].edges = newEdge;
	}
}

void destroy(graph *descriptor)
{
	if(descriptor -> nodes)
	{
		for(int i = 0; i < descriptor -> order; i++)
		{
			edge *navigator = descriptor -> nodes[i].edges;

			while(navigator)
			{
				edge *previous = navigator;
				navigator = navigator -> next;
				free(previous);
			}
		}

		free(descriptor -> nodes);
	}

	free(descriptor);
}
