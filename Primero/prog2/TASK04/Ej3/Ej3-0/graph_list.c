#include "graph.h"
#include "node.h"
#include "list.h"
#include "types.h"
#define MAX_NODES 1064

/*ESTRUCTURA GRAPH*/

struct _Graph {
    List *plnode;/*!<Listwith the graph nodes*/
    Bool connections[MAX_NODES][MAX_NODES];/*!<Adjacencymatrix*/
    int num_nodes;/*!<Totalnumber of nodes in the graph*/
    int num_edges;/*!<Totalnumber of connections in the graph*/
};


int find_node_index(const Graph * g, long nId1);
int* graph_getConnectionsIndex(const Graph * g, int index);

Graph * graph_init (){
	
	int i=0,j=0;
	Graph * g;
	g = (Graph*) calloc (1, sizeof(Graph));
    g->plnode = list_new(node_free, node_copy, node_print, node_cmp);
    
	if (g == NULL){
		return NULL;
	} else if(!g->plnode) {
        graph_free(g);
        return NULL;
    } else {

		g->num_edges = 0;
		g->num_nodes = 0;
		
		for( i=0; i < MAX_NODES; i++ ){
			
			for( j=0; j < MAX_NODES; j++ ) {
				g->connections[i][j] = 0;
			}

		}
	
		return g;
	}

}

void graph_free (Graph *g){
    Graph *graph;
    graph = (Graph*)g;
    list_free(g->plnode);
	free(graph);
}

Status graph_insertNode (Graph *g, const Node *n){
	int i;
		if(!g||!n){
		return ERROR;
	}
	for(i=0;i<g->num_nodes;i++)
	{
		if(node_getId(list_getElementInPos(g->plnode,i))==node_getId(n))
		{
			return ERROR;
		}
	}
    if(list_pushFront(g->plnode, n) == ERROR) return ERROR;
    (g->num_nodes)++;
    return OK;
}

Status graph_insertEdge (Graph *g, const long nId1, const long nId2) {
    Node * naux;
    naux = list_getElementInPos(g->plnode,(g->num_nodes-1)- find_node_index(g, nId1));

    if(!g) {
	    return ERROR;
	}

	g->connections[find_node_index(g, nId1)][find_node_index(g, nId2)]=1;
	g->num_edges++;
	node_setNConnect(naux, node_getConnect(naux)+1);

	
	return OK;
}

Node *graph_getNode (const Graph *g, long nId){
	Node * n,*aux;
	int i;
	for (i=0;i<graph_getNumberOfNodes(g);i++)
	{
		n = list_getElementInPos(g->plnode,i);
		if(nId==node_getId(n))
		{
			aux = node_copy(n);
			return aux;
		}
	}

	return NULL;
}

Status graph_setNode (Graph *g, const Node *n){
    Node * naux;
	if(!n||!g){
		return ERROR;
	}
    naux = list_getElementInPos(g->plnode,(g->num_nodes-1)-find_node_index(g,node_getId(n)));

    node_setName(naux,node_getName(n));
    node_setNConnect(naux,node_getConnect(n));
    node_setLabel(naux,node_getLabel(n));
    /*
    node_free(naux);
    naux = node_copy(n);
	*/
	return OK;
}

long * graph_getNodesId (const Graph *g) {
	long *array;
    int i;
	Node * naux;
	if(!g){
		return NULL;
	}
	if(!(array = (long*)calloc(g->num_nodes,sizeof(long)))){
		return NULL;
	}
	for (i=0;i<graph_getNumberOfNodes(g);i++)
    {
        naux = list_getElementInPos(g->plnode,i);
		array[i] = node_getId(naux);
    }
	return array;
}

int graph_getNumberOfNodes (const Graph *g){
	if(!g){
		return -1;
	}
		
	return g->num_nodes;


}

int graph_getNumberOfEdges (const Graph *g){
	if(!g){
		return -1;
	}
		
	return g->num_edges;

}

Bool graph_areConnected (const Graph *g, const long nId1, const long nId2){
	if (!g) {
		return FALSE;
	}
	return g->connections[find_node_index(g, nId1)][find_node_index(g, nId2)];
}

int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId){
	if(!g){
		return -1;
	}
	return node_getConnect(list_getElementInPos(g->plnode,(g->num_nodes -1)-find_node_index(g, fromId)));
}

long* graph_getConnectionsFrom (const Graph *g, const long fromId){
	long * array;
	int* index = graph_getConnectionsIndex(g,find_node_index(g, fromId));
	int i=0;
	if(!g){
		return NULL;
	}



	if(!(array = (long*)calloc(graph_getNumberOfConnectionsFrom(g,fromId),sizeof(long)))){
			return NULL;
	}
	for (i=0;i<graph_getNumberOfConnectionsFrom(g,fromId);i++){
		array[i] = node_getId(list_getElementInPos(g->plnode,(g->num_nodes-1)-index[i]));
	}
	free(index);
	return array;
}

int graph_print (FILE *pf, const Graph *g){
	Node * aux;
	int i,j,*array,n;
	for (i=graph_getNumberOfNodes(g)-1;i>=0;i--)
	{
		aux = list_getElementInPos(g->plnode,i);
		n = n + node_print(pf,aux);
		array = graph_getConnectionsIndex(g,i);
		for( j=0; j<node_getConnect(aux); j++){
			n = n + fprintf(pf,"%li ", node_getId(list_getElementInPos(g->plnode,array[j])));
		}
		fprintf(pf,"\n");
		free(array);

	}
	return n;
	/*
	int i=0,n=0, j=0,*array=NULL;	

	if (!g){
		return -1;
	}
	for(i=0;i<g->num_nodes;i++){
		if( list_getElementInPos(g->plnode,i) != NULL ){
			n = n + node_print (pf,list_getElementInPos(g->plnode,i));
			array = graph_getConnectionsIndex( g, find_node_index(g,node_getId(list_getElementInPos(g->plnode,i))));
			for( j=0; j<node_getConnect(list_getElementInPos(g->plnode,i)); j++){
				n = n + fprintf(pf,"%li ", node_getId(list_getElementInPos(g->plnode,array[j])));
			}
			free(array);
			fprintf(pf,"\n");
				
		}

	}
	
	return n;
	*/
}

Status graph_readFromFile (FILE *fin, Graph *g){
    Node *n = NULL;
    char a[NAME_L], name[NAME_L];
    int i, numn = 0;
    long id1, id2;
    int label = 0;
    Status f = OK;

    if(fgets(a, NAME_L, fin)!=NULL){
        if(sscanf(a, "%d",&numn)!=1) return ERROR;
    }

    n=node_init();
    if(!n) return ERROR;

    for(i=0;i<numn && f==OK;i++){
        if(fgets(a,NAME_L,fin)!=NULL){
            if(sscanf(a,"%ld %s %d",&id1,name,&label)==3){
                node_setName(n,name);
                node_setId(n,id1);
                node_setLabel(n,label);
                f=graph_insertNode(g,n);
            }
            else {
                f=ERROR;
            }
        }
    }

    if(i<numn){
        f=ERROR;
    }

    while(fgets(a,NAME_L,fin)&&f==OK){
        if(sscanf(a,"%ld %ld",&id1,&id2)==2){
            f=graph_insertEdge(g,id1,id2);
        }
        else{
            f=ERROR;
        }
    }

    node_free(n);


    return f;

}






int find_node_index(const Graph * g, long nId1) {
	Node * naux;
	int index;
	if(!g) return -1;
	naux = graph_getNode(g,nId1);
	index = list_getPositionElement(g->plnode,naux);
	node_free(naux);
	return (g->num_nodes - index)-1;
}

int* graph_getConnectionsIndex(const Graph * g, int index) {
	int *array = NULL, i, j = 0, size;
	if (!g) return NULL;
	if (index < 0 || index > g->num_nodes) return NULL;

	size = node_getConnect (list_getElementInPos(g->plnode,(g->num_nodes-1)- index));
	array = (int *) malloc(sizeof (int) * size);
	if (!array) {

		fprintf (stderr, "%s\n", strerror(errno));
		return NULL;
	}
	for(i = 0; i< g->num_nodes; i++) {
		if (g->connections[index][i] == TRUE) {
			array[j++] = i;
		}
	}
	return array;
}