#include <stdio.h>
#include <stdlib.h>
#include "game_reader.h"
#include "game_reader_test.h"
#include "test.h"

#define MAX_TESTS 12

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
        test1_game_load_spaces();
    if (all || test == 2)
        test2_game_load_spaces();
    if (all || test == 3)
        test3_game_load_spaces();
    if (all || test == 4)
        test1_game_load_objects();
    if (all || test == 5)
       test2_game_load_objects();
    if (all || test == 6)
       test3_game_load_objects();
    if (all || test == 7)
        test1_game_load_players();
    if (all || test == 8)
        test2_game_load_players();
    if (all || test == 9)
        test3_game_load_players();
    if (all || test == 10)
        test1_game_load_links();
    if (all || test == 11)
        test2_game_load_links();
    if (all || test == 12)
        test3_game_load_links();

        PRINT_PASSED_PERCENTAGE;

        return 1;
}

void test1_game_load_spaces()
{
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_load_spaces(g,"Hola") == OK);
    game_destroy(g);
    
}

void test2_game_load_spaces()
{
    Game *g;
    g=game_create();
    PRINT_TEST_RESULT(game_load_spaces(g,"") == ERROR);
    game_destroy(g);
}

void test3_game_load_spaces()
{
    Game *g=NULL;
    PRINT_TEST_RESULT(game_load_spaces(g,"Hola") == ERROR);
}

void test1_game_load_objects()
{
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_load_objects(g,"Hola") == OK);
    game_destroy(g);
    
}

void test2_game_load_objects()
{
    Game *g;
    g=game_create();
    PRINT_TEST_RESULT(game_load_objects(g,"") == ERROR);
    game_destroy(g);
}

void test3_game_load_objects()
{
    Game *g=NULL;
    PRINT_TEST_RESULT(game_load_objects(g,"Hola") == ERROR);

}

void test1_game_load_players()
{
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_load_players(g,"Hola") == OK);
    game_destroy(g);
    
}

void test2_game_load_players()
{
    Game *g;
    g=game_create();
    PRINT_TEST_RESULT(game_load_players(g,"") == ERROR);
    game_destroy(g);
}

void test3_game_load_players()
{
    Game *g=NULL;
    PRINT_TEST_RESULT(game_load_players(g,"Hola") == ERROR);

}

void test1_game_load_links()
{
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_load_links(g,"Hola") == OK);
    game_destroy(g);
    
}

void test2_game_load_links()
{
    Game *g;
    g=game_create();
    PRINT_TEST_RESULT(game_load_links(g,"") == ERROR);
    game_destroy(g);
}

void test3_game_load_links()
{
    Game *g=NULL;
    PRINT_TEST_RESULT(game_load_links(g,"Hola") == ERROR);

}