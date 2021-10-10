struct N
{
    int val;
    struct N *next;
};
typedef struct N Node;
typedef Node *List;

int addTail(List *, int);
void intersecOrd(List, List, List *);
void insertOrd(List *, int);
void print(List);
