#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include "Use.h"


/**
 * @brief makes the proceedment for the "use" command
 *
 *
 * @return creates a new table
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
void ShowUseMenu(char *tablename)
{
    int lenght = -1;
    printf("Enter the name of the table you want to use >");
    if (!fgets(tablename, 30, stdin))
    {
        /* reading input failed, give up: */
        printf("Sorry! There was an error with the table name");
    }
    lenght = strlen(tablename);
    tablename[lenght-1] = '\0';
    if (!createTable(tablename))
    {
        printf("Sorry! There was a problem creating the table");
        return;
    }

    return;
}


/**
 * @brief replaces end of name to .idx
 *
 *
 * @return void
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
void replaceExtensionByIdx(const char *fileName, char *indexName)
{
    int lenght;
    strcpy(indexName, fileName);
    lenght = strlen(fileName);
    indexName[lenght - 3] = 'i';
    indexName[lenght - 2] = 'd';
    indexName[lenght - 1] = 'x';
    return;
}
/**
 * @brief creates a table
 *
 *
 * @return error handle
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
bool createTable(const char *tableName)
{
    FILE *f = NULL;
    int init = -1;
    char indexName[30];
    if (tableName == NULL)
    {
        return false;
    }

    f = fopen(tableName, "rb");
    if (!f)
    {
        f = fopen(tableName, "wb");
        if (!f)
            return false;
        fwrite(&init, sizeof(int), 1, f); /*Como hago un control de errores de esto?*/
    }
    fclose(f);
    replaceExtensionByIdx(tableName, indexName);
    return createIndex(indexName);
}
/**
 * @brief creates an index file
 *
 *
 * @return error handle
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
bool createIndex(const char *indexName)
{
    FILE *f = NULL;
    int init = -1;
    if (indexName == NULL)
    {
        return false;
    }
    f = fopen(indexName, "rb");
    if (!f)
    {
        f = fopen(indexName, "wb");
        if (!f)
            return false;
        fwrite(&init, sizeof(int), 1, f); /*Como hago un control de errores de esto?*/
        fwrite(&init, sizeof(int), 1, f); /*Como hago un control de errores de esto?*/
    }
    fclose(f);
    return true;
}
