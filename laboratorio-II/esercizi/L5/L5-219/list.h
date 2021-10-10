struct N
{
    int val;
    struct N *next;
};
typedef struct N Node;
typedef Node *List;

int addTail(List *, int);
void insertOrd(List *, int);
int produttoriaInRange(List, int, int);
void print(List);
