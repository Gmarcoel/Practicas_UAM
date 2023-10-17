/***
 * @brief Player test functions
 * @file player_test.c
 * @author Javier López
 * @version 1.0 
 * @date 14/04/20
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 28

/** 
 * @brief Main function for PLAYER unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char **argv)
{

    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all test for module Object:\n");
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
        test1_player_create();
    if (all || test == 3)
        test2_player_create();
    if (all || test == 4)
        test1_player_set_name();
    if (all || test == 5)
        test2_player_set_name();
    if (all || test == 6)
        test3_player_set_name();
    if (all || test == 7)
        test1_player_get_name();
    if (all || test == 8)
        test2_player_get_name();
    if (all || test == 9)
        test1_player_get_id();
    if (all || test == 10)
        test2_player_get_id();
    if (all || test == 11)
        test1_player_set_location();
    if (all || test == 12)
        test2_player_set_location();
    if (all || test == 13)
        test3_player_set_location();
    if (all || test == 14)
        test1_player_get_location();
    if (all || test == 15)
        test2_player_get_location();
    if (all || test == 16)
        test1_player_add_object();
    if (all || test == 17)
        test2_player_add_object();
    if (all || test == 18)
        test3_player_add_object();
    if (all || test == 19)
        test1_player_del_object();
    if (all || test == 20)
        test2_player_del_object();
    if (all || test == 21)
        test3_player_del_object();
    if (all || test == 22)
        test1_player_get_objects();
    if (all || test == 23)
        test2_player_get_objects();
    if (all || test == 24)
        test1_player_get_inventory();
    if (all || test == 25)
        test2_player_get_inventory();
    if (all || test == 26)
        test1_player_is_object();
    if (all || test == 27)
        test2_player_is_object();
    if (all || test == 28)
        test3_player_is_object();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_player_create()
{

    Player *p;
    Id id;
    id = 1;
    p = player_create(id);

    PRINT_TEST_RESULT(p != NULL);

    player_destroy(p);
}

void test2_player_create()
{

    Player *p;
    Id id;
    id = NO_ID;
    p = player_create(id);

    PRINT_TEST_RESULT(p == NULL);

    player_destroy(p);
}

void test1_player_set_name()
{

    Player *p;
    char name[10];
    Id id;
    id = 1;
    p = player_create(id);
    strcpy(name, "uno");

    PRINT_TEST_RESULT(player_set_name(p, name) == OK);

    player_destroy(p);
}

void test2_player_set_name()
{

    Player *p;
    Id id;
    id = 1;
    p = player_create(id);

    PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);

    player_destroy(p);
}

void test3_player_set_name()
{

    Player *p = NULL;
    char name[10];

    strcpy(name, "uno");

    PRINT_TEST_RESULT(player_set_name(p, name) == ERROR);
}

void test1_player_get_name()
{
    Player *p;
    const char *name;
    Id id;
    id = 1;
    p = player_create(id);

    name = player_get_name(p);

    PRINT_TEST_RESULT(name != NULL);

    player_destroy(p);
}

void test2_player_get_name()
{
    Player *p = NULL;
    const char *name;

    name = player_get_name(p);

    PRINT_TEST_RESULT(name == NULL);
}

void test1_player_get_id()
{

    Player *p;
    Id id;
    id = 1;
    p = player_create(id);

    PRINT_TEST_RESULT(player_get_id(p) == 1);

    player_destroy(p);
}

void test2_player_get_id()
{

    Player *p = NULL;

    PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}

void test1_player_set_location()
{

    Player *p;
    Id id1, id2;
    id1 = 1;
    id2 = 2;
    p = player_create(id1);

    PRINT_TEST_RESULT(player_set_location(p,id2) == OK);

    player_destroy(p);
}

void test2_player_set_location()
{

    Player *p = NULL;
    Id id;
    id=1;
    
    PRINT_TEST_RESULT(player_set_location(p, id) == ERROR);
}

void test3_player_set_location()
{

    Player *p;
    Id id;
    id = NO_ID;
    p = player_create(id);

    PRINT_TEST_RESULT(player_set_location(p, id) == ERROR);

    player_destroy(p);
}

void test1_player_get_location()
{

    Player *p;
    Id id;
    id = 1;
    p = player_create(id);
    player_set_location(p,1);

    PRINT_TEST_RESULT(player_get_location(p) == 1);

    player_destroy(p);
}

void test2_player_get_location()
{
    Player *p = NULL;

    player_set_location(p,1);

    PRINT_TEST_RESULT(player_get_location(p) != 1);
}

void test1_player_add_object()
{
    Player *p;
    Id id;
    id=1;
    p = player_create(id);
    
    PRINT_TEST_RESULT(player_add_object(p, 3) == OK);
    
    player_destroy(p);
}

void test2_player_add_object()
{
    Player *p;
    Id id;
    id=1;
    p = player_create(id);

    PRINT_TEST_RESULT(player_add_object(p, NO_ID) == ERROR);

    player_destroy(p);
}
    
void test3_player_add_object()
{
    Player *p=NULL;
    
    PRINT_TEST_RESULT(player_add_object(p, 3) == ERROR);    
}


void test1_player_del_object()
{
    Player *p;
    Id id;
    id=1;
    p=player_create(id);
    player_add_object(p,id);
    PRINT_TEST_RESULT(player_del_object(p,id) == OK);
    player_destroy(p);
}

void test2_player_del_object()
{
    Player *p = NULL;
    Id id;
    id=1;
    player_add_object(p,id);
    PRINT_TEST_RESULT(player_del_object(p,id) == ERROR);
}

void test3_player_del_object()
{
    Player *p;
    Id id1, id2;
    id1=1;
    id2=NO_ID;
    p=player_create(id1);
    player_add_object(p,id1);
    PRINT_TEST_RESULT(player_del_object(p,id2) == ERROR);
    player_destroy(p);
}

void test1_player_get_objects()
{
    Player *p;
    Id id;
    id=1;
    p=player_create(id);
    player_add_object(p,id);
    PRINT_TEST_RESULT(player_get_objects(p) != NULL);
    player_destroy(p);
}

void test2_player_get_objects()
{
    Player *p;
    Id id;
    id=NO_ID;
    p=player_create(id);
    PRINT_TEST_RESULT(player_get_objects(p) == ERROR);
    player_destroy(p);
}

void test1_player_get_inventory()
{
    Player *p;
    Id id;
    id=1;
    p=player_create(id);
    player_add_object(p,id);
    PRINT_TEST_RESULT(player_get_inventory(p) != NULL);
    player_destroy(p);
}

void test2_player_get_inventory()
{
    Player *p;
    Id id;
    id=NO_ID;
    p=player_create(id);
    player_add_object(p,id);
    PRINT_TEST_RESULT(player_get_inventory(p) == ERROR);
    player_destroy(p);
}

void test1_player_is_object()
{
    Player *p;
    Id id;
    id=1;
    p=player_create(id);
    player_add_object(p,id);
    PRINT_TEST_RESULT(player_is_object(p,id) == OK);
    player_destroy(p);
}

void test2_player_is_object()
{
    Player *p;
    Id id;
    id=1;
    p=player_create(id);
    PRINT_TEST_RESULT(player_is_object(p, NO_ID) == ERROR);
    player_destroy(p);
}

void test3_player_is_object()
{
    Player *p = NULL;
    Id id;
    id=1;
    player_add_object(p,id);
    PRINT_TEST_RESULT(player_is_object(p,id) == ERROR);
}