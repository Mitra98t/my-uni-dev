#include "graph.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf("CONNECTED: %d\n", isConnected(g));
    printf("HASCYCLES: %d\n", hasCycles(g));
    printf("ISTREE: %d\n", isTree(g));
    return 0;
}