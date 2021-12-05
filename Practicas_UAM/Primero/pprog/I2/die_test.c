#include "die.h"
int main(){
	int i;
	Die * die;
	die = die_create(0);
	
	die_roll(die);
	die_print(die);
	die_roll(die);
	die_print(die);
	die_roll(die);
	die_print(die);	
	die_destroy(die);
}