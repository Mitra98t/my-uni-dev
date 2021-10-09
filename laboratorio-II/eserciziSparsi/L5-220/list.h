struct N {
    int val;
    struct N * next;
};
typedef struct N Node;
typedef Node * List;

void inserOrd(List *, int);
void print(List);