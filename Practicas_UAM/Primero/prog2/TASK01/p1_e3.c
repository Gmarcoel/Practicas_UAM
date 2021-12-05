#include "graph.h"
#define MAX 100
int main(int argc,char * argv[]){
	FILE* f;
	Graph * g;
	char name[MAX];
	strcpy(name,argv[1]);
	g = graph_init();



	
	f = fopen(name,"r");

	
	graph_readFromFile (f,g);


	fclose(f);
	graph_print(stdout,g);
	graph_free(g);
	return 0;
}