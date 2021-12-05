#include <stdio.h>
#include <stdlib.h>
#include "products.h"
#include "orders.h"
#include "customers.h"
#include "odbc.h"

static int ShowMainMenu();

/**
 * @brief Main function.
 *
 *
 * @return selected entry in the menu
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
int main(void) {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    int ret = 0;
    int nChoice = 0;
    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        return EXIT_FAILURE;
    }
    /*MENU*/
    do {
        nChoice = ShowMainMenu();
        switch (nChoice) {
            case 1: {
                ShowProductsMenu(dbc);
            }
                break;
            
            case 2: {
                ShowOrdersMenu(dbc);
            }
                break;

            case 3: {
                ShowCustomersMenu(dbc);
            }
                break;

            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);
    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        return EXIT_FAILURE;
    }
    return 0;
}

/**
 * @brief prints main menu and allows to select an option.
 *
 *
 * @return selected entry in the menu
 * @author rmarabini
 */

int ShowMainMenu() {
    int nSelected = 0;
    char buf[16]; /* buffer for reading user input
                     in theory we only need 1 char
                     but a large buffer will handle
                     more gracefully wrong inputs
                     as 'qwerty' */

    do {
        printf("This is a classic models program.\n");
        printf("You can choose to display the products, the orders or the clients:\n\n");

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Quit\n\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}