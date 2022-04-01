#define _POSIX_C_SOURCE 200112L
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

static int N;
static int stop;

static sem_t ordering;   // per gestire l'ordine di arrivo
static sem_t mutex;      // per proteggere 'rcounter' modificato dai lettori
static sem_t rwlock;     // per garantire l'accesso esclusivo tra lettori e scrittori
static int rcounter = 0; // contatore dei lettori in sezione critica

static void P(sem_t *sem)
{
    sem_wait(sem);
}
static void V(sem_t *sem)
{
    sem_post(sem);
}

void work(long us)
{
    struct timespec t = {0, us * 1000};
    nanosleep(&t, NULL);
}

void *Writer(void *);
void *Reader(void *);

void startWrite();
void endWrite();
void startRead();
void endRead();

int main(int argc, char const *argv[])
{
    int R = 10; // preparo 10 lettori
    int W = 15; // preparo 10 scrittori
    N = 2;
    stop = W;

    // Alloco spazio per lettori e scrittori
    pthread_t *readers = malloc(R * sizeof(pthread_t));
    pthread_t *writers = malloc(W * sizeof(pthread_t));
    // Creazione dei W thread scrittori e R thread lettori
    for (long i = 0; i < W; i++)
    {
        if (pthread_create(&writers[i], NULL, Writer, (void *)i) != 0)
        {
            fprintf(stderr, "pthread_create Writer failed\n");
            return -1;
        }
    }
    for (long i = 0; i < R; i++)
    {
        if (pthread_create(&readers[i], NULL, Reader, (void *)i) != 0)
        {
            fprintf(stderr, "pthread_create Writer failed\n");
            return -1;
        }
    }

    // Chiusura dei thread aperti precedentemente
    for (long i = 0; i < R; ++i)
    {
        if (pthread_join(readers[i], NULL) == -1)
        {
            fprintf(stderr, "pthread_join failed\n");
        }
    }
    for (long i = 0; i < W; ++i)
    {
        if (pthread_join(writers[i], NULL) == -1)
        {
            fprintf(stderr, "pthread_join failed\n");
        }
    }

    free(writers);
    free(readers);

    // Distruzione semafori
    if (sem_destroy(&ordering) < 0)
    {
        fprintf(stderr, "sem_destroy ordering failed\n");
        return -1;
    }
    if (sem_destroy(&mutex) < 0)
    {
        fprintf(stderr, "sem_destroy mutex failed\n");
        return -1;
    }
    if (sem_destroy(&rwlock) < 0)
    {
        fprintf(stderr, "sem_destroy rwlock failed\n");
        return -1;
    }

    return 0;
}

void *Writer(void *arg)
{
    long id = (long)arg;
    for (int i = 0; i < N; i++)
    {
        startWrite();
        printf("Writer %ld entrato nella zona critica\n", id);
        work(3000);
        printf("Writer %ld uscito dalla  zona critica\n", id);
        if (i + 1 == N)
            --stop;
        endWrite();
    }

    printf("Writer %ld terminato\n", id);
    return NULL;
}
void *Reader(void *arg)
{
    long id = (long)arg;

    while (stop > 0)
    {
        startRead();

        printf("Reader %ld entrato nella zona critica\n", id);
        work(2000);
        printf("Reader %ld uscito dalla  zona critica\n", id);

        endRead();
    }

    printf("Reader %ld terminato\n", id);
    return NULL;
}

void startWrite()
{
    P(&ordering);
    P(&rwlock);
    V(&ordering);
}
void endWrite()
{
    V(&rwlock);
}
void startRead()
{
    P(&ordering);
    P(&mutex);
    if (++rcounter)
        P(&rwlock);
    V(&ordering);
    V(&mutex);
}
void endRead()
{

    P(&mutex);
    if (--rcounter == 0)
        V(&rwlock);
    V(&mutex);
}