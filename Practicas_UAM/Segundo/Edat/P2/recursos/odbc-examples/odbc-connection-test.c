#include <stdlib.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

/* test database connection */

int main(void) {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLRETURN ret; /* ODBC API return status */
    #define BufferLength 1024
    char outstr[BufferLength] = "\0";
    SQLSMALLINT bufferLength = BufferLength;
    SQLSMALLINT outstrlen = 0;

    /* Allocate an environment handle */
    ret = SQLAllocHandle(SQL_HANDLE_ENV, (SQLHANDLE *) SQL_NULL_HANDLE, &env);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", env, SQL_HANDLE_ENV);
        return ret;
    }
    /* We want ODBC 3 support */
    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("Error setting odbc version", env, SQL_HANDLE_ENV);
        return ret;
    }
    /* Allocate a connection handle */
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", dbc, SQL_HANDLE_DBC);
        return ret;
    }
    /* Connect to the DSN mydsn */
    ret = SQLDriverConnect(dbc, (SQLHWND *) NULL, (SQLCHAR*) "DRIVER={PostgreSQL ANSI};DATABASE=test01;SERVER=localhost;PORT=5432;UID=alumnodb;PWD=alumnodb;", SQL_NTS, (SQLCHAR *) outstr, bufferLength, &outstrlen,
                           SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", dbc, SQL_HANDLE_DBC);
        return ret;
    }

    if (SQL_SUCCEEDED(ret)) {
        printf("Connected\n");
        printf("Returned connection string was:\n\t%s\n", outstr);
        if (ret == SQL_SUCCESS_WITH_INFO) {
            printf("Driver reported the following diagnostics\n");
            odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
        }
    } else {
        fprintf(stderr, "Failed to connect\n");
        odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
    }
    /* disconnect from database and free up allocated handles */
    /* Disconnect from database */
    ret = SQLDisconnect(dbc);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", dbc, SQL_HANDLE_DBC);
        return ret;
    }

    /* Free connection handle */
    ret = SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", dbc, SQL_HANDLE_DBC);
        return ret;
    }

    /* Free environment handle */
    ret = SQLFreeHandle(SQL_HANDLE_ENV, env);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", env, SQL_HANDLE_ENV);
        return ret;
    }


    return EXIT_SUCCESS;
}
