<<<<<<< HEAD
#include "iris.h"

typedef struct graph graph;
typedef struct node node;
typedef struct edge edge;

struct graph
{
    node *nodes;
    int order;
};

struct node
{
    sample sample;
    edge *edges;
    int degree;
};

struct edge
{
    int node;
    edge *next;
};

graph* create()
{
    graph *descriptor = (graph *) malloc(sizeof(graph));

    descriptor -> nodes = NULL;
    descriptor -> order = 0;

    return descriptor;
}

void add_node(graph *descriptor, sample sample)
{
    descriptor -> order += 1;
    descriptor -> nodes = (node *) realloc(descriptor -> nodes, descriptor -> order * sizeof(node));
    descriptor -> nodes[descriptor -> order - 1].sample = sample;
    descriptor -> nodes[descriptor -> order - 1].degree = 0;
    descriptor -> nodes[descriptor -> order - 1].edges = NULL;
}

void add_edge(graph *descriptor, int head, int tail)
{
    edge *new_edge = (edge *) malloc(sizeof(edge));
    new_edge -> node = tail;
    new_edge -> next = NULL;
    edge *last;
    for(last = descriptor -> nodes[head].edges; last != NULL; last = last -> next);
    last -> next = new_edge;
}
=======
#include "iris.h"

typedef struct graph graph;
typedef struct node node;
typedef struct edge edge;

struct graph
{
	node *nodes;
	int order;
};

struct node
{
	sample sample;
	edge *edges;
	int degree;
};

struct edge
{
	int node;
	edge *next;
};
>>>>>>> f8f5a45ff5cd7c7c22afc6db0006c8a087e20b12
