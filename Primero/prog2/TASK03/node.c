#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!< Maximum node name length */

struct _Node {
	/*!<Node name */
	char name[NAME_L]; 
	/*!<Node id */
	long id;
	/*!<Node number of connections */
	int nConnect;
	/*!<Node state */
	Label label;
	/*!<Nodepredecessor Id*/
	long predecessorid;
};

Node * node_init (){
	
	Node * node;
	node = (Node*) calloc (1, sizeof (Node));
	
	if(!node){
		printf("Error allocating memory!!\n");
		return NULL;
	}
	
	strcpy(node->name,"");
	node->id = (-1);
	node->nConnect = 0;
	node->label = WHITE;
	node->predecessorid = -1;

	return node;
}

void node_free (void * n){
	Node *node;
	node = (Node*)n;
	free(node);
}

long node_getId (const Node * n){

	if(!n){
		return -1;
	}

	return n->id;
}

const char* node_getName (Node * n){

	if(!n){
		return NULL;
	}

	return n->name;
}

int node_getConnect (const Node * n){

	if(!n){
		return -1;
	}

	return n->nConnect;
}

Label node_getLabel (const Node*n){

	if(!n){
		return ERROR_NODE;
	}

	return n->label;
}
long node_getPredecessorId (const Node * n){
	if(!n) return -1;
	return n->predecessorid;
}
Status node_setPredecessorId (Node * n,long predid){
	if(!n) return ERROR;
	n->predecessorid = predid;
	return OK;
}

Status node_setLabel (Node *n, Label l){

	if(!n){
		return ERROR;
	}

	n->label=l;
	return OK;
}

Status node_setId (Node * n, const long id){

	if(!n){
		return ERROR;
	}

	n->id = id;
	return OK;

}

Status node_setName (Node *n, const char *name){
	if(!n||!name){
		return ERROR;
	}
	strcpy(n->name, name);
	return OK;
}

Status node_setNConnect (Node *n, const int cn){
	if(!n){
		return ERROR;
	}
	n->nConnect=cn;
	return OK;
}

int node_cmp (const void *n1, const void *n2){

    Node *node1, *node2;

	if(!n1 || !n2){
		return -1;
	}

    node1 = (Node*)n1;
    node2 = (Node*)n2;

    if(node1->id != node2->id){
        return -1;
    }

    if(strcmp(node1->name, node2->name) != 0){
        return 1;
    }

    if((strcmp(node1->name, node2->name) == 0) && (node1->id == node2->id)){
        return 0;
    }
    return -1;
}

void * node_copy (const void *src){

	Node *node = NULL, *naux = NULL;
	if(src == NULL){
		return NULL;
	}
	node = node_init();
	if(node==NULL){
		return NULL;
	}
	naux = (Node*)src;
	if(node_setId(node, naux->id) == ERROR){
		return NULL;
	}
	if(node_setName(node, naux->name) == ERROR){
		return NULL;
	}
	if(node_setNConnect(node, naux->nConnect) == ERROR){
		return NULL;
	}
	if(node_setLabel(node, naux->label) == ERROR){
		return NULL;
	}

	if(node_setPredecessorId(node, naux->predecessorid) == ERROR){
		return NULL;
	}


	return node;
}

int node_print (FILE *pf, const void *n){

	Node *naux = NULL;
    int a;
    if(pf == NULL || n == NULL){
        return 0;
    }
    naux = (Node*)n;
	a = fprintf(pf, "[%ld, %s, %d, %d, %ld]", naux->id, naux->name, naux->nConnect, naux->label, naux->predecessorid);

    return a;
}










































































