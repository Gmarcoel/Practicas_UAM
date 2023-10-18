/**
The  compiler's  symbol  table  developed  during  the  course  should  provide  the  correct  management  of 
domains. Given the characteristics of the ALFA language, it can be said that 
● When the compiler is compiling code outside a function, there is only one scope (the global one). 
● When the compiler is compiling a function, there are two open scopes (the global scope and the local 
scope of the function). 
 
That is, at any given moment of the compilation, there can be a maximum of two open domains. 
 
A possible solution for the management of scopes in ALFA is to have two tables, one for storing the 
identifiers of the global scope, and the other for storing the local identifiers of the functions. 
In  order  to  obtain  the  shortest  possible  compilation  time,  it  is  common  to  use  hash  tables  for  the 
implementation  of  the  compilers'  symbol  tables.  The  student  already  knows  this  type  of  data,  the 
algorithms for its management and its performance. 
 
The  student  must  write  the  files  and  C  modules  that  he  considers  necessary  for  the  definition  and 
implementation of a hash table. Later, the compiler's symbol table will consist of the combination of 
two of these hash tables. 
 
The  information  that  is  stored  in  the  symbol  table  for  each  program  identifier  can  be  found  in  the 
documentation corresponding to the working sessions of this practice
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLE_SIZE 	1024*1024		// Longitud máxima de la tabla
#define TRUE			1
#define FLASE			0
// kinds
#define VARIABLE 1
#define PARAMETRO 2
#define FUNCION 3
// data types
#define BOOLEAN 1
#define INT 2
// categories
#define ESCALAR 1
#define VECTOR 2


typedef struct _hash_node
{
	struct hash_node *next;	// Si el hash (clave) es el mismo, siga el relevo
	char *key;				//Palabra clave
	void *value;			//valor
	char is_occupyed;	// ¿Está ocupado?
}Hash_node;

typedef struct hash_table
{
	Hash_node **table;	//Tabla de picadillo
}Hash_Table;



unsigned int Hash(char* key, unsigned int key_len);

Hash_Table *creat_hash_table(void);
int add_node2HashTable(Hash_Table *Hs_table, char *key, unsigned int key_len, void *value);
void *get_value_from_hstable(Hash_Table *Hs_table, char *key, unsigned int key_len);

void hash_table_delete(Hash_Table *Hs_Table);

int exists_value_from_hstable(Hash_Table *Hs_table, char *key, unsigned int key_len);
Hash_node *alloc_and_init_hs_node();

