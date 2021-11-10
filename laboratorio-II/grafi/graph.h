typedef struct e
{
    int neigh;
    float peso;
    struct e *next;
} Edge;

typedef struct
{
    int lable;
    Edge *edges;
} Node;

typedef struct
{
    Node *nodes;
    int Num;
    int EdgesNum;
} Graph;

Graph loadGraph(char *);
void addEdge(Edge **, int, float);
int *dfs(Graph, int, int *, int *);
int hasCycles(Graph);
int isConnected(Graph);
int isTree(Graph);