#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"

#define MAXSTRING 65536

/***** @brief Implements the BFS algorithm from an initial node
* @param pg, Graph
* @param ini_id, Origin node Id
* @param end_id, Destination node Id
* @param path, String with the traversed node's name.
* This parameter is modified by the function.
* @return, OK or ERROR if any pointer is NULL
****/
Status graph_breadthFirst (Graph *pg,long ini_id,long end_id,char * nodestraversed);
int pathToFrom (FILE*dev, Graph *g,long orignid,long toid);
int printNode (FILE*fp,const Graph *g,long actualid,long*predid);
int pathFromTo (FILE*dev, Graph *g,long orignid,long toid);
int pathFromTo_rec (FILE * dev, Graph * g, long * originid, long id);

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
    graph_breadthFirst (g,atol(argv[2]),atol(argv[3]),names);
    printf("From origin to end:\n");
    pathFromTo (stdout,g,atol(argv[2]),atol(argv[3]));
    printf("\nFrom end to origin:\n");
    pathToFrom (stdout,g,atol(argv[2]),atol(argv[3]));
    graph_free(g);
    fclose(f);
    return 0;
}



Status graph_breadthFirst (Graph *pg,long ini_id,long end_id,char * nodestraversed)
{
    /*Initialization*/
    int i;
    long * nodes;
    Queue * q;
    Node * n, * n2;
    nodes = graph_getNodesId(pg);

    /*Error control*/
    if (!pg||!nodestraversed) return ERROR;

    /*Initialize auxiliar queue*/
    if(!(q = queue_init(node_free,node_copy,node_print))) return ERROR;

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
        
    
    /*Insert root node in queue*/
    if(queue_insert(q,n) == ERROR ) return ERROR;
    node_free(n);

    /*Bucle*/
    while (queue_isEmpty(q)==FALSE)
    {
        n = (Node*)queue_extract(q);
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
                        queue_insert(q,n2);
            }
            node_free(n2);
        }
        free(n);
    }
    queue_free(q);
    node_free(n);
    free(nodes);
    return END;
}

/****
* @brief Prints a path from the destination node to the origin* using the predecessors
* @param dev, Stream pointer
* @param g, Pointer to the graph
* @param originid, node origin id
* @param toid, node destination id
* @return.  Return the number of characters printed.10
* If there have been errors in the Output flow* prints an error message in stderror and returns the value -1.
**/
int pathToFrom (FILE*dev, Graph *g,long orignid,long toid)
{
    long id = toid, *preid = NULL;
    int n = 0;
    preid = (long*)malloc(sizeof(long));

    while ( id != orignid ){
        n = n + printNode(dev,g,id,preid);
        id = *preid;
    }
    n = n + printNode(dev,g,id,preid);
    free(preid);
    return n;
}
int printNode (FILE*fp,const Graph *g,long actualid,long*predid)
{
    Node * n, * n2;
    int p = 0;
    if(!fp||!g) return -1;
    n = graph_getNode(g,actualid);
    n2 = graph_getNode(g,node_getPredecessorId(n));
    *predid = node_getId(n2);
    p = p + node_print(fp,n);
    free(n);
    free(n2);
    return p;
}

/**
 *@brief Prints a path from the destination node to the origin* using the predecessors
 *@param dev, Stream pointer* @ param g, Pointer to the graph*@paramoriginid, node origin id
 *@param toid, node destination id
 *@return.  Return the number of characters printed.
 * If there have been errors in the Output flow
 * prints an error message in stderror and returns the value -1.
**/
int pathFromTo (FILE*dev, Graph *g,long orignid,long toid)
{
    return pathFromTo_rec (dev,g,&orignid,toid);
}
int pathFromTo_rec (FILE * dev, Graph * g, long * orignid, long id)
{
    Node * n;
    int c;
    long preid;
    /* Base case */
    if (*orignid == id){
        c = printNode(dev, g, id, &preid);
        return c;
    }
    /* get actual node */
    n = graph_getNode (g, id);
    if (!n) return -1;

    /* get predecessor id   */
    preid = node_getPredecessorId(n);

    /* recursive call   */
    c = pathFromTo_rec(dev, g, orignid, preid);
    if(c == -1) return -1;
    /* print actual node    */
    c += node_print (dev, n);
    node_free (n);
    return c;
}

