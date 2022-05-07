// garatisce l'ordine FIFO
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <queue.h>

#define NROWS 16
#define NCOLS 32
static char Tabellone[NROWS*NCOLS];
int ridx=0;
int cidx=0;
static int  N;
static int  stop;

static pthread_mutex_t mutex    = PTHREAD_MUTEX_INITIALIZER;
static int activeReaders = 0;
static int stato = -1;  // -1 iniziale,  0 lettura,  1 scrittura, 2 scrittura

typedef struct _ordering {
  pthread_cond_t ord;
  int rw;   // reader 0, writer 1
} ordering_t;

Queue_t* orderingQ;

void startRead(int id) {
  pthread_mutex_lock(&mutex);
  printf("READER%d START\n", id);
  ordering_t* o = top(orderingQ);
  if (stato > 0 || (o && o->rw == 1) ) { // c'e' uno scrittore dentro oppure davanti a me c'e' uno scrittore  
    printf("READER%d MI ACCODO\n", id);
    ordering_t* o = malloc(sizeof(ordering_t));
    pthread_cond_init(&o->ord, NULL);
    o->rw = 0;    
    if (push(orderingQ, o)<0) abort();

    while(stato > 0) {    // finche' ci sono scrittori aspetto
      pthread_cond_wait(&o->ord, &mutex);
    }
    pthread_cond_destroy(&o->ord);
    free(o);
    printf("READER%d RIPARTO\n", id);
  }
  activeReaders++;
  stato = 0;
  printf("READER%d ENTRO\n", id);
  pthread_mutex_unlock(&mutex);
}
void doneRead(int id) {
  pthread_mutex_lock(&mutex);
  activeReaders--;
  assert(activeReaders>=0);
  printf("READER%d DONE\n", id);
  if (activeReaders==0) { // sono l'ultimo lettore
    stato = -1; // resetto lo stato
    if (length(orderingQ)>0) { //  c'e' uno scrittore in coda lo faccio partire
      printf("READER%d FACCIO PARTIRE UNO SCRITTORE\n", id);
      ordering_t* o = pop(orderingQ);
      assert(o);
      assert(o->rw == 1); // c'e' un writer
      pthread_cond_signal(&o->ord);

      stato = 2; // stato scrittura
    } 
  }
  pthread_mutex_unlock(&mutex);
}

void startWrite(int id) {
  pthread_mutex_lock(&mutex);
  printf("WRITER%d START\n", id);
  if (stato >= 0) {  // c'e' uno scrittore oppure dei lettori
    printf("WRITER%d MI ACCODO\n", id);
    ordering_t* o = malloc(sizeof(ordering_t));
    pthread_cond_init(&o->ord, NULL);
    o->rw = 1;
    push(orderingQ, o);

    do {
      pthread_cond_wait(&o->ord, &mutex);  // posso essere svegliato con stato=2
      printf("WRITER%d RIPARTO con stato =%d, activerReaders=%d\n", id, stato, activeReaders);
    } while(stato == 0 || stato == 1);

    assert(stato == 2 || stato == -1);
    
    pthread_cond_destroy(&o->ord);
    free(o);
    printf("WRITER%d RIPARTO\n", id);
  }
  stato = 1;
  printf("WRITER%d ENTRO\n", id);
  pthread_mutex_unlock(&mutex);
}
void doneWriter(int id) {
  pthread_mutex_lock(&mutex);
  assert(stato == 1);
  printf("WRITER%d DONE\n", id);
  stato = -1;
  if (length(orderingQ) > 0) {
    ordering_t* o = pop(orderingQ); 
    assert(o);
    pthread_cond_signal(&o->ord);
    if (o->rw == 0) { // e' un reader
      printf("WRITER%d FACCIO PARTIRE UN LETTORE\n", id);
      stato = 0;
      
      while(1) {
	o = top(orderingQ);
	if (!o || o->rw==1) break;
	printf("WRITER%d FACCIO PARTIRE UN ALTRO LETTORE\n", id);
	pthread_cond_signal(&o->ord);
	pop(orderingQ);
      }
    } else {
      stato = 2; // <-- per dare precedenza allo scrittore in coda
      printf("WRITER%d FACCIO PARTIRE UNO SCRITTORE stato=%d\n", id, stato);
    }
  }   
  pthread_mutex_unlock(&mutex);
}

void *Reader(void* arg) {
  long id = (long)arg;

  while(stop>0) {
    startRead(id);

#if 0    
    if (id ==0) {
      clear();
      char tab[NCOLS+1];
      for(int i=0;i<NROWS;++i) {
	strncpy(tab, &Tabellone[i*NCOLS], NCOLS);
	tab[NCOLS]='\0';
	printf("%s\n", tab);
	fflush(stdout);
      }
    }
#endif    
    usleep(1000);
    
    doneRead(id);
  }
  return NULL;
}

void *Writer(void* arg) {
  long id = (long)arg;
  char myname[NCOLS];
  snprintf(myname, NCOLS, "Writer%ld", id); 
  const size_t namelen = strlen(myname);
  for(int i=0;i<N;++i) {
    startWrite(id);

    if ((NCOLS-(cidx+1)) >= namelen) {
      strncpy(&Tabellone[ridx*NCOLS+cidx],myname, namelen);
      cidx+=namelen;
      if (cidx==NCOLS) cidx=0;
    } else {
      int len = NCOLS-cidx;
      strncpy(&Tabellone[ridx*NCOLS+cidx],myname, len);
      cidx=0;
      ridx++;
      if (ridx==NROWS) ridx=0;
      strncpy(&Tabellone[ridx*NCOLS+cidx],myname+len, namelen-len);
      cidx+=(namelen-len);
    }  
    usleep(3000);

    if (i+1 == N) --stop;
    doneWriter(id);
  }

  printf("WRITER TERMINATO\n");
  
  return NULL;
}

int main(int argc, char* argv[]) {
  int R = 5;
  int W = 2;
  N = 100;
  if (argc > 1) {
    if (argc != 4) {
      fprintf(stderr, "usage: %s [#R #W N]\n", argv[0]);
      return -1;
    }
    R = atoi(argv[1]);
    W = atoi(argv[2]);
    N = atoi(argv[3]);
  }  
  // a reasonable limit 
  if (R>100) R = 100;
  if (W>100) W = 100;

  stop = W;
  orderingQ = initQueue();
  
  pthread_t* readers     = malloc(R*sizeof(pthread_t));
  pthread_t* writers     = malloc(W*sizeof(pthread_t));
  if (!readers || !writers) {
    fprintf(stderr, "not enough memory\n");
    return -1;
  }

  
  for(long i=0; i<W; ++i)
    if (pthread_create(&writers[i], NULL, Writer, (void*)i) != 0) {
      fprintf(stderr, "pthread_create Writer failed\n");
      return -1;
    }
  for(long i=0; i<R; ++i)
    if (pthread_create(&readers[i], NULL, Reader, (void*)i) != 0) {
      fprintf(stderr, "pthread_create Reader failed\n");
      return -1;
    }		
  for(long i=0;i<R; ++i)
    if (pthread_join(readers[i], NULL) == -1) {
      fprintf(stderr, "pthread_join failed\n");
    }
  for(long i=0;i<W; ++i)
    if (pthread_join(writers[i], NULL) == -1) {
      fprintf(stderr, "pthread_join failed\n");
    }
  
  free(writers);
  free(readers);
  deleteQueue(orderingQ);
  return 0;   
  
}
