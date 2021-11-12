//A==EdgesNum;
//N==Num

#include "graph.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Graph loadGraph(char *file)
{
    Graph g;
    g.Num = 0;
    g.EdgesNum = 0;
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
                fscanf(f, "%d", &g.nodes[i].label);
                g.nodes[i].edges = NULL;
            }
            while (!feof(f))
            {
                int n1, n2, n1Idx, n2Idx;
                float peso;

                fscanf(f, "%d %d %f", &n1, &n2, &peso);
                if (!feof(f))
                {
                    //Aggiungo arco
                    for (int i = 0; i < g.Num; i++)
                    {
                        if (g.nodes[i].label == n1)
                        {
                            n1Idx = i;
                        }
                        if (g.nodes[i].label == n2)
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

void removeEdge(Edge **adjList, int n)
{
    if (*adjList != NULL && (*adjList)->neigh == n)
    {
        Edge *temp = *adjList;
        *adjList = temp->next;
        free(temp);
        return;
    }
    if (*adjList != NULL)
        removeEdge(&(*adjList), n);
}

int *dfs(Graph g, int start, int *hasCycles, int *CCCount)
{
    Stack *s = NULL;
    int finished = 0;
    int *ris = (int *)malloc((g.Num) * sizeof(int));
    int risCount = 0;

    int visited[g.Num];
    for (int i = 0; i < g.Num; i++)
    {
        visited[i] = 0;
    }
    if (hasCycles)
    {
        (*hasCycles) = 0; //non sono sicuro del valore (0 o 1) -A
    }
    push(start, s);
    (*CCCount) = 1;
    while (!finished)
    {
        while (s->n > 0)
        {
            int node = pop(s);
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
                    *hasCycles = 1;
                }
            }
            Edge *edges = g.nodes[node].edges;
            while (edges)
            {
                if (!visited[edges->neigh])
                    push(edges->neigh, s);
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
            push(i, s);
        }
    }
    return ris;
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

int compareEdges(const void *a, const void *b)
{
    SimpleEdge *e1 = (SimpleEdge *)a;
    SimpleEdge *e2 = (SimpleEdge *)b;
    return e1->peso - e2->peso;
}

Graph kruskal(Graph g)
{
    Graph tree;
    tree.Num = g.Num;
    tree.EdgesNum = 0;

    tree.nodes = (Node *)malloc(sizeof(Node) * tree.Num);
    if (tree.nodes)
    {
        for (int i = 0; i < tree.Num; i++)
        {
            tree.nodes[i].label = g.nodes[i].label;
            tree.nodes[i].edges = NULL;
        }

        //creo array di archi
        SimpleEdge edges[g.EdgesNum];
        int count = 0;
        for (int i = 0; i < g.Num; i++)
        {
            Edge *e = g.nodes[i].edges;
            while (e)
            {
                if (e->neigh > i)
                {
                    edges[count].n1 = i;
                    edges[count].n2 = e->neigh;
                    edges[count].peso = e->peso;
                    count++;
                }
                e = e->next;
            }
        }
        //ordino
        qsort(edges, tree.EdgesNum, sizeof(SimpleEdge), compareEdges);

        //applico il mitico KRUSKAL

        count = 0;
        while (tree.EdgesNum < tree.Num - 1)
        {
            int i = edges[count].n1;
            int j = edges[count].n2;
            addEdge(&tree.nodes[i].edges, j, edges[count].peso);
            addEdge(&tree.nodes[j].edges, i, edges[count].peso);
            tree.EdgesNum++;
            if (hasCycles(tree))
            {
                tree.EdgesNum--;
                removeEdge(&tree.nodes[i].edges, j);
                removeEdge(&tree.nodes[j].edges, i);
            }
            count++;
        }
    }
    else
    {
        printf("errore di memoria\n");
        exit(1);
    }

    return tree;
}

void printGraph(Graph g)
{
    g = loadGraph("g1.txt");

    printf("Grafo con %d nodi: \n", g.Num);

    for (int i = 0; i < g.Num; i++)
    {
        printf("Nodo %d con vicini: \n", g.nodes[i].label);
        Edge *edges = g.nodes[i].edges;
        while (edges)
        {
            printf("%d - peso: %.2f \n", g.nodes[edges->neigh].label, edges->peso);
            edges = edges->next;
        }
    }

    printf("CONNECTED: %d\n", isConnected(g));
    // printf("HASCYCLES: %d\n", hasCycles(g));
    // printf("ISTREE: %d\n", isTree(g));
    return;
}

void freeGraph(Graph g)
{
    for (int i = 0; i < g.Num; i++)
    {
        freeEdges(&g.nodes[i].edges);
    }
    free(g.nodes);
}

void freeEdges(Edge **adjL)
{
    if (*adjL != NULL)
    {
        freeEdges(&(*adjL)->next);
        free(*adjL);
        *adjL = NULL;
    }
}