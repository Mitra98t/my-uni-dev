typedef struct e
{
    int neigh;
    float peso;
    struct e *next;
} Edge;

typedef struct
{
    int label;
    Edge *edges;
} Node;

typedef struct
{
    Node *nodes;
    int Num;
    int EdgesNum;
} Graph;

typedef struct
{
    int n1;
    int n2;
    float peso;
} SimpleEdge;

void printGraph(Graph);

Graph loadGraph(char *);

void addEdge(Edge **, int, float);
void removeEdge(Edge **, int);

int *dfs(Graph, int, int *, int *);

int hasCycles(Graph);
int isConnected(Graph);
int isTree(Graph);

Graph kruskal(Graph);
int compareEdges(const void *, const void *);

void freeEdges(Edge **);
void freeGraph(Graph);