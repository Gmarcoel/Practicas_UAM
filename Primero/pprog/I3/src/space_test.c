/***
 * @brief Space functions library
 * @file space_test.c
 * @author Gabriela Trabajo
 * @version 1.0 
 * @date 13/04/20
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "space.h"
#include "space_test.h"
#include "test.h"
#include <string.h>

#define MAX_TESTS 57

/** 
 * @brief Main function for SPACE unit tests. 
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
        printf("Running all test for module Space:\n");
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
        test_space_create();
    if (all || test == 2)
        test1_space_set_name();
    if (all || test == 3)
        test2_space_set_name();
    if (all || test == 4)
        test3_space_set_name();
    if (all || test == 5)
        test1_space_set_icon();
    if (all || test == 6)
        test2_space_set_icon();
    if (all || test == 7)
        test3_space_set_icon();
    if (all || test == 8)
        test1_space_set_icon2();
    if (all || test == 9)
        test2_space_set_icon2();
    if (all || test == 10)
        test3_space_set_icon2();
    if (all || test == 11)
        test1_space_set_icon3();
    if (all || test == 12)
        test2_space_set_icon3();
    if (all || test == 13)
        test3_space_set_icon3();
    if (all || test == 14)
        test1_space_set_linkNorth();
    if (all || test == 15)
        test2_space_set_linkNorth();
    if (all || test == 16)
        test1_space_set_linkSouth();
    if (all || test == 17)
        test2_space_set_linkSouth();
    if (all || test == 18)
        test1_space_set_linkEast();
    if (all || test == 19)
        test2_space_set_linkEast();
    if (all || test == 20)
        test1_space_set_linkWest();
    if (all || test == 21)
        test2_space_set_linkWest();
    if (all || test == 22)
        test1_space_get_name();
    if (all || test == 23)
        test2_space_get_name();
    if (all || test == 24)
        test1_space_set_description();
    if (all || test == 25)
        test2_space_set_description();
    if (all || test == 26)
        test3_space_set_description();
    if (all || test == 27)
        test1_space_get_description();
    if (all || test == 28)
        test2_space_get_description();
    if (all || test == 29)
        test1_space_get_icon();
    if (all || test == 30)
        test2_space_get_icon();
    if (all || test == 31)
        test1_space_get_icon2();
    if (all || test == 32)
        test2_space_get_icon2();
    if (all || test == 33)
        test1_space_get_icon3();
    if (all || test == 34)
        test2_space_get_icon3();
    if (all || test == 35)
        test1_space_get_id();
    if (all || test == 36)
        test2_space_get_id();
    if (all || test == 37)
        test1_space_get_linkNorth();
    if (all || test == 38)
        test2_space_get_linkNorth();
    if (all || test == 39)
        test1_space_get_linkSouth();
    if (all || test == 40)
        test2_space_get_linkSouth();
    if (all || test == 41)
        test1_space_get_linkEast();
    if (all || test == 42)
        test2_space_get_linkEast();
    if (all || test == 43)
        test1_space_get_linkWest();
    if (all || test == 44)
        test2_space_get_linkWest();
    if (all || test == 45)
        test1_space_add_object();
    if (all || test == 46)
        test2_space_add_object();
    if (all || test == 47)
        test3_space_add_object();
    if (all || test == 48)
        test1_space_del_object();
    if (all || test == 49)
        test2_space_del_object();
    if (all || test == 50)
        test3_space_del_object();
    if (all || test == 51)
        test1_space_get_objects();
    if (all || test == 52)
        test2_space_get_objects();
    if (all || test == 53)
        test1_space_is_object();
    if (all || test == 54)
        test2_space_is_object();
    if (all || test == 55)
        test3_space_is_object();
    if (all || test == 56)
        test1_space_get_object_set();
    if (all || test == 57)
        test2_space_get_object_set();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_space_create()
{

    Space *s;
    s = space_create(1);

    PRINT_TEST_RESULT(s != NULL);

    space_destroy(s);
}

void test1_space_set_name()
{

    Space *s;
    char name[10];
    strcpy(name, "dos");

    s = space_create(2);

    PRINT_TEST_RESULT(space_set_name(s, name) == OK);

    space_destroy(s);
}

void test2_space_set_name()
{

    Space *s;
    s = space_create(3);

    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);

    space_destroy(s);
}

void test3_space_set_name()
{

    Space *s = NULL;
    char name[10];

    strcpy(name, "cuatro");

    PRINT_TEST_RESULT(space_set_name(s, name) == ERROR);
}

void test1_space_set_icon()
{
    Space *s;
    char icon[10];
    strcpy(icon, ":D");
    s = space_create(5);

    PRINT_TEST_RESULT(space_set_icon(s, icon) == OK);

    space_destroy(s);
}

void test2_space_set_icon()
{
    Space *s;
    s = space_create(6);

    PRINT_TEST_RESULT(space_set_icon(s, NULL) == ERROR);

    space_destroy(s);
}

void test3_space_set_icon(){

    Space *s = NULL;
    char icon[10];

    strcpy(icon, ":D");

    PRINT_TEST_RESULT(space_set_icon(s, icon) == ERROR);
}

void test1_space_set_icon2()
{

    Space *s;
    char icon[10];
    strcpy(icon, ":D");
    s = space_create(7);

    PRINT_TEST_RESULT(space_set_icon2(s, icon) == OK);

    space_destroy(s);
}

void test2_space_set_icon2() {

    Space *s;
    s = space_create(8);

    PRINT_TEST_RESULT(space_set_icon2(s, NULL) == ERROR);

    space_destroy(s);
}

void test3_space_set_icon2()
{
    Space *s = NULL;
    char icon[10];

    strcpy(icon, ":D");

    PRINT_TEST_RESULT(space_set_icon2(s, icon) == ERROR);
}

void test1_space_set_icon3()
{
    Space *s;
    char icon[10];
    strcpy(icon, ":D");
    s = space_create(9);

    PRINT_TEST_RESULT(space_set_icon3(s, icon) == OK);

    space_destroy(s);
}

void test2_space_set_icon3() 
{
    Space *s;
    s = space_create(10);

    PRINT_TEST_RESULT(space_set_icon3(s, NULL) == ERROR);

    space_destroy(s);
}

void test3_space_set_icon3()
{
    Space *s = NULL;
    char icon[10];

    strcpy(icon, ":D");

    PRINT_TEST_RESULT(space_set_icon3(s, icon) == ERROR);
}

void test1_space_set_linkNorth()
{
    Space *s;
    s = space_create(11);

    PRINT_TEST_RESULT(space_set_linkNorth(s, 5) == OK);

    space_destroy(s);
}

void test2_space_set_linkNorth()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_set_linkNorth(s, 7) == ERROR);
}

void test1_space_set_linkSouth()
{
    Space *s;
    s = space_create(11);

    PRINT_TEST_RESULT(space_set_linkSouth(s, 5) == OK);

    space_destroy(s);
}

void test2_space_set_linkSouth()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_set_linkSouth(s, 7) == ERROR);
}

void test1_space_set_linkEast()
{
    Space *s;
    s = space_create(11);

    PRINT_TEST_RESULT(space_set_linkEast(s, 5) == OK);

    space_destroy(s);
}

void test2_space_set_linkEast()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_set_linkEast(s, 7) == ERROR);
}

void test1_space_set_linkWest()
{
    Space *s;
    s = space_create(11);

    PRINT_TEST_RESULT(space_set_linkWest(s, 5) == OK);

    space_destroy(s);
}

void test2_space_set_linkWest()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_set_linkWest(s, 7) == ERROR);
}

void test1_space_get_name()
{
    Space *s;
    char *name;
    s = space_create(12);

    name = space_get_name(s);

    PRINT_TEST_RESULT(name != NULL);

    space_destroy(s);
}

void test2_space_get_name()
{
    Space *s = NULL;
    char *name;

    name = space_get_name(s);

    PRINT_TEST_RESULT(name == NULL);
}

void test1_space_set_description()
{
    Space *s;
    char description[10];
    strcpy(description, "prueba");
    s = space_create(15);

    PRINT_TEST_RESULT(space_set_description(s, description) == OK);

    space_destroy(s);
}

void test2_space_set_description()
{
    Space *s;
    s = space_create(16);

    PRINT_TEST_RESULT(space_set_description(s, NULL) == ERROR);

    space_destroy(s);
}

void test3_space_set_description()
{
    Space *s = NULL;
    char description[10];

    strcpy(description, "prueba");

    PRINT_TEST_RESULT(space_set_description(s, description) == ERROR);
}

void test1_space_get_description()
{
    Space *s;
    char *description, aux[10];
    int cmp;
    s = space_create(16);

    strcpy(aux, "prueba");
    space_set_description(s, aux);
    description = space_get_description(s);

    cmp = strcmp(description, aux);

    PRINT_TEST_RESULT(cmp == 0);

    space_destroy(s);
}

void test2_space_get_description()
{
    Space *s = NULL;
    char *description;

    description = space_get_description(s);

    PRINT_TEST_RESULT(description == NULL);
}

void test1_space_get_icon()
{
    Space *s;
    const char *icon;
    char aux[10];
    int cmp;
    s = space_create(18);

    strcpy(aux, ":D");
    space_set_icon(s, aux);
    icon = space_get_icon(s);

    cmp = strcmp(icon, aux);

    PRINT_TEST_RESULT(cmp == 0);

    space_destroy(s);
}

void test2_space_get_icon()
{
    Space *s = NULL;
    const char *icon;

    icon = space_get_icon(s);

    PRINT_TEST_RESULT(icon == NULL);
}

void test1_space_get_icon2()
{
    Space *s;
    const char *icon;
    char aux[10];
    int cmp;
    s = space_create(18);

    strcpy(aux, ":D");
    space_set_icon2(s, aux);
    icon = space_get_icon2(s);

    cmp = strcmp(icon, aux);

    PRINT_TEST_RESULT(cmp == 0);

    space_destroy(s);
}

void test2_space_get_icon2()
{
    Space *s = NULL;
    const char *icon;

    icon = space_get_icon2(s);

    PRINT_TEST_RESULT(icon == NULL);
}

void test1_space_get_icon3()
{
    Space *s;
    const char *icon;
    char aux[10];
    int cmp;
    s = space_create(18);

    strcpy(aux, ":D");
    space_set_icon3(s, aux);
    icon = space_get_icon3(s);

    cmp = strcmp(icon, aux);

    PRINT_TEST_RESULT(cmp == 0);

    space_destroy(s);
}

void test2_space_get_icon3()
{
    Space *s = NULL;
    const char *icon;

    icon = space_get_icon3(s);

    PRINT_TEST_RESULT(icon == NULL);
}

void test1_space_get_id()
{
    Space *s;
    s = space_create(20);

    PRINT_TEST_RESULT(space_get_id(s) == 20);

    space_destroy(s);
}

void test2_space_get_id()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_get_linkNorth()
{
    Space *s;
    s = space_create(22);

    space_set_linkNorth(s, 3);

    PRINT_TEST_RESULT(space_get_linkNorth(s) == 3);

    space_destroy(s);
}

void test2_space_get_linkNorth()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_get_linkNorth(s) == NO_ID);
}

void test1_space_get_linkSouth()
{
    Space *s;
    s = space_create(23);

    space_set_linkSouth(s, 5);

    PRINT_TEST_RESULT(space_get_linkSouth(s) == 5);

    space_destroy(s);
}

void test2_space_get_linkSouth()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_get_linkSouth(s) == NO_ID);
}

void test1_space_get_linkEast()
{
    Space *s;
    s = space_create(23);

    space_set_linkEast(s, 5);

    PRINT_TEST_RESULT(space_get_linkEast(s) == 5);

    space_destroy(s);
}

void test2_space_get_linkEast()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_get_linkEast(s) == NO_ID);
}

void test1_space_get_linkWest()
{
    Space *s;
    s = space_create(23);

    space_set_linkWest(s, 5);

    PRINT_TEST_RESULT(space_get_linkWest(s) == 5);

    space_destroy(s);
}

void test2_space_get_linkWest()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_get_linkWest(s) == NO_ID);
}

void test1_space_add_object()
{
    Space *s;
    s = space_create(25);

    PRINT_TEST_RESULT(space_add_object(s, 4) == OK);

    space_destroy(s);
}

void test2_space_add_object()
{
    Space *s;
    s = space_create(25);

    PRINT_TEST_RESULT(space_add_object(s, NO_ID) == ERROR);

    space_destroy(s);
}

void test3_space_add_object()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_add_object(s, 6) == ERROR);
}

void test1_space_del_object()
{
    Space *s;
    s = space_create(27);

    space_add_object(s, 4);

    PRINT_TEST_RESULT(space_del_object(s, 4) == OK);

    space_destroy(s);
}

void test2_space_del_object()
{
    Space *s;
    s = space_create(27);

    PRINT_TEST_RESULT(space_del_object(s, 4) == ERROR);

    space_destroy(s);
}

void test3_space_del_object()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_del_object(s, 4) == ERROR);
}

void test1_space_get_objects()
{
    Space *s;
    Id *ids;
    s = space_create(28);

    space_add_object(s, 3);
    space_add_object(s, 4);
    ids = space_get_objects(s);

    PRINT_TEST_RESULT(ids[0] == 3 && ids[1] == 4);

    space_destroy(s);
}

void test2_space_get_objects()
{
    Space *s = NULL;
    Id *ids;

    ids = space_get_objects(s);

    PRINT_TEST_RESULT(ids == NULL);
}

void test1_space_is_object()
{
    Space *s;
    s = space_create(30);

    space_add_object(s, 2);

    PRINT_TEST_RESULT(space_is_object(s, 2) == OK);

    space_destroy(s);
}

void test2_space_is_object()
{
    Space *s;
    s = space_create(30);

    PRINT_TEST_RESULT(space_is_object(s, NO_ID) == ERROR);

    space_destroy(s);
}

void test3_space_is_object()
{
    Space *s = NULL;

    PRINT_TEST_RESULT(space_is_object(s, 3) == ERROR);
}

void test1_space_get_object_set()
{
    Space *s;
    Set *aux;
    s = space_create(31);

    aux = space_get_object_set(s);

    PRINT_TEST_RESULT(aux != NULL);

    space_destroy(s);
}

void test2_space_get_object_set()
{
    Space *s = NULL;
    Set *aux;

    aux = space_get_object_set(s);

    PRINT_TEST_RESULT(aux == NULL);
}