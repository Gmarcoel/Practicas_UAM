/***
 * @brief Inventory test functions library
 * @file inventory_test.c
 * @author Gabriela Trabajo
 * @version 1.0
 * @date 12/04/20
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 19

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
        test_inventory_create();
    if (all || test == 2)
        test1_inventory_set_object();
    if (all || test == 3)
        test2_inventory_set_object();
    if (all || test == 4)
        test3_inventory_set_object();
    if (all || test == 5)
        test1_inventory_is_object();
    if (all || test == 6)
        test2_inventory_is_object();
    if (all || test == 7)
        test3_inventory_is_object();
    if (all || test == 8)
        test1_inventory_delete_object();
    if (all || test == 9)
        test2_inventory_delete_object();
    if (all || test == 10)
        test3_inventory_delete_object();
    if (all || test == 11)
        test1_inventory_get_maxobj();
    if (all || test == 12)
        test2_inventory_get_maxobj();
    if (all || test == 13)
        test1_inventory_set_maxobj();
    if (all || test == 14)
        test2_inventory_set_maxobj();
    if (all || test == 15)
        test1_inventory_get_NumObjects();
    if (all || test == 16)
        test2_inventory_get_NumObjects();
    if (all || test == 17)
        test3_inventory_get_NumObjects();
    if (all || test == 18)
        test1_inventory_print();
    if (all || test == 19)
        test2_inventory_print();

        PRINT_PASSED_PERCENTAGE;

        return 1;
}

void test_inventory_create()
{
    Inventory *in;
    in = inventory_create();
    PRINT_TEST_RESULT(in!=NULL);

    inventory_destroy(in);
}

void test1_inventory_add_object()
{
    Inventory *in;
    in = inventory_create();

    PRINT_TEST_RESULT(inventory_add_object(in, 3) == OK);

    inventory_destroy(in);
}

void test2_inventory_add_object()
{
    Inventory *in;
    in = inventory_create();

    PRINT_TEST_RESULT(inventory_add_object(in, NO_ID) == ERROR);

    inventory_destroy(in);
}

void test3_inventory_add_object()
{
    Inventory *in = NULL;

    PRINT_TEST_RESULT(inventory_add_object(in, 4) == ERROR);
}

void test1_inventory_is_object()
{
    Inventory *in;
    in = inventory_create();
    inventory_set_object(in, 2);

    PRINT_TEST_RESULT(inventory_is_object(in, 2) == OK);

    inventory_destroy(in);
}

void test2_inventory_is_object()
{
    Inventory *in;
    in = inventory_create();

    PRINT_TEST_RESULT(inventory_is_object(in, 5) == ERROR);

    inventory_destroy(in);
}

void test3_inventory_is_object()
{
    Inventory *in = NULL;

    PRINT_TEST_RESULT(inventory_is_object(in, 5) == ERROR);
}

void test1_inventory_delete_object()
{
    Inventory *in;
    in = inventory_create();
    inventory_set_object(in, 2);

    PRINT_TEST_RESULT(inventory_delete_object(in, 2) == OK);

    inventory_destroy(in);
}

void test2_inventory_delete_object()
{
    Inventory *in;
    in = inventory_create();

    PRINT_TEST_RESULT(inventory_delete_object(in, 6) == ERROR);

    inventory_destroy(in);
}

void test3_inventory_delete_object()
{
    Inventory *in = NULL;

    PRINT_TEST_RESULT(inventory_delete_object(in, 6) == ERROR);
}

void test1_inventory_get_maxobj()
{
    Inventory *in;
    in = inventory_create();

    PRINT_TEST_RESULT(inventory_get_maxobj(in) == 5); /*puesto por defecto*/

    inventory_destroy(in);
}

void test2_inventory_get_maxobj()
{
    Inventory *in = NULL;

    PRINT_TEST_RESULT(inventory_get_maxobj(in) == -1);
}

void test1_inventory_set_maxobj()
{
    Inventory *in;
    in = inventory_create();

    PRINT_TEST_RESULT(inventory_set_maxobj(in, 4) == OK);

    inventory_destroy(in);
}

void test2_inventory_set_maxobj()
{
    Inventory *in = NULL;

    PRINT_TEST_RESULT(inventory_set_maxobj(in, 4) == ERROR);
}

void test1_inventory_get_NumObjects()
{
    Inventory *in;
    in = inventory_create();
    inventory_set_object(in, 7);

    PRINT_TEST_RESULT(inventory_get_NumObjects(in) == 1);

    inventory_destroy(in);
}

void test2_inventory_get_NumObjects()
{
    Inventory *in = NULL;

    PRINT_TEST_RESULT(inventory_get_NumObjects(in) == -1);
}

void test3_inventory_get_NumObjects()
{
    Inventory *in;
    in = inventory_create();

    PRINT_TEST_RESULT(inventory_get_NumObjects(in) == 0);

    inventory_destroy(in);
}

void test1_inventory_print()
{
    Inventory *in;
    in = inventory_create();
    
    PRINT_TEST_RESULT(inventory_print(in) == OK);  /*No hace falta*/

    inventory_destroy(in);
}

void test2_inventory_print()
{
    Inventory *in = NULL;
    PRINT_TEST_RESULT(inventory_print(in) == ERROR);
}
