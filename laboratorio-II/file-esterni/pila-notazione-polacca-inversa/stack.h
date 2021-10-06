#define N 100

typedef struct {
  int elements[N]; 
  int n;
} Stack;

void push (int, Stack*);
int pop (Stack*);
int top (Stack);
void empty(Stack*);
void print(Stack);
