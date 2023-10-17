#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 14

/** 
 * @brief Main function for OBJECT unit tests. 
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
        test1_object_create();
    if (all || test == 2)
        test1_object_create();
    if (all || test == 3)
        test1_object_set_name();
    if (all || test == 4)
        test2_object_set_name();
    if (all || test == 5)
        test3_object_set_name();
    if (all || test == 6)
        test1_object_get_name();
    if (all || test == 7)
        test2_object_get_name();
    if (all || test == 8)
        test1_object_get_id();
    if (all || test == 9)
        test2_object_get_id();
    if (all || test == 10)
        test1_object_set_description();
    if (all || test == 11)
        test2_object_set_description();
    if (all || test == 12)
        test3_object_set_description();
    if (all || test == 13)
        test1_object_get_description();
    if (all || test == 14)
        test2_object_get_description();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_object_create()
{

    Object *ob;
    Id id;
    id = 1;
    ob = object_create(id);

    PRINT_TEST_RESULT(ob != NULL);

    object_destroy(ob);
}

void test2_object_create()
{

    Object *ob;
    Id id;
    id = NO_ID;
    ob = object_create(id);

    PRINT_TEST_RESULT(ob == NULL);

    object_destroy(ob);
}

void test1_object_set_name()
{

    Object *ln;
    char *name = "uno";
    Id id;
    id = 1;
    ln = object_create(id);

    PRINT_TEST_RESULT(object_set_name(ln, name) == OK);

    object_destroy(ln);
}

void test2_object_set_name()
{

    Object *ln;
    Id id;
    id = 1;
    ln = object_create(id);

    PRINT_TEST_RESULT(object_set_name(ln, NULL) == ERROR);

    object_destroy(ln);
}

void test3_object_set_name()
{

    Object *ln = NULL;
    char *name = "uno";

    PRINT_TEST_RESULT(object_set_name(ln, name) == ERROR);
}

void test1_object_get_name()
{
    Object *ln;
    const char *name;
    Id id;
    id = 1;
    ln = object_create(id);

    name = object_get_name(ln);

    PRINT_TEST_RESULT(name != NULL);

    object_destroy(ln);
}

void test2_object_get_name()
{
    Object *ln = NULL;
    const char *name;

    name = object_get_name(ln);

    PRINT_TEST_RESULT(name == NULL);
}

void test1_object_get_id()
{

    Object *ln;
    Id id;
    id = 1;
    ln = object_create(id);

    PRINT_TEST_RESULT(object_get_id(ln) == 1);

    object_destroy(ln);
}

void test2_object_get_id()
{

    Object *ln = NULL;

    PRINT_TEST_RESULT(object_get_id(ln) == NO_ID);
}

void test1_object_set_description()
{

    Object *ln;
    Id id;
    id = 1;
    ln = object_create(id);
    object_set_description(ln, " ");

    PRINT_TEST_RESULT(object_set_description(ln, " ") == OK);

    object_destroy(ln);
}

void test2_object_set_description()
{

    Object *ln = NULL;

    object_set_description(ln, " ");

    PRINT_TEST_RESULT(object_set_description(ln, " ")  == ERROR);
}

void test3_object_set_description()
{

    Object *ln;
    Id id;
    id = 1;
    ln = object_create(id);

    PRINT_TEST_RESULT(object_set_description(ln, NULL) == ERROR);

    object_destroy(ln);
}

void test1_object_get_description()
{

    Object *ln;
    Id id;
    id = 1;
    ln = object_create(id);
    object_set_description(ln, " ");

    PRINT_TEST_RESULT(strcmp(object_get_description(ln)," ") == 0);

    object_destroy(ln);
}

void test2_object_get_description()
{

    Object *ln;
    Id id;
    id = 1;
    ln = object_create(id);
    object_set_description(ln, "k");

    PRINT_TEST_RESULT(strcmp(object_get_description(ln), " ") != 0);

    object_destroy(ln);
}