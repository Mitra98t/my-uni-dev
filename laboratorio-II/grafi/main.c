#include "graph.h"

int main(void)
{
    Graph g = loadGraph("g1.txt");

    printf("Grafo con %d nodi: \n", &g.Num);

    for (int i = 0; i < g.Num; i++)
    {
        printf("Nodo %d con vicini: ", g.nodes[i].lable);
        Edge *e = g.nodes[i].edges;

        while (e)
        {
            printf("%d (%f)", g.nodes[e->neigh].lable, e->peso);
        }
    }
    return 0;
}