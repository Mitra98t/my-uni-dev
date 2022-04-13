#define _POSIX_C_SOURCE 200112L
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

static int  N;
static int  stop;
static unsigned long t0; // tempo iniziale

static inline unsigned long getusec() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (unsigned long)(tv.tv_sec*1e6+tv.tv_usec);
}


static sem_t ordering;      // per gestire l'ordine di arrivo
static sem_t mutex;         // per proteggere 'rcounter' modificato dai lettori
static sem_t rwlock;        // per garantire l'accesso esclusivo tra lettori e scrittori
static int   rcounter = 0;  // contatore dei lettori in sezione critica

static void P(sem_t* sem) {
  sem_wait(sem);
}
static void V(sem_t* sem) {
  sem_post(sem);
}
  
void startRead() {
  P(&ordering);         // mi metto in fila secondo l'ordine di arrivo
  P(&mutex);            // devo modificare rcounter in modo atomico
  if (++rcounter == 1)  // sono il primo lettore
    P(&rwlock);         // se c'e' uno scrittore in sezione critica mi blocco
  V(&ordering);         // faccio iniziare l'accesso ad altri (sia lettori che scrittori)
  V(&mutex);            // faccio entrare i lettori
}
void doneRead() {
  P(&mutex);            // devo modificare rcounter in modo atomico
  if (--rcounter == 0)  // se sono l'ultimo lettore...
    V(&rwlock);         // ... faccio entrare gli scrittori, se in attesa
  V(&mutex);          
}

void startWrite() {
  P(&ordering);        // mi metto in file secondo l'ordine di arrivo
  P(&rwlock);          // se c'e' un lettore o uno scrittore mi blocco
  V(&ordering);        // avanti al prossimo della fila
}
void doneWriter() {
  V(&rwlock);          // faccio entrare o altri scrittori o il primo lettore se in attesa
}


void work(long us) {
  struct timespec t={0, us*1000};
  nanosleep(&t, NULL);
}

void *Reader(void* arg) {
  long id = (long)arg;

  while(stop>0) {
    startRead();
    
    printf("READER%ld ENTRATO in sezione critica t=%.2f\n",id, (getusec()-t0)/1000.0);
    work(3000);
    printf("READER%ld USCITO dalla sezione critica\n",id);
    
    doneRead();
  }
  printf("READER%ld TERMINATO\n", id);  
  return NULL;
}

void *Writer(void* arg) {
  long id = (long)arg;

  for(int i=0;i<N;++i) {
    startWrite();

    printf("WRITER%ld ENTRATO in sezione critica t=%.2f\n",id, (getusec()-t0)/1000.0);
    work(6000);
    printf("WRITER%ld USCITO dalla sezione critica\n",id);

    if (i+1 == N) --stop;
    
    doneWriter();
  }

  printf("WRITER%ld TERMINATO\n", id);  
  return NULL;
}

int main(int argc, char* argv[]) {
  int R = 5;
  int W = 2;
  N=100;
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

  
  // sem initializations
  if (sem_init(&ordering, 0, 1)<0) {
    fprintf(stderr, "sem_init ordering failed\n");
    return -1;
  }
  if (sem_init(&mutex, 0, 1)<0) {
    fprintf(stderr, "sem_init mutex failed\n");
    return -1;
  }
  if (sem_init(&rwlock, 0, 1)<0) {
    fprintf(stderr, "sem-init rwlock failed\n");
    return -1;
  }	   

  stop = W;
  t0   = getusec();
  
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

  // sem initializations
  if (sem_destroy(&ordering)<0) {
    fprintf(stderr, "sem_destroy ordering failed\n");
    return -1;
  }
  if (sem_destroy(&mutex)<0) {
    fprintf(stderr, "sem_destroy mutex failed\n");
    return -1;
  }
  if (sem_destroy(&rwlock)<0) {
    fprintf(stderr, "sem_destroy rwlock failed\n");
    return -1;
  }	   

  return 0;   
  
}
