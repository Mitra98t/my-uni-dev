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
    int Num;
    Node *nodes;
} Graph;

Graph loadGraph(char *);
void addEdge(Edge **, int, float);
int *dfs(Graph, int);