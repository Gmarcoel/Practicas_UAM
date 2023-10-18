#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tabla.h"
// #include <errno.h>

#define BUFFER_SIZE 100

typedef struct Instruction
{
    char *key;
    int value;
} Instruction;

/*************************************/

int main(int argc, char **argv)
{
    FILE *fin = NULL, *fout = NULL;
    Instruction i;
    Hash_Table *global = creat_hash_table(), *current = global;
    char buffer[BUFFER_SIZE];
    char *aux_value = NULL;
    int *value = NULL;
    int exists;
    int *aux = NULL, *aux2 = NULL;

    /*Checking args*/
    if (argc != 3)
    {
        char err_msg[BUFFER_SIZE];
        sprintf(err_msg, "Usage: %s <input_file> <output_file>", argv[0]);
        perror(err_msg);
        return -1;
    }

    /*Openning the input file*/
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    /*Error control*/
    if (!fin)
    {
        char err_msg[BUFFER_SIZE];
        sprintf(err_msg, "Unable to open the file: %s ", argv[0]);
        perror(err_msg);
        return -1;
    }
    int n_line = 0;
    while (fgets(buffer, BUFFER_SIZE, fin) != NULL)
    {

        aux_value = NULL;
        i.value = 0;
        // int sscanf(const char *str, const char *format, ...)
        i.key = (char *)strtok(buffer, " \t\n");

        aux_value = strtok(NULL, " \t\n");

        /* Si buscamos un valor*/
        if (!aux_value)
        {
            value = NULL;
            value = (int *)get_value_from_hstable(current, i.key, strlen(i.key));
            /*Si no enconttramos el valor en la tabla */

            if ((current != global) && (value == NULL))
            {
                value = (int *)get_value_from_hstable(global, i.key, strlen(i.key));
            }
            if (value == NULL)
            {
                /*Buscar en la global*/

                fprintf(stderr, "Error: %s not found\n", i.key);
                fprintf(fout, "%s\t-1\n", i.key);
            }
            else /*Encontramos el valor en la tabla*/
            {
                fprintf(fout, "%s\t%d\n", i.key, *value);
            }
        }
        else
        {
            //buscar nodo
            exists = exists_value_from_hstable(current, i.key, strlen(i.key));

            /* Si la key no existe */
            if (!exists)
            {
                aux = NULL;
                aux = (int *)malloc(sizeof(int));
                *aux = atoi(aux_value);
                i.value = atoi(aux_value);

                if (i.value >= 0)
                {
                    add_node2HashTable(current, i.key, strlen(i.key), aux);
                    fprintf(fout, "%s\n", i.key);
                }

                /*if instruction = cierre -999*/
                else if (i.value == -999 && (strcmp(i.key, "cierre") == 0))
                {
                    //cerrar table
                    hash_table_delete(current);
                    current = global;
                    fprintf(fout, "%s\n", i.key);
                    free(aux);
                }
                else
                {

                    if (current == global)
                    {
                        add_node2HashTable(global, i.key, strlen(i.key), aux);
                        /* Create local table */
                        current = creat_hash_table();
                        /* Insert function in local table */
                        aux2 = NULL;
                        aux2 = (int *)malloc(sizeof(int));
                        *aux2 = *aux;

                        add_node2HashTable(current, i.key, strlen(i.key), aux2);
                        fprintf(fout, "%s\n", i.key);
                    }
                    else
                    {
                        fprintf(stderr, "Error: no se puede abrir una tabla local dentro de una tabla local\n");
                        fprintf(fout, "-1\t%s\n", i.key);
                    }
                }
            }
            /* Si la key si existe */
            else
            {

                fprintf(stderr, "Error: variable ya declarada\n");
                fprintf(fout, "-1\t%s\n", i.key);
            }
        }
        n_line++;
    }
    if (current != global)
    {
        hash_table_delete(current);
        hash_table_delete(global);
    }
    else
    {
        hash_table_delete(global);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
