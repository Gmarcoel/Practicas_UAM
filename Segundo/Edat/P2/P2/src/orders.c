#include <string.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "orders.h"
#define BufferLength 512

/*Private functions*/
static int Open(SQLHDBC dbc);
static int Range(SQLHDBC dbc);
static int Detail(SQLHDBC dbc);
static int ShowOrdersSubMenu();

/**
 * @brief Prints orders menu and allows the user to select an option.
 *
 *
 * @return selected entry in the menu
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */
void ShowOrdersMenu(SQLHDBC dbc)
{
    int nChoice = 0;
    do
    {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice)
        {

        case 1:
        {
            (void)Open(dbc);
        }
        break;

        case 2:
        {

            (void)Range(dbc);
        }
        break;

        case 3:
        {

            (void)Detail(dbc);
        }
        break;

        case 4:
        {
            (void)printf("Bye Bye\n\n");
        }
        break;
        }
    } while (nChoice != 4);
}

/**
 * @brief Shows orders submenu options 
 *
 * @return selected option
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 *
 **/

int ShowOrdersSubMenu()
{
    int nSelected = 0;
    char buf[16];
    do
    {

        (void)printf(" (1) Open\n"
                     " (2) Range\n"
                     " (3) Detail\n"
                     " (4) Exit\n\n");
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

        if ((nSelected < 1) || (nSelected > 4))
        {
            (void)printf("%i ", nSelected);
            (void)printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

/**
 * @brief Returns all the orders with no shippeddate
 * @return order number of orders with not shippeddate
 * @date 18-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int Open(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    char y[BufferLength] = "";

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select ordernumber from orders where shippeddate is null order by ordernumber;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    (void)fflush(stdout);

    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        ret = SQLGetData(stmt, 1, SQL_CHAR, y, BufferLength, NULL);

        printf("%s\n", y);
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

    return EXIT_SUCCESS;
}

/**
 * @brief given two dates shows orders between both
 * @return ordernumber, orderdate and shippeddate of orders between input dates
 * @date 18-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int Range(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    char x1[BufferLength] = "";
    char x2[BufferLength] = "";
    char y[BufferLength] = "";
    char z[BufferLength] = "";
    char w[BufferLength] = "";

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select ordernumber, orderdate, shippeddate from orders where (orderdate <= ? and orderdate >= ?) or (orderdate >= ? and orderdate <= ?) order by ordernumber;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
    (void)fflush(stdout);
    (void)scanf("%s - %s", x1, x2);
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x1, 0, NULL);
    (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x2, 0, NULL);
    (void)SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x1, 0, NULL);
    (void)SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x2, 0, NULL);

    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        ret = SQLGetData(stmt, 1, SQL_CHAR, y, BufferLength, NULL);
        ret = SQLGetData(stmt, 2, SQL_CHAR, z, BufferLength, NULL);
        ret = SQLGetData(stmt, 3, SQL_CHAR, w, BufferLength, NULL);
        printf("%s ", y);
        printf("%s ", z);
        printf("%s\n", w);
    }

    if (y[0] == '\0')
    {
        printf("No results for given dates\n");
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

/**
 * @brief returns the details of the given order
 * @return orderdate, status, total cost, productcode, quantityordered and priceeach
 * @date 18-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int Detail(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL, stmt2 = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    int x = 0;
    char y[BufferLength] = "";
    char y2[BufferLength] = "";
    double z = 0;
    char w[BufferLength] = "";
    char w2[BufferLength] = "";
    char w3[BufferLength] = "";

    /* Allocate a statements handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    ret = SQLPrepare(stmt, (SQLCHAR *)"select o.orderdate, o.status, sum(od.quantityordered*od.priceeach) as amount from orderdetails od, orders o where o.ordernumber = ? and od.ordernumber = o.ordernumber group by o.orderdate, o.status;", SQL_NTS);

    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt2);
    ret = SQLPrepare(stmt2, (SQLCHAR *)"select productcode, quantityordered, priceeach from orderdetails where ordernumber = ? order by orderlinenumber;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter ordernumber > ");
    (void)fflush(stdout);
    (void)scanf("%i", &x);
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &x, 0, NULL);
    (void)SQLBindParameter(stmt2, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &x, 0, NULL);

    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {

        ret = SQLGetData(stmt, 1, SQL_CHAR, y, BufferLength, NULL);
        ret = SQLGetData(stmt, 2, SQL_CHAR, y2, BufferLength, NULL);
        ret = SQLGetData(stmt, 3, SQL_C_DOUBLE, &z, BufferLength, NULL);
        printf("Order Date=%s ", y);
        printf("- status=%s\n", y2);
        printf("Total sum = %f\n", z);
    }

    /*if no results*/
    if (y[0] == '\0')
    {
        printf("No results for given ordernumber\n");
    }

    (void)SQLCloseCursor(stmt);
    (void)fflush(stdin);
    (void)SQLExecute(stmt2);
    (void)SQLBindCol(stmt2, 1, SQL_C_CHAR, w, BufferLength, NULL);

    while (SQL_SUCCEEDED(ret = SQLFetch(stmt2)))
    {
        ret = SQLGetData(stmt2, 1, SQL_CHAR, w, BufferLength, NULL);
        ret = SQLGetData(stmt2, 2, SQL_CHAR, w2, BufferLength, NULL);
        ret = SQLGetData(stmt2, 3, SQL_CHAR, w3, BufferLength, NULL);
        printf("%s ", w);
        printf("%s ", w2);
        printf("%s\n", w3);
    }

    (void)SQLCloseCursor(stmt2);
    (void)fflush(stdin);
    printf("\n");

    /* free up statements handle */

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt2);
    if (!SQL_SUCCEEDED(ret2))
    {
        odbc_extract_error("", stmt2, SQL_HANDLE_STMT);
        return ret;
    }
    (void)getchar();
    return EXIT_SUCCESS;
}
