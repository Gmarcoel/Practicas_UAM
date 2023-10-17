#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

/* 
 * example 2 with a fixed query, results retrieved with SQLBindCol
 */

int main(void) {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* ODBC API return status */
    SQLSMALLINT columns = 0; /* number of columns in result-set */
    SQLUSMALLINT ucolumns = 0;
    SQLUSMALLINT i = 0;
    SQLINTEGER x = 0;
    #define BufferLength 512
    char y[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    /* simple query */
    ret = SQLExecDirect(stmt, (SQLCHAR*) "select x, y from a", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }
    /* How many columns are there */
    ret = SQLNumResultCols(stmt, &columns);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("Error getting number of columns", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    /* print the name of each column */
    ucolumns = (SQLUSMALLINT)columns;
    for (i = 1; i <= ucolumns; i++) {
        char buf[BufferLength] = "\0";
        ret = SQLDescribeCol(stmt, i, (SQLCHAR *) buf, BufferLength, NULL, NULL, NULL, NULL, NULL);
        if (!SQL_SUCCEEDED(ret)) {
            odbc_extract_error("Error in SQLDescribeCol", stmt, SQL_HANDLE_STMT);
            return ret;
        }
        printf("%s\t", buf);
    }
    printf("\n");

    ret = SQLBindCol(stmt, 1, SQL_C_SLONG, &x, 0, NULL);
    ret = SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR *) y, BufferLength, NULL);
    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%d\t%s\n", x, y);
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

