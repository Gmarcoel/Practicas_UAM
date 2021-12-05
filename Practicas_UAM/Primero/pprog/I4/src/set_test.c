#include "set.h"
int main(){
	int i;
	Set * set;
	set= set_create();
	
	set_print(stdout,set);
	set_addId(set,34);
	set_addId(set,56);
	set_print(stdout,set);
	set_addId(set,71);
	set_print(stdout,set);
	set_delId(set,56);
	set_print(stdout,set);
	set_destroy(set);
}
