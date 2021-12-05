#include "graph.h"
#include "node.h"

/*ESTRUCTURA GRAPH*/
struct _Graph {
	Node *nodes[MAX_NODES]; /*!<Array with the graph nodes */
	Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
	int num_nodes;
/*!<Total number of nodes in te graph */
	int num_edges;
/*!<Total number of connection in the graph*/
};


int find_node_index(const Graph * g, long nId1);
int* graph_getConnectionsIndex(const Graph * g, int index);

Graph * graph_init (){
	
	int i=0,j=0;
	Graph * g;
	
	g = (Graph*)calloc(1,sizeof(Graph));
	


	if (g == NULL){
		return NULL;
	} else {
		g->num_edges = 0;
		g->num_nodes = 0;
		
		for( i=0; i < MAX_NODES; i++ ){

			g->nodes[i]=NULL;
			
			for( j=0; j < MAX_NODES; j++ ) {
				g->connections[i][j] = 0;
			}

		}
		
		return g;
	}

}

void graph_free (Graph *g){
	int i;
	for(i=0;i<g->num_nodes;i++){
		free(g->nodes[i]);
	}
	free(g);
}

Status graph_insertNode (Graph *g, const Node *n){
	int i,id;	
	if(!g){
		return ERROR;
	}
	i=g->num_nodes;
	id = node_getId(n);
	if ( find_node_index(g,id) == -1 ) {
		g->nodes[i]=node_copy(n);
		(g->num_nodes)++;

		return OK;
	} else {
		return ERROR;
	}

}

Status graph_insertEdge (Graph *g, const long nId1, const long nId2) {

int a = node_getConnect(g->nodes[find_node_index(g,nId1)])+1;

	if(!g) {
		return ERROR;
	}	

	g->connections[find_node_index(g,nId1)][find_node_index(g,nId2)]=1;
	
	g->num_edges++;
	
	node_setNConnect(g->nodes[find_node_index(g,nId1)],a);

	
	return OK;
}

Node *graph_getNode (const Graph *g, long nId){
	Node * n;
	if(!g){
		return NULL;
	}
	if(find_node_index(g,nId)!=-1){
		n = node_copy(g->nodes[find_node_index(g, nId)]);
		return n;
	}
	return NULL;
}

Status graph_setNode (Graph *g, const Node *n){

	int i;	
	if(!n||!g){
		return ERROR;
	}
	for(i=0;i<g->num_nodes;i++){
		if(node_getId(g->nodes[i]) == node_getId(n)){
			/*Esto yo no se si va asi*/
			node_free(g->nodes[i]);
			g->nodes[i] = node_copy(n);
			return OK;
		}
	}
	return ERROR;
}

long * graph_getNodesId (const Graph *g) {
	long *array;
	int i=0,j;	
	if(!g){
		return NULL;
	}
	if(!(array = (long*)calloc(g->num_nodes,sizeof(long)))){
		return NULL;
	}
	/*
	for(i=0;i<g->num_nodes;i++){
		array[i]=node_getId(g->nodes[i]);
	}	
	*/
	for (i=0,j=0;i<MAX_NODES;i++)
	{
		if (g->nodes[i]!=NULL)
		{
			array[j] = node_getId(g->nodes[i]);
			j++;
		}
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

	int in1, in2;	
	if (!g) {
		return FALSE;
	}
	in1 = find_node_index(g,nId1);
	in2 = find_node_index(g,nId2);
	return g->connections[in1][in2];
}

int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId){
	if(!g){
		return -1;
	}
	return node_getConnect(g->nodes[find_node_index(g, fromId)]);
}

long* graph_getConnectionsFrom (const Graph *g, const long fromId){
	long * array;
	int* index = graph_getConnectionsIndex(g, find_node_index(g, fromId));
	int i=0;
	if(!g){
		return NULL;
	}



	if(!(array = (long*)calloc(graph_getNumberOfConnectionsFrom(g,fromId),sizeof(long)))){
			return NULL;
	}
	for (i=0;i</*node_getConnect(g->nodes[find_node_index(g, fromId)])*/graph_getNumberOfConnectionsFrom(g,fromId);i++){
		array[i] = node_getId(g->nodes[index[i]]);
	}
	free(index);
	return array;
}

int graph_print (FILE *pf, const Graph *g){
	int i=0,n=0, j=0,*array=NULL;	
	if (!g){
		return -1;
	}
	for(i=0;i<g->num_nodes;i++){
		if( g->nodes[i] != NULL ){
			n = n + node_print (pf,g->nodes[i]);
			array = graph_getConnectionsIndex( g, find_node_index(g,node_getId(g->nodes[i])));
			for( j=0; j<node_getConnect(g->nodes[i]); j++){
				n = n + fprintf(pf,"%li ", node_getId(g->nodes[array[j]]));
			}
			free(array);
			fprintf(pf,"\n");
				
		}

	}
	
	return n;
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
int i;
if (!g) return -1;
for(i=0; i < g->num_nodes; i++) {
if (node_getId (g->nodes[i]) == nId1) return i;
}
return -1;
}

int* graph_getConnectionsIndex(const Graph * g, int index) {
	int *array = NULL, i, j = 0, size;
	if (!g) return NULL;
	if (index < 0 || index >g->num_nodes) return NULL;

	size = node_getConnect (g->nodes[index]);
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
