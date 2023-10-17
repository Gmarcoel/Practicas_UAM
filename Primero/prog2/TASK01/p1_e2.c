#include <stdio.h>
#include "graph.h"

int main(int argc,char **argv){

	Node* a;
	Node* b;
	Graph* g;
	/*Inicializa nodos*/

	a = node_init();
	b = node_init();
	
	node_setName(a, "first");
	node_setId( a,111);
	node_setLabel(a, WHITE);

	node_setName(b, "second");
	node_setId(b, 222);
	node_setLabel(b, WHITE);


	/*Grafo*/

	g = graph_init(); 

	/*Inserta nodos en grafo*/

	printf("Inserting node 1...");
	if( graph_insertNode (g,a) == ERROR ){
		printf("resultado...:0 ERROR\n");
	} else {
		printf("resultado...:1\n");
	}

	printf("Inserting node 2...");
	if( graph_insertNode(g,b) == ERROR ){
		printf("resultado...:0 ERROR\n");
	}	else {
		printf("resultado...:1\n");
	}




	/*Inserta edge de 2 a 1*/
	
	printf("Inserting edge: node 2 ---> node 1\n");
	graph_insertEdge ( g, 222, 111 );

	/*Comprobación de conexiones*/

	printf("Nodes 1 and 2 connected? ");
	if(graph_areConnected (g, node_getId(a),node_getId(b)) == TRUE ) {
			printf("Si\n");
	}	else {
		printf("No\n");
	}

	printf("Nodes 2 and 1 connected? ");
	if(graph_areConnected (g, node_getId(b),node_getId(a)) == TRUE ) {
			printf("Si\n");
	}	else {
		printf("No\n");
	}

	

	/*Inserta nodo 2 en el grafo*/

	printf("Inserting node 2...");
	if( graph_insertNode (g,b) == ERROR ){
		printf("resultado...:0 ERROR\n");
	}	else {
		printf("resultado...:1\n");
	}

	/*Imprimir el grafo*/
	graph_print (stdout, g);

	/*Liberar recursos*/
	node_free(a);
	node_free(b);
	graph_free(g);
	return 0;
}
