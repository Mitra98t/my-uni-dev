struct N
{
    int mat;
    struct N *next;
};
typedef struct N Stud;
typedef Stud *ANONIMI;

void add_end(ANONIMI *, int);
int RecLength(ANONIMI);
void RecStampaInversa(ANONIMI);
void RecStampa(ANONIMI);
void CancellaMultipli(ANONIMI *, int n);
int firstPari(ANONIMI);
int firstDispari(ANONIMI);