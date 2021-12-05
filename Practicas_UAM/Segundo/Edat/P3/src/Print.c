#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "Print.h"

/**
 * @brief makes the proceedment for the "print" command
 *
 *
 * @return prints all the information of a tree
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
void ShowPrintMenu(char *tablename)
{
    char indexname[30];
    FILE *f = NULL;

    f = fopen(tablename, "rb");
    if (!f)
    {
        printf("You must use the command -use- first to create a table, this does not exist");
        return;
    }

    fclose(f);

    replaceExtensionByIdx(tablename, indexname);
    printf("INDEXNAME %s\n",indexname);
    printTree(4, indexname);

    return;
}
/**
 * @brief prints a node
 *
 *
 * @return prints all the information of a tree
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */

void printnode(size_t level, FILE *indexFileHandler, int node_id, char side)
{
    size_t i = 0;
    int lk = -1, rk = -1, f = -1, off = -1;
    char key[5];
    long offset = 8;
    if (indexFileHandler == NULL)
        return;
    key[4] = '\0';
    while (i < level)
    {
        printf("    ");
        i++;
    }

    offset = offset + (node_id * 20);
    rewind(indexFileHandler);
    fseek(indexFileHandler, offset, SEEK_SET);

    fread(&key[0], sizeof(char), 1, indexFileHandler);
    fread(&key[1], sizeof(char), 1, indexFileHandler);
    fread(&key[2], sizeof(char), 1, indexFileHandler);
    fread(&key[3], sizeof(char), 1, indexFileHandler);
    fread(&lk, sizeof(int), 1, indexFileHandler);
    fread(&rk, sizeof(int), 1, indexFileHandler);
    fread(&f, sizeof(int), 1, indexFileHandler);
    fread(&off, sizeof(int), 1, indexFileHandler);
    fprintf(stdout, "%c %s (%d): %d\n", side, key, node_id, off);

    /*l MAR0 (2): 37*/

    return;
}
/**
 * @brief recursive function of printTree. Travels through all nodes of the tree and calls nodeprint
 *
 *
 * @return prints all the information of a tree
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */

void printTreeRec(FILE *f, int id, size_t level, size_t end, char side)
{
    long offset = 8;
    int idl = -1, idr = -1;
    offset = 8 + (20 * id) + 4;
    if (level > end || id == -1)
        return;
    rewind(f);
    fseek(f, offset, SEEK_SET);

    fread(&idl, sizeof(int), 1, f);
    fread(&idr, sizeof(int), 1, f);
    printnode(level, f, id, side);
    printTreeRec(f, idl, level + 1, end, 'l');
    printTreeRec(f, idr, level + 1, end, 'r');
}
/**
 * @brief Prints all the nodes of the given tree
 *
 *
 * @return prints all the information of a tree
 * @author Guillermo Martín-Coello & Gabriela Trabajo
 */
void printTree(size_t level, const char *indexName)
{
    FILE *f = NULL;
    int root = -1;
    f = fopen(indexName, "rwb+");
    if (!f)
        return;

    /*This part is not part of the code is just for debbuging purposes*/
    /*
    int i, l, r, fa, o;
    char key[5];
    key[4] = '\0';
    fread(&l, sizeof(int), 1, f);
    printf("%i ", l);
    fread(&r, sizeof(int), 1, f);
    printf("%i \n", r);
    for (i = 0; i < 11; i++)
    {
        fread(&key[0], sizeof(char), 1, f);
        printf("%c ", key[0]);
        fread(&key[1], sizeof(char), 1, f);
        printf("%c ", key[1]);
        fread(&key[2], sizeof(char), 1, f);
        printf("%c ", key[2]);
        fread(&key[3], sizeof(char), 1, f);
        printf("%c ", key[3]);
        fread(&l, sizeof(int), 1, f);
        printf("%i ", l);
        fread(&r, sizeof(int), 1, f);
        printf("%i ", r);
        fread(&fa, sizeof(int), 1, f);
        printf("%i ", fa);
        fread(&o, sizeof(int), 1, f);
        printf("%i \n", o);
    }
    rewind(f);
    */

    fread(&root, sizeof(int), 1, f);
    printTreeRec(f, root, 0, level, ' ');
    fclose(f);
    return;
}