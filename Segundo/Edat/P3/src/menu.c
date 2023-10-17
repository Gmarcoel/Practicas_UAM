#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "Use.h"
#include "Insert.h"
#include "Print.h"
#include "tester.h"

int ShowMainMenu();

/**
 * @brief Main function.
 *
 *
 * @return selected entry in the menu
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
int main(void)
{
    int nChoice = 0;
    char tablename[30] = " ";

    do
    {
        nChoice = ShowMainMenu();
        switch (nChoice)
        {
        case 1:
        {
            ShowUseMenu(tablename);
        }
        break;

        case 2:
        {
            ShowInsertMenu(tablename);
        }
        break;

        case 3:
        {
            ShowPrintMenu(tablename);
        }
        break;

        case 4:
        {
            maintest();
        }
        break;

        case 5:
        {
            printf("Bye Bye\n\n");
        }
        break;
        }
    } while (nChoice != 5);
    return 0;
}

/**
 * @brief prints main menu and allows to select an option.
 *
 *
 * @return selected entry in the menu
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
int ShowMainMenu()
{
    int nSelected = 0;
    char buf[16]; /* buffer for reading user input
                     in theory we only need 1 char
                     but a large buffer will handle
                     more gracefully wrong inputs
                     as 'qwerty' */

    do
    {
        printf("You can choose to create a table (use), insert on a table (insert) or print its content (print):\n\n");

        printf(" (1) Use\n"
               " (2) Insert\n"
               " (3) Print\n"
               " (4) Tests\n"
               " (5) Exit\n\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected = 0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 5))
        {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 5));

    return nSelected;
}