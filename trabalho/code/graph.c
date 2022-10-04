#include "graph.h"

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
