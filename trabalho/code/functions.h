#include "graph.h"
#define bound 0.11
#define numSamples 150

float distance(sample p, sample q);

float normalize(float x, float maximum, float minimum);

void link(graph *descriptor);

void readCsv(graph *descriptor);

void print(graph* graph);

void saveTxt(graph* graph);

void plot(graph *descriptor);

void readTxt(graph *descriptor);
