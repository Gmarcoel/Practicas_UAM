#include <stdio.h>
#include <stdlib.h>
#include "die.h"
#include "die_test.h"
#include "test.h"

#define MAX_TESTS 6

/** 
 * @brief Main function for INVENTORY unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char **argv){

    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all test for module Inventory:\n");
    }
    else
    {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS)
        {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS); /*EXIT_SUCCESSS*/
        }
    }

    if (all || test == 1)
	{
        test1_die_create();
	}
    if (all || test == 2)
	{
        test2_die_create();
	}
	if (all || test == 3)
	{
        test1_die_roll();
	}
    if (all || test == 4)
	{
        test2_die_roll();
	}
	if (all || test == 5)
	{
        test1_die_last_value();
	}
    if (all || test == 6)
	{
        test2_die_last_value();
	}



        PRINT_PASSED_PERCENTAGE;

        return 1;
}

void test1_die_create()
{
	Die *die;
	Id id;
	id=2;
	die=die_create(id);
	PRINT_TEST_RESULT(die!=NULL);

	die_destroy(die);
}

void test2_die_create()
{
	Die *die;
	Id id=NO_ID;
	die=die_create(id);
	PRINT_TEST_RESULT(die==NULL);

	die_destroy(die);
}

void test1_die_roll()
{
	Die *die;
	Id id;
	id=2;
	die=die_create(id);
	PRINT_TEST_RESULT(die_roll(die)!=-1);

	die_destroy(die);
}

void test2_die_roll()
{
	Die *die=NULL;
	Id id;
	id=NO_ID;
	die=die_create(id);
	PRINT_TEST_RESULT(die_roll(die)==-1);

	die_destroy(die);
}

void test1_die_last_value()
{
	Die *die;
	Id id;
	int value;
	id=2;
	die=die_create(id);
	value=die_roll(die);
	PRINT_TEST_RESULT(value!=-1);

	die_destroy(die);
}

void test2_die_last_value()
{
	Die *die;
	Id id;
	int value;
	id=NO_ID;
	die=die_create(id);
	value=die_roll(die);
	PRINT_TEST_RESULT(value==-1);

	die_destroy(die);
}
