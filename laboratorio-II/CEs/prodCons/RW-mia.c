#define _POSIX_C_SOURCE 200112L
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

static int N;    // Numero di volte in cui ripetere le azioni di scrittura
static int stop; // Scritture mancanti

// Variabile mutex usata per zona critica
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variabile mutex usata per bloccare gli altri se un lettore o scrittore lavora
static pthread_mutex_t ordering = PTHREAD_MUTEX_INITIALIZER;

// Variabile di condizione per sospendere lettori o scrdittori
static pthread_cond_t Go = PTHREAD_COND_INITIALIZER;

static int activeReaders = 0; // Sgna lettori attivi
static int activeWriters = 0; // Sgna scrittori attivi

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
    if (!readers || !writers)
    {
        fprintf(stderr, "not enough memory to allocate readers or writers\n");
        return -1;
    }

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

    // Libero la memoria allocata per i thread
    free(writers);
    free(readers);

    return 0;
}

/**
 * @brief Writer behavior
 *
 * @param args
 * @return void*
 */
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

/**
 * @brief Reader behavior
 *
 * @param args
 * @return void*
 */
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
    pthread_mutex_lock(&ordering);
    pthread_mutex_lock(&mutex);
    while (activeReaders > 0 || activeWriters > 0)
    {
        pthread_cond_wait(&Go, &mutex);
    }
    activeWriters++;
    pthread_mutex_unlock(&ordering);
    pthread_mutex_unlock(&mutex);
}
void endWrite()
{
    pthread_mutex_lock(&mutex);
    activeWriters--;
    pthread_cond_signal(&Go);
    pthread_mutex_unlock(&mutex);
}
void startRead()
{
    pthread_mutex_lock(&ordering);
    pthread_mutex_lock(&mutex);
    while (activeWriters > 0)
    {
        pthread_cond_wait(&Go, &mutex);
    }
    activeReaders++;
    pthread_mutex_unlock(&ordering);
    pthread_mutex_unlock(&mutex);
}
void endRead()
{
    pthread_mutex_lock(&mutex);
    activeReaders--;
    if (activeReaders == 0)
        pthread_cond_signal(&Go);

    pthread_mutex_unlock(&mutex);
}