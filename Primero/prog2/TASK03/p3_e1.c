#include "graph.h"
#include "queue.h"
#include "string.h"
#define SIZE 100
int main(int argc, char * argv[])
{
    /*Declaration*/
    FILE *f;
    Graph * g;
    Queue * q;
    Node * a;
    long * nodes;
    int i;
    char name[SIZE];

    /*Initialization*/
    if(!argv[1]) 
    {
        printf("ERROR no file name provided\n");
        return -1;
    }
    strcpy(name,argv[1]);
    f = fopen(name,"r");
    g = graph_init();
    graph_readFromFile(f,g);
    nodes = graph_getNodesId(g);
    q = queue_init(node_free,node_copy,node_print);

    /*Insert nodes in graph*/
    printf("Inserting nodes in the graph...\n");
    for (i=0;i<3;i++)
    {
        queue_insert(q,graph_getNode(g,nodes[i]));
    }

    /*Change nodes in graph label to BLACK*/
    printf("Changing labels to black...\n");
    for (i=0;i<graph_getNumberOfNodes(g);i++)
    {
        node_setLabel(graph_getNode(g,nodes[i]),BLACK);
    }    

    /*Print graph*/
    printf("Printing graph...\n");
    graph_print(stdout,g);

    /*Print queue size*/
    printf("Printing queue size...\n");
    printf("\nSize of the queue: %i\n",queue_size(q));

    /*Print queue*/
    printf("Printing queue...\n");
    queue_print(stdout,q);

    /*Extract elements from queue*/
    while (queue_isEmpty(q)==FALSE)
    {
        printf("\nExtract node:\n");
        a = (Node*)queue_extract(q);
        node_print(stdout,a);
        node_free(a);
    }

    /*Print queue size*/
    printf("Printing queue size...\n");
    printf("\nSize of the queue: %i\n",queue_size(q));

    /*Free*/
    fclose(f);
    graph_free(g);
    queue_free(q);
    free(nodes);
    return 0;
}