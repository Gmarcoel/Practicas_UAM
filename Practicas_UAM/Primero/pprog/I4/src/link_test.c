/***
 * @brief Link functions library
 * @file link_test.c
 * @author Gabriela Trabajo
 * @version 1.0 
 * @date 12/04/20
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 33

/** 
 * @brief Main function for LINK unit tests. 
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
        printf("Running all test for module Link:\n");
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
        test_link_create();
    if (all || test == 2)
        test1_link_set_idLink();
    if (all || test == 3)
        test2_link_set_idLink();
    if (all || test == 4)
        test1_link_set_name();
    if (all || test == 5)
        test2_link_set_name();
    if (all || test == 6)
        test2_link_set_name();
    if (all || test == 7)
        test1_link_set_id1();
    if (all || test == 8)
        test2_link_set_id1();
    if (all || test == 9)
        test3_link_set_id1();
    if (all || test == 10)
        test1_link_set_id2();
    if (all || test == 11)
        test2_link_set_id2();
    if (all || test == 12)
        test3_link_set_id2();
    if (all || test == 13)
        test1_link_set_connection();
    if (all || test == 14)
        test2_link_set_connection();
    if (all || test == 15)
        test3_link_set_connection();
    if (all || test == 16)
        test4_link_set_connection();
    if (all || test == 17)
        test1_link_set_status();
    if (all || test == 18)
        test2_link_set_status();
    if (all || test == 19)
        test3_link_set_status();
    if (all || test == 20)
        test1_link_get_idLink();
    if (all || test == 21)
        test2_link_get_idLink();
    if (all || test == 22)
        test1_link_get_name();
    if (all || test == 23)
        test2_link_get_name();
    if (all || test == 24)
        test1_link_get_id1();
    if (all || test == 25)
        test2_link_get_id1();
    if (all || test == 26)
        test1_link_get_id2();
    if (all || test == 27)
        test2_link_get_id2();
    if (all || test == 28)
        test1_link_get_status();
    if (all || test == 29)
        test2_link_get_status();
    if (all || test == 30)
        test1_link_get_otherId();
    if (all || test == 31)
        test2_link_get_otherId();
    if (all || test == 32)
        test3_link_get_otherId();
    if (all || test == 33)
        test4_link_get_otherId();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test_link_create()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(ln != NULL);

    link_destroy(ln);
}

void test1_link_set_idLink()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_idLink(ln, 1) == OK);

    link_destroy(ln);
}

void test2_link_set_idLink()
{

    Link *ln = NULL;

    PRINT_TEST_RESULT(link_set_idLink(ln, 1) == ERROR);
}

void test3_link_set_idLink()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_idLink(ln, NO_ID) == OK);

    link_destroy(ln);
}

void test1_link_set_name()
{

    Link *ln;
    char *name = "uno";
    ln = link_create();

    PRINT_TEST_RESULT(link_set_name(ln, name) == OK);

    link_destroy(ln);
}

void test2_link_set_name()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_name(ln, NULL) == ERROR);

    link_destroy(ln);
}

void test3_link_set_name()
{

    Link *ln = NULL;
    char *name = "uno";

    PRINT_TEST_RESULT(link_set_name(ln, name) == ERROR);
}

void test1_link_set_id1()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_id1(ln, 2) == OK);

    link_destroy(ln);
}

void test2_link_set_id1()
{

    Link *ln = NULL;

    PRINT_TEST_RESULT(link_set_id1(ln, 2) == ERROR);
}

void test3_link_set_id1()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_id1(ln, NO_ID) == ERROR);

    link_destroy(ln);
}

void test1_link_set_id2()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_id2(ln, 3) == OK);

    link_destroy(ln);
}

void test2_link_set_id2()
{

    Link *ln = NULL;

    PRINT_TEST_RESULT(link_set_id2(ln, 3) == ERROR);
}

void test3_link_set_id2()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_id2(ln, NO_ID) == ERROR);

    link_destroy(ln);
}

void test1_link_set_connection()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_connection(ln, 4, 5) == OK);

    link_destroy(ln);
}

void test2_link_set_connection()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_connection(ln, NO_ID, 6) == ERROR);

    link_destroy(ln);
}

void test3_link_set_connection()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_connection(ln, 7, NO_ID) == ERROR);

    link_destroy(ln);
}

void test4_link_set_connection()
{

    Link *ln = NULL;

    PRINT_TEST_RESULT(link_set_connection(ln, 8, 9) == ERROR);
}

void test1_link_set_status()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_status(ln, CLOSED) == OK);

    link_destroy(ln);
}

void test2_link_set_status()
{

    Link *ln;
    ln = link_create();

    PRINT_TEST_RESULT(link_set_status(ln, OPEN) == OK);

    link_destroy(ln);
}

void test3_link_set_status()
{

    Link *ln = NULL;

    PRINT_TEST_RESULT(link_set_status(ln, OPEN) == ERROR);
}

void test1_link_get_idLink()
{

    Link *ln;
    Id id;
    ln = link_create();
    link_set_idLink(ln, 3);

    PRINT_TEST_RESULT(link_get_idLink(ln) == 3);

    link_destroy(ln);
}

void test2_link_get_idLink()
{

    Link *ln = NULL;
    Id id;

    PRINT_TEST_RESULT(link_get_idLink(ln) == NO_ID);
}

void test1_link_get_name()
{
    Link *ln;
    const char *name;
    ln = link_create();

    name = link_get_name(ln);

    PRINT_TEST_RESULT(name != NULL);

    link_destroy(ln);
}

void test2_link_get_name()
{
    Link *ln = NULL;
    const char *name;

    name = link_get_name(ln);

    PRINT_TEST_RESULT(name == NULL);
}

void test1_link_get_id1()
{
    Link *ln;
    Id id;

    ln = link_create();
    link_set_id1(ln, 5);

    PRINT_TEST_RESULT(link_get_id1(ln) == 5);

    link_destroy(ln);
}

void test2_link_get_id1()
{
    Link *ln = NULL;
    Id id;

    id = link_get_id1(ln);

    PRINT_TEST_RESULT(id == NO_ID);
}

void test1_link_get_id2()
{
    Link *ln;
    Id id;

    ln = link_create();
    link_set_id2(ln, 4);

    PRINT_TEST_RESULT(link_get_id2(ln) == 4);

    link_destroy(ln);
}

void test2_link_get_id2()
{
    Link *ln = NULL;
    Id id;

    id = link_get_id2(ln);

    PRINT_TEST_RESULT(id == NO_ID);
}

void test1_link_get_status()
{
    Link *ln;
    CONNECTION con;

    ln = link_create();
    link_set_status(ln, OPEN);

    PRINT_TEST_RESULT(link_get_status(ln) == OPEN);

    link_destroy(ln);
}

void test2_link_get_status()
{

    Link *ln = NULL;
    CONNECTION con;

    con = link_get_status(ln);

    PRINT_TEST_RESULT(con == -1);
}

void test1_link_get_otherId()
{

    Link *ln;
    Id id;
    
    ln = link_create();
    link_set_connection(ln, 1, 2);

    PRINT_TEST_RESULT(link_get_otherId(ln, 1) == 2);

    link_destroy(ln);
}

void test2_link_get_otherId()
{

    Link *ln;
    Id id;

    ln = link_create();
    link_set_connection(ln, 1, 2);

    PRINT_TEST_RESULT(link_get_otherId(ln, 2) == 1);

    link_destroy(ln);
}

void test3_link_get_otherId()
{

    Link *ln = NULL;
    Id id;

    PRINT_TEST_RESULT(link_get_otherId(ln, 2) == NO_ID);
}

void test4_link_get_otherId()
{

    Link *ln;

    ln = link_create();
    link_set_connection(ln, 1, 2);

    PRINT_TEST_RESULT(link_get_otherId(ln, NO_ID) == NO_ID);

    link_destroy(ln);
}