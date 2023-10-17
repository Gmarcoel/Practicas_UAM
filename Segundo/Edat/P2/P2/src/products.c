#include <string.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"
#define BufferLength 512

/*Private functions*/
static int PrintStock(SQLHDBC dbc);
static int PrintFind(SQLHDBC dbc);
static int ShowProductsSubMenu();

/**
 * @brief Prints products menu and allows the user to select an option.
 *
 *
 * @return selected entry in the menu
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */
void ShowProductsMenu(SQLHDBC dbc)
{
    int nChoice = 0;
    do
    {
        nChoice = ShowProductsSubMenu();
        switch (nChoice)
        {

        case 1:
        {
            (void)PrintStock(dbc);
        }
        break;

        case 2:
        {

            (void)PrintFind(dbc);
        }
        break;

        case 3:
        {
            (void)printf("Bye Bye\n\n");
        }
        break;
        }
    } while (nChoice != 3);
}

/**
 * @brief Shows product submenu options 
 *
 * @return selected option
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 *
 **/

int ShowProductsSubMenu()
{
    int nSelected = 0;
    char buf[16];
    do
    {

        (void)printf(" (1) Stock\n"
                     " (2) Find\n"
                     " (3) Back\n");
        (void)printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected = 0;

        else
        {
            /* have some input, convert it to integer: */
            nSelected = atoi((char *)buf);
        }
        (void)printf("\n");

        if ((nSelected < 1) || (nSelected > 3))
        {
            (void)printf("%i ", nSelected);
            (void)printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 3));

    return nSelected;
}

/**
 * @brief Finds the asked stock
 * @return number of units in stock of the asked product
 * @date 30-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int PrintStock(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    char x[BufferLength] = "";
    char y[BufferLength] = "";

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select quantityinstock from products where productcode = ?", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter productcode > ");
    (void)fflush(stdout);
    while (scanf("%s", x) == 0)
    {
        printf("Enter productcode > ");
        (void)fflush(stdout);
    }
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x, 0, NULL);

    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {

        printf("Quantity in stock = %s\n", y);
    }

    /*if no results*/
    if (y[0] == '\0')
    {
        printf("No results for given productcode\n");
    }

    (void)SQLCloseCursor(stmt);

    (void)fflush(stdin);
    printf("\n");

    /* free up statement handle */

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    (void)getchar();
    return EXIT_SUCCESS;
}

/**
 * @brief Finds the asked stock
 * @return number of units in stock of the asked product
 * @date 30-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int PrintFind(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    char x[BufferLength] = "";
    char y[BufferLength] = "";
    char z[BufferLength] = "";


    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select productcode, productname from products where productname like '%' || ? || '%' order by productcode;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter productname > ");
    (void)fflush(stdout);
    (void)scanf("%s", x);
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x, 0, NULL);

    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        ret = SQLGetData(stmt, 1, SQL_CHAR, y, BufferLength, NULL);
        ret = SQLGetData(stmt, 2, SQL_CHAR, z, BufferLength, NULL);
        printf("%s ", y);
        printf("%s\n", z);
    }

    /*if no results*/
    if (y[0] == '\0')
    {
        printf("No results for given productname\n");
    }

    (void)SQLCloseCursor(stmt);

    printf("\n");

    /* free up statement handle */

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    (void)getchar();
    return EXIT_SUCCESS;
}
