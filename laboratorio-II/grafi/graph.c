#include "graph.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Graph loadGraph(char *file)
{
    Graph g;
    g.Num = 0;
    g.nodes = NULL;

    FILE *f = fopen(file, "r");

    if (f)
    {
        fscanf(f, "%d", &g.Num);
        g.nodes = (Node *)malloc(g.Num * sizeof(Node));
        if (g.nodes)
        {
            for (int i = 0; i < g.Num; i++)
            {
                fscanf(f, "%d", g.nodes[i].lable);
                g.nodes[i].edges = NULL;
            }
            while (!feof(f))
            {
                int n1, n2, n1Idx, n2Idx;
                float peso;

                fscanf(f, "%d %d %d", &n1, &n2, &peso);
                if (!feof(f))
                {
                    //Aggiungo arco
                    for (int i = 0; i < g.Num; i++)
                    {
                        if (g.nodes[i].lable == n1)
                        {
                            n1Idx = i;
                        }
                        if (g.nodes[i].lable == n2)
                        {
                            n2Idx = i;
                        }
                    }
                    //Metto arco a 2 direzioni perchè non è orientato
                    addEdge(&g.nodes[n1Idx].edges, n2Idx, peso);
                    addEdge(&g.nodes[n2Idx].edges, n1Idx, peso);
                    g.EdgesNum++;
                }
            }
        }
        else
        {
            printf("Fine memoria");
            exit(0);
        }
        fclose(f);
    }
    else
    {
        perror("Errore in apertura file");
    }

    return g;
}

void addEdge(Edge **adjList, int n, float peso)
{
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    if (newEdge)
    {
        newEdge->neigh = n;
        newEdge->next = *adjList;
        newEdge->peso = peso;
        *adjList = newEdge;
    }
    else
    {
        printf("Fine memoria");
        exit(0);
    }
}

int *dfs(Graph g, int start, int *hasCycles, int *CCCount)
{
    Stack *s = NULL;
    int finished = 0;
    int ris[] = malloc(g.Num * sizeof(int));
    int risCount = 0;

    int visited[g.Num];
    for (int i = 0; i < g.Num; i++)
    {
        visited[i] = 0;
    }
    if (hasCycles)
    {
        hasCycles = 0; //non sono sicuro del valore (0 o 1) -A
    }
    push(&s, start);
    (*CCCount) = 1;
    while (!finished)
    {
        while (s)
        {
            int node = pop(&s);
            if (!visited[node])
            {
                // Qui NON HO un ciclo
                // Visito il nodo per la prima volta
                visited[node] = 1;
                ris[risCount] = node;
                risCount++;
            }
            else
            {
                // Qui HO un ciclo
                if (hasCycles)
                {
                    hasCycles = 1;
                }
            }
            Edge *edges = g.nodes[node].edges;
            while (edges)
            {
                if (!visited[edges->neigh])
                    push(edges->neigh, &s);
                edges = edges->next;
            }
        }
        int i = 0;
        while (i < g.Num && visited[i])
        {
            i++;
        }
        if (i == g.Num)
            finished = 1;
        else
        {
            if (CCCount)
                (*CCCount)++;
            push(i, &s);
        }
    }
}

int hasCycles(Graph g)
{
    int res;
    dfs(g, 0, &res, NULL);
    return res;
}

int isConnected(Graph g)
{
    int res;
    dfs(g, 0, NULL, &res);
    return res == 1;
}

int isTree(Graph g)
{
    int conn, cycl;
    dfs(g, 0, &cycl, &conn);
    return (cycl == 0) && (conn == 1);
}