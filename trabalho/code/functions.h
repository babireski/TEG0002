#include "graph.h"
#define bound 0.12
#define numSamples 150

float distance(sample p, sample q);

float normalize(float x, float maximum, float minimum);

float **table(graph *descriptor);

void link(graph *descriptor, float **distances);

void superlink(graph *descriptor);

void read(graph *descriptor);

void print(graph* graph);

void saveTxt(graph* graph);

void plot(graph *descriptor);