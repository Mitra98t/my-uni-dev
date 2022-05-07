struct N{
  double v;
  struct N * next;
};
typedef struct N Node;
typedef Node * List;

void insertOrd(List*, double);
void insertOrdRec(List*, double);
void printList(List );
void freeListR(List* );
