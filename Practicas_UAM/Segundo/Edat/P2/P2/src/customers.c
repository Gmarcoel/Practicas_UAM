#include <string.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "customers.h"
#define BufferLength 512

/*Private functions*/
static int Find(SQLHDBC dbc);
static int Products(SQLHDBC dbc);
static int Balance(SQLHDBC dbc);
static int ShowCustomersSubMenu();

/**
 * @brief Prints customers menu and allows the user to select an option.
 *
 *
 * @return selected entry in the menu
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */
void ShowCustomersMenu(SQLHDBC dbc)
{
    int nChoice = 0;
    do
    {
        nChoice = ShowCustomersSubMenu();
        switch (nChoice)
        {

        case 1:
        {
            (void)Find(dbc);
        }
        break;

        case 2:
        {

            (void)Products(dbc);
        }
        break;

        case 3:
        {

            (void)Balance(dbc);
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
 * @brief Shows customers submenu options 
 *
 * @return selected option
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 *
 **/

int ShowCustomersSubMenu()
{
    int nSelected = 0;
    char buf[16];
    do
    {

        (void)printf(" (1) Find\n"
                     " (2) Products\n"
                     " (3) Balance\n"
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
 * @brief Returns the customer and contact information from the contacts whose name or lastname have the given string inside
 * @return customernumber, customername, contactfirstname, contactlastname
 * @date 18-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int Find(SQLHDBC dbc)
{

    SQLHSTMT stmt = NULL;
    int ret = 0;
    SQLRETURN ret2; /* ODBC API return status */
    int offset = 0;
    char move = '\0';
    char x[BufferLength] = "";
    char y[BufferLength] = "";
    char y2[BufferLength] = "";
    char y3[BufferLength] = "";
    char y4[BufferLength] = "";

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select customernumber, customername, contactfirstname, contactlastname from customers where (contactfirstname like '%' || ? || '%') or (contactlastname like '%' || ? || '%') limit 10 offset ?;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer name > ");
    (void)fflush(stdout);
    (void)scanf("%s", x);
    printf("\n");

    while (move != '1')
    {
        printf("Lines %i to %i\n\n", offset + 1, offset + 10);
        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x, 0, NULL);
        (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x, 0, NULL);
        (void)SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);

        (void)fflush(stdout);
        (void)SQLExecute(stmt);

        (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);
        (void)SQLBindCol(stmt, 2, SQL_C_CHAR, y2, BufferLength, NULL);
        (void)SQLBindCol(stmt, 3, SQL_C_CHAR, y3, BufferLength, NULL);
        (void)SQLBindCol(stmt, 4, SQL_C_CHAR, y4, BufferLength, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
        {
            ret = SQLGetData(stmt, 1, SQL_CHAR, y, BufferLength, NULL);
            ret = SQLGetData(stmt, 2, SQL_CHAR, y2, BufferLength, NULL);
            ret = SQLGetData(stmt, 3, SQL_CHAR, y3, BufferLength, NULL);
            ret = SQLGetData(stmt, 4, SQL_CHAR, y4, BufferLength, NULL);

            printf("%s ", y);
            printf("%s ", y2);
            printf("%s ", y3);
            printf("%s\n", y4);
        }

        /*if no results*/
        if (y[0] == '\0')
        {
            printf("No results for given customername\n");
        }

        (void)SQLCloseCursor(stmt);
        (void)fflush(stdin);
        printf("\n");

        printf("< previous page \n> next page\n1 end\n");
        (void)fflush(stdout);
        (void)getchar();
        (void)scanf("%c", &move);
        if (move == '<' && offset > 0)
        {
            offset = offset - 10;
        }
        if (move == '>')
        {
            offset = offset + 10;
        }
        printf("\n");
    }
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
 * @brief shows amount of each product ordered by a customer
 * @return productname, sum of quantityordered of each product
 * @date 19-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int Products(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    int x = 0;
    int offset = 0;
    char move = '\0';
    char y[BufferLength] = "";
    char z[BufferLength] = "";

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select p.productname, sum(od.quantityordered) from products p, orderdetails od, orders o where o.customernumber = ? and o.ordernumber = od.ordernumber and od.productcode = p.productcode group by p.productname, p.productcode order by p.productcode limit 10 offset ?;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer number > ");
    (void)fflush(stdout);
    (void)scanf("%i", &x);
    printf("\n");

    while (move != '1')
    {
        printf("Lines %i to %i\n\n", offset + 1, offset + 10);
        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &x, 0, NULL);
        (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);

        (void)SQLExecute(stmt);

        (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);
        (void)SQLBindCol(stmt, 2, SQL_C_CHAR, z, BufferLength, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
        {
            ret = SQLGetData(stmt, 1, SQL_CHAR, y, BufferLength, NULL);
            ret = SQLGetData(stmt, 2, SQL_CHAR, z, BufferLength, NULL);
            printf("%s ", y);
            printf("%s \n", z);
        }

        /*if no results*/
        if (y[0] == '\0')
        {
            printf("No results for given customernumber\n");
        }

        (void)SQLCloseCursor(stmt);
        printf("\n");

        printf("< previous page \n> next page\n1 end\n");
        (void)fflush(stdout);
        (void)getchar();
        (void)scanf("%c", &move);
        if (move == '<' && offset > 0)
        {
            offset = offset - 10;
        }
        if (move == '>')
        {
            offset = offset + 10;
        }
        printf("\n");
    }

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
 * @brief returns the balance of a given costumer
 * @return balance
 * @date 18-10-2020
 * @author Gabriela Trabajo & Guillermo Martín-Coello
 */

int Balance(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    int x = 0;
    char y[BufferLength] = "";

    /* Allocate a statements handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select (select sum(pa.amount) from payments pa where pa.customernumber = ?) - (select sum(od.quantityordered*od.priceeach) from orders o, orderdetails od where o.customernumber = ? and o.ordernumber = od.ordernumber);", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer number >  ");
    (void)fflush(stdout);
    (void)scanf("%i", &x);
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &x, 0, NULL);
    (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &x, 0, NULL);

    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, y, BufferLength, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        ret = SQLGetData(stmt, 1, SQL_CHAR, y, BufferLength, NULL);
        printf("Balance = %s \n", y);
    }

    /*if no results*/
    if (y[0] == '\0')
    {
        printf("No results for given customernumber\n");
    }

    (void)SQLCloseCursor(stmt);
    (void)fflush(stdin);
    printf("\n");

    /* free up statements handle */

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    (void)getchar();
    return EXIT_SUCCESS;
}
