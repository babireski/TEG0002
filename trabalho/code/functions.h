#include "graph.h"
#define bound 0.3
#define numSamples 150

float distance(sample p, sample q);

float normalize(float x, float maximum, float minimum);

void table(graph *descriptor);

void link(graph *descriptor, float **distances);

void plot(graph *descriptor);

sample* newSamples();

// All the samples read will be stored in samples pointer, which
// will be changed by reference, and while reading the database,
void readCsv(sample **samples);

void printGraph(graph* graph);

void saveTxt(graph* graph);