#include "pool_thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// Macros
#define QUEUE_SIZE 20

// Global variables
int workCount = 0;

typedef struct _Work
{
    void (*function)(void *, char*);
    void *arg;
    char * name;
} Work;
Work *queue[QUEUE_SIZE];
/*
struct _pool_thread
{
    int stop;
    pthread_mutex_t *shared_mutex;
    pthread_t *threads;
};
*/

/**
    * @brief Create a new thread pool.
    *
    * @param nthreads Number of threads in the pool.
    * @param shared_mutex If non-zero, the threads in the pool share a mutex.
    *
    * @return A new thread pool.
*/

int pool_th_ini(pool_thread * pt, int nthreads) {
    int i;
    pt->stop = 0;
    
    pthread_mutex_init(&(pt->shared_mutex), NULL);

    //pthread_mutex_init(pt->shared_mutex, NULL);

    pt->threads = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    for (i = 0; i < nthreads; i++)
    {
        printf("Creating thread %d\n", i);
        pthread_create(&(pt->threads[i]), NULL, th_main, (void*)pt);
    }
}

/**
    * @brief Create a work item.
    *
    * @param function Function to be executed by the thread.
    * @param arg Argument to be passed to the function.
*/
Work *work_create(void *function, void *arg, char * name)
{
    Work *work = (Work *)malloc(sizeof(Work));
    work->function = function;
    work->arg = arg;
    work->name = name;
    return work;
}

/**
    * @brief Destroy a work item.
    *
    * @param work Work item to be destroyed.
*/
void work_destroy(Work *work)
{
    free(work);
}

/**
    * @brief submit a job to the thread pool.
    *
    * @param work The job to be done.
*/
void poolSubmit(pool_thread *pt, void *function, void *arg, char * name)
{
    Work *work;
    work = work_create(function, arg, name);
    pthread_mutex_lock(&(pt->shared_mutex));
    queue[workCount] = work;
    workCount++;
    pthread_mutex_unlock(&(pt->shared_mutex));
}

void *th_main(pool_thread *pt)
{
    while (1)
    {
        
        if (pt->stop)
            break;
        Work *work;
        int found = 0;
        int connfd;
        pthread_mutex_lock(&(pt->shared_mutex));
        if (workCount > 0)
        {
            printf("Enters thread %d\n", pthread_self());
            found = 1;
            work = queue[0];
            for (int i = 0; i+1 < workCount; i++)
            {
                queue[i] = queue[i + 1];
            }
            workCount--;
        }
        pthread_mutex_unlock(&(pt->shared_mutex));

        if (found == 1)
        {
            (work->function)(work->arg,work->name);
            work_destroy(work);
        }
    }
    
    
}

/**
    * @brief Destroy a thread pool.
    *
    * @param pt Thread pool to destroy.
    */
void pool_th_destroy(pool_thread *pt)
{
    int nthreads;
    int i;
    if (pt == NULL)
        return;
    nthreads = sizeof(pt->threads);
    pthread_mutex_lock(&(pt->shared_mutex));
    pt->stop = 1;
    pthread_mutex_unlock(&(pt->shared_mutex));

    for (i = 0; i < nthreads; i++)
    {
        pthread_join(pt->threads[i], NULL);
    }
    pthread_mutex_destroy(&(pt->shared_mutex));
    free(&(pt->shared_mutex));
    free(pt->threads);
}
