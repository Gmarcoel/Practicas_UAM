#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Insert.h"

/**
 * @brief makes the proceedment for the "insert" command
 *
 *
 * @return adds a new table entry
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
void ShowInsertMenu(char *tablename)
{
    char key[5];
    char title[64], indexname[30];
    FILE *f = NULL;
    Book *bo = NULL;

    printf("Enter the key you want to insert >");
    if (!fgets(key, 5, stdin))
    {
        /* reading input failed, give up: */
        printf("Sorry! There was an error while introducing the key");
    }
    getchar();
    printf("Enter the title you want to insert >");
    if (!fgets(title, 64, stdin))
    {
        /* reading input failed, give up: */
        printf("Sorry! There was an error while introducing the title");
    }

    f = fopen(tablename, "rb");
    if  (!f)
    {
        printf("You must use the command -use- first to create a table, this does not exist");
        return;
    } 
    
    fclose(f);

    bo = (Book *)malloc(sizeof(Book));
    bo->title = (char*)malloc(64*sizeof(char));
    strcpy(bo->title, title);
    bo->title_len = strlen(title)-1;
    strcpy(bo->book_id, key);

    replaceExtensionByIdx(tablename, indexname);

    if (!addTableEntry(bo, tablename, indexname))
    {
        printf("The table could not be created or it already existed");
        free(bo->title);
        free(bo);
        return;
    }
    free(bo->title);
    free(bo);
    return;
}
/**
 * @brief recursive function of find key. Finds the asked key from an index file
 *
 *
 * @return error handle
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */

bool findKeyRec(int id, FILE *f, const char *book_id, int *idoff)
{
    long offset = 8;
    int son = -1, cmp;
    char key[5];
    key[4] = '\0';
    if (id == -1)
        return false;
    *idoff = id;
    offset = 8 + (20 * id);
    rewind(f);
    fseek(f, offset, SEEK_SET);
    fread(&key[0], sizeof(char), 1, f);
    fread(&key[1], sizeof(char), 1, f);
    fread(&key[2], sizeof(char), 1, f);
    fread(&key[3], sizeof(char), 1, f);
    cmp = strcmp(key, book_id);
    if (cmp == 0)
    {

        fseek(f, 12, SEEK_CUR);
        fread(idoff, sizeof(int), 1, f);
        return true;
    }
    else if (cmp > 0)
    {
        fread(&son, sizeof(int), 1, f);
        return findKeyRec(son, f, book_id, idoff);
    }

    fseek(f, 4, SEEK_CUR);
    fread(&son, sizeof(int), 1, f);
    return findKeyRec(son, f, book_id, idoff);
}
/**
 * @brief Finds the asked key from an index file
 *
 *
 * @return error handle
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
bool findKey(const char *book_id, const char *indexName, int *nodeIDOrDataOffset)
{
    FILE *f = NULL;
    int root = -1;
    bool value;
    char book[5];
    book[0] = book_id[0];
    book[1] = book_id[1];
    book[2] = book_id[2];
    book[3] = book_id[3];
    book[4] = '\0';
    f = fopen(indexName, "rb");
    if (!f)
    {
        return false;
    }
    fread(&root, sizeof(int), 1, f);
    value = findKeyRec(root, f, book, nodeIDOrDataOffset);
    fclose(f);
    return value;
}
/**
 * @brief check if a offset of the data file has a deleted record
 *
 *
 * @return offset
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */

int checkDeleted(FILE *data, long off, int *lenght)
{
    int size = -1;
    int next = -1;
    long lnext;
    if (off == -1)
    {
        return -1;
    }
    fseek(data, off + 4, SEEK_SET);
    fread(&size, sizeof(int), 1, data);
    fflush(data);
    if (size >= *lenght)
    {

        *lenght = size;

        fflush(data);
        return off;
    }
    fseek(data, off, SEEK_SET);
    fread(&next, sizeof(int), 1, data);
    lnext = next;
    return checkDeleted(data, lnext, lenght);
}
/**
 * @brief add a node to a given index file
 *
 *
 * @return error handle
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */

bool addIndexEntry(char *book_id, int bookOffset, char const *indexName)
{
    FILE *index = NULL;     /*index file*/
    int son = -1;           /*just -1*/
    int father = -1;        /**/
    int id = -1;            /**/
    long loff = bookOffset; /**/
    int ioff = loff;        /**/
    char key[5];            /**/
    int cmp;                /**/
    int del, tempdel;       /**/
    int root;

    /*Find father node*/
    if (findKey(book_id, indexName, &father) == true)
        return false;

    index = fopen(indexName, "rb+");
    if (!index)
    {
        return false;
    }

    /*Check if deleted record*/
    fseek(index, 0, SEEK_SET);
    fread(&root, sizeof(int), 1, index);
    fread(&del, sizeof(int), 1, index);
    fflush(index);
    if (del != -1)
    {
        fseek(index, 8 + (20 * del) + 4, SEEK_SET);
        fread(&tempdel, sizeof(int), 1, index);
        fflush(index);
        fseek(index, 4, SEEK_SET);
        fwrite(&tempdel, sizeof(int), 1, index);
        fflush(index);
        id = del;
        loff = 8 + (20 * id);
    }

    else
    {
        /*id and index offset*/
        fseek(index, 0, SEEK_END);
        loff = ftell(index);
        id = ((loff - 8) / 20);
    }

    /*If no root*/
    if (root == -1)
    {
        fseek(index, 0, SEEK_SET);
        fwrite(&id, sizeof(int), 1, index);
    }

    /*new index*/
    fseek(index, loff, SEEK_SET);
    fwrite(book_id, PK_SIZE, 1, index);
    fwrite(&son, sizeof(int), 1, index);
    fwrite(&son, sizeof(int), 1, index);
    fwrite(&father, sizeof(int), 1, index);
    fwrite(&ioff, sizeof(int), 1, index);
    fflush(index);

    /*change father*/
    if (father != -1)
    {
        loff = 8 + (20 * father);
        fseek(index, loff, SEEK_SET);
        fread(&key[0], sizeof(char), 1, index);
        fread(&key[1], sizeof(char), 1, index);
        fread(&key[2], sizeof(char), 1, index);
        fread(&key[3], sizeof(char), 1, index);
        fflush(index);
        key[4] = '\0';
        cmp = strcmp(book_id, key);
        if (cmp < 0)
        {
            fseek(index, loff + 4, SEEK_SET);
        }
        else
        {
            fseek(index, loff + 8, SEEK_SET);
        }
        fwrite(&id, sizeof(int), 1, index);
        fflush(index);
    }
    /*Close*/
    fclose(index);
    return true;
}
/*Private function*/
void debugTable(const char *tableName);
/**
 * @brief add a book to a given table
 *
 *
 * @return error handle
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */

bool addTableEntry(Book *book, const char *dataName, const char *indexName)
{
    FILE *data = NULL;
    int father = -1;
    int del = -1,tempdel = -1;
    long ldel;
    int length = strlen(book->title), extra, l2, i;
    char titleAux[64];
    long offset;
    int ioff = -1;
    bool value;
    /*Check if key exists*/
    if (findKey(book->book_id, indexName, &father) == true)
        return false;

    data = fopen(dataName, "rb+");
    if (!data)
        return false;

    /*Check if deleted record exists*/
    fseek(data, 0, SEEK_SET);
    fread(&del, sizeof(int), 1, data);
    fflush(data);
    if (del != -1)
    {
        ldel = del;
        ioff = checkDeleted(data, ldel, &length);
        offset = ioff;
        fseek(data,offset,SEEK_SET);
        fread(&tempdel,sizeof(int),1,data);
        fflush(data);
        fseek(data,0,SEEK_SET);
        fwrite(&tempdel,sizeof(int),1,data);
        fflush(data);

    }
    if (ioff == -1)
    {
        /*saves offset*/
        fseek(data, 0, SEEK_END);
        offset = ftell(data);
        ioff = offset;
    }

    /*Title adjustment to deleted files*/
    extra = length - book->title_len;
    strcpy(titleAux, book->title);
    for (i = 0, l2 = book->title_len; i < extra; i++)
    {
        titleAux[l2 + i] = ' ';
        titleAux[l2 + i + 1] = '\0';
    }

    /*adds entry*/
    fseek(data, offset, SEEK_SET);
    fwrite((book->book_id), PK_SIZE, 1, data);
    fwrite(&(length), sizeof(int), 1, data);
    fwrite(titleAux, (length), 1, data);

    /*creates index*/
    value = addIndexEntry(book->book_id, ioff, indexName);
    fclose(data);
    return value;
}
/**
 * @brief debugging function that prints a .dat file
 *
 *
 * @return error handle
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */

void debugTable(const char *tableName)
{
    FILE *f = NULL;
    int l, i, j;
    long off;
    char key[5];
    char title;
    key[4] = '\0';

    printf("\n--------------------- INICIO --------------------------\n");
    f = fopen(tableName, "rb+");

    fread(&l, sizeof(int), 1, f);
    printf("%i\n", l);
    for (i = 0; i < 15; i++)
    {
        off = ftell(f);
        printf("%li|| ", off);
        fread(&key[0], sizeof(char), 1, f);
        printf("%c", key[0]);
        fread(&key[1], sizeof(char), 1, f);
        printf("%c", key[1]);
        fread(&key[2], sizeof(char), 1, f);
        printf("%c", key[2]);
        fread(&key[3], sizeof(char), 1, f);
        printf("%c ", key[3]);
        fread(&l, sizeof(int), 1, f);
        printf("%i ", l);
        for (j = 0; j < l; j++)
        {
            fread(&title, sizeof(char), 1, f);
            printf("%c ", title);
        }
        printf("\n");
    }
    printf("--------------------- FINAL --------------------------\n\n");
    fclose(f);
}