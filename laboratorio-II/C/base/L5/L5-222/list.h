struct N
{
    int val;
    struct N *next;
};
typedef struct N Node;
typedef Node *List;

int removeValue(List *, int);
int addHead(List *, int);
int addTail(List *, int);
void inserOrdCrescDup(List *, int);
void inserOrdDecrescDup(List *, int);
void fillOrdDecresc(List);
void printBR(List);
void printInLine(List);