#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "graph.h"
#include "stack_fp.h"
#include "stack_types.h"

#define MAXSTRING 65536
/**
* @brief This function implements the DFS algorithm starting
from the node with id ini_id
* @param pg, Graph
* @param ini_id, Origin node Id
* @param end_id, Destination node Id
* @param path, String with the traversed node's name.
* This parameter is modified by the function.
**/
Status graph_deepFirst (Graph *pg, long ini_id, long end_id, char *nodestraversed);

int main(int argc, char * argv[])
{
    /*Initialization*/
    FILE * f;
    Graph * g;
    char names[MAXSTRING];
    names[0]='\0';
    if(!argv[3]) 
    {
        printf("ERROR not enough arguments. arg1: filename, arg2: root id, arg3: dest id\n");
        return -1;
    }
    f = fopen(argv[1],"r");
    g = graph_init();

    /*File reading*/
    if((graph_readFromFile(f,g)) == ERROR)
    {
        printf("ERROR READING FILE");
        return 1;
    }

    /*Function call*/
    graph_deepFirst (g,atol(argv[2]),atol(argv[3]),names);
    printf("%s",names);
    graph_free(g);
    fclose(f);
    return 0;
}

Status graph_deepFirst (Graph *pg, long ini_id, long end_id, char *nodestraversed){

    /*Initialization*/
    int i;
    long * nodes;
    Stack * s = NULL;
    Node * n, * n2;
    nodes = graph_getNodesId(pg);

    /*Error control*/
    if (!pg||!nodestraversed) return ERROR;

    /*Initialize auxiliar stack*/
    if(!(s = stack_init(node_free,node_copy,node_print))) return ERROR;

    /*Change nodes in graph label to WHITE except root to black*/
    printf("Changing labels to white...\n");
    for (i=0;i<graph_getNumberOfNodes(pg);i++)
    {

        n = graph_getNode(pg,nodes[i]);
        node_setLabel(n, WHITE);
        graph_setNode(pg,n);
        node_free(n);
    }
    printf("Changing root node label to black...\n");
        n = graph_getNode(pg,ini_id);
        node_setLabel(n, BLACK);
        graph_setNode(pg,n);
        
    
    /*Insert root node in stack*/
    if(stack_push(s,n) == ERROR ) return ERROR;
    node_free(n);

    /*Bucle*/
    while (stack_isEmpty(s)==FALSE)
    {
        n = (Node*)stack_pop(s);
        strcat(nodestraversed,node_getName(n));
        strcat(nodestraversed,"\n");
        if (node_getId(n) == end_id) break; 
        free(nodes);
        nodes = graph_getConnectionsFrom(pg,node_getId(n)); /*Array con todas las conexiones*/
        for (i=0;i<node_getConnect(n);i++)
        {
            n2 = graph_getNode(pg, nodes[i]);
            if ( node_getLabel(n2) == WHITE )
            {
                        node_setLabel(n2, BLACK);
                        node_setPredecessorId(n2,node_getId(n));
                        graph_setNode(pg,n2);
                        stack_push(s,n2);
            }
            node_free(n2);
        }
        free(n);
    }
    stack_free(s);
    node_free(n);
    free(nodes);
    return END;
}