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

graph* create();

void add_node(graph *descriptor, sample sample);

void add_edge(graph *descriptor, int head, int tail);