
#ifndef POOL_THREAD_H_
#define POOL_THREAD_H_


#include <stdlib.h>

//typedef struct _pool_thread pool_thread;
typedef struct _pool_thread
{
    int stop;
    pthread_mutex_t shared_mutex;
    pthread_t *threads;
} pool_thread;


// typedef struct _Work Work;
void *th_main(pool_thread *pt);
void pool_th_destroy();
void poolSubmit(pool_thread * pt, void *function, void * arg, char * name);
int pool_th_ini(pool_thread * pt, int nthreads);



#endif