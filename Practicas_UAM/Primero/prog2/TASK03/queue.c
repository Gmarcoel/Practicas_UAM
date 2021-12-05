#include "queue.h"

/* ----------- queue.c -------------- */
struct _Queue {
void* items [MAX_QUEUE];
int front;
int rear;
destroy_element_function_type free;
copy_element_function_type copy;
print_element_function_type print;
};

Queue* queue_init(destroy_element_function_type f1,copy_element_function_type f2, print_element_function_type f3)
{
    /*Declarations*/
    Queue * q = NULL;
    int i;
    
    /*Error control*/
    if(!f1||!f2||!f3) return NULL;

    /*Allocation*/
    if(!(q = (Queue *)malloc(sizeof(Queue)))) return NULL;

    /*Initialization*/
    for (i = 0; i<MAX_QUEUE; i++) q->items[i]=NULL;
    q->front = 0;
    q->rear = 0;
    q->free = f1;
    q->copy = f2;
    q->print = f3;

    return q;

}

void queue_free(Queue *q)
{
    /*Declarations*/
    int i;

    /*Error control*/
    if (!q) return;

    /*Implementation*/
    while (q->front!=q->rear)
    {
        q->free(q->items[q->front]);
        q->front = (q->front + 1)%MAX_QUEUE;
    }
    free(q);
    
    return;
}

Bool queue_isEmpty(const Queue *q)
{
    /*Error control*/
    if(!q) return TRUE;

    /*Implementation*/
    if(q->front == q->rear) return TRUE;
    return FALSE;
}

Bool queue_isFull(const Queue *q)
{
    /*Error control*/
    if(!q) return FALSE;

    /*Implementation*/
    if((q->rear+1)%MAX_QUEUE == q->front) return TRUE;
    
    
    return FALSE;
}

Status queue_insert(Queue *q, const void* e)
{
    /*Declaration*/
    void * a = NULL;
    /*Error control*/
    
    if (!q||!e||queue_isFull(q) == TRUE) return ERROR;

    /*Implementation*/
    if(!(a = q->copy(e))) return ERROR;
    q->items[q->rear] = a;
    q->rear = (q->rear +1)%MAX_QUEUE;


    
    
    return OK;
}

void * queue_extract(Queue *q)
{
    /*Declaration*/
    void * a;
    /*Error control*/
    if(!q||queue_isEmpty(q)==TRUE) return NULL;

    /*Implementation*/
    a = q->items[q->front];
    q->items[q->front]=NULL;
    q->front = (q->front +1)%MAX_QUEUE;
    
    
    return a;
}

int queue_size (const Queue *q)
{
    /*Error control*/
    if (!q) return -1;

    /*Implementation*/
    if (q->front<=q->rear) return q->rear - q->front;
    

    return (MAX_QUEUE - q->front) + q->rear;
}

int queue_print(FILE *pf, const Queue *q){
    /*Declaration*/
    int i,n=0;

    /*Error control*/
    if(!q) return -1;

    /*Implementation*/
    for(i=q->front;i!=q->rear;/*(i+1)%MAX_QUEUE*/i++)
        n = n + q->print(pf,q->items[i]);
    
    return n;
}