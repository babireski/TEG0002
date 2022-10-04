#include "graph.h"
#define bound 0.3

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

void load()
{

}

void save()
{
    
}

void plot(graph *descriptor)
{
    FILE *plot = fopen("iris.gv", "w");

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