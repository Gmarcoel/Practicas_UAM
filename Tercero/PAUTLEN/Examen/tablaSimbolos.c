#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tablaSimbolos.h"
// #include <errno.h>

#define BUFFER_SIZE 100

char value_str[MAX_LONG_ID + 1];

/*************************************/
TablaSimbolos *initTablaSimbolos()
{
    TablaSimbolos *ts = NULL;
    ts = (TablaSimbolos *)malloc(sizeof(TablaSimbolos));
    if (!ts)
        return NULL;

    ts->global = creat_hash_table();

    if (!(ts->global))
    {
        freeTablaSimbolos(ts);
        return NULL;
    }

    ts->current = ts->global;

    return ts;
}

int estoyEnAmbitoGlobal(TablaSimbolos *ts)
{
    if (ts->global != ts->current) 
        return ERROR;
    return OK;
}

void freeTablaSimbolos(TablaSimbolos *ts)
{
    if (ts->global != ts->current)
    {
        hash_table_delete(ts->current);
    }
    hash_table_delete(ts->global);
    free(ts);
    return;
}

elementoTablaSimbolos *crear_elemento(char *lexema, CATEGORIA categoria, CLASE clase, TIPO tipo, int size,
                                      int n_locales, int local_position, int n_param, int param_position)
{
    elementoTablaSimbolos *elem = NULL;
    elem = (elementoTablaSimbolos *)malloc(sizeof(elementoTablaSimbolos));

    if (!elem)
        return NULL;

    strcpy(elem->lexema, lexema);
    elem->categoria = categoria;
    elem->clase = clase;
    elem->tipo = tipo;
    elem->size = size;
    elem->n_locales = n_locales;
    elem->local_position = local_position;
    elem->n_param = n_param;
    elem->param_position = param_position;

    return elem;
}

/*
    char lexema[BUFFER_SIZE]; // nombre
    CATEGORIA categoria;   // variable
    CLASE clase;    // int
    TIPO tipo;  // escalar
    int size; cambio el nombre de la variable para no poner una ñ como nombre de variable
    int n_locales;
    int local_posicion;
    int n_param;
    int param_position;
*/

void insertValue(FILE *fout, TablaSimbolos *ts, int *aux, char *key)
{
    add_node2HashTable(ts->current, key, strlen(key), aux);
    fprintf(fout, "%s\n", key);
}

int insertarTablaSimbolosAmbitos(TablaSimbolos *tabla, char *lexema, CATEGORIA categoria, CLASE clase, TIPO tipo, int size, int n_locales, int local_posicion, int n_param, int param_position)
{
    elementoTablaSimbolos *elem = crear_elemento(lexema, categoria, clase, tipo, size, n_locales, local_posicion, n_param, param_position);
    if (!elem)
        return ERROR;

    if (add_node2HashTable(tabla->current, lexema, strlen(lexema), elem) == -1)
        return ERROR;

    return OK;
}

elementoTablaSimbolos *buscarTablaSimbolosAmbitoActual(TablaSimbolos *tabla, char *lexema)
{
    return (elementoTablaSimbolos *)get_value_from_hstable(tabla->current, lexema, strlen(lexema));
}

elementoTablaSimbolos *buscarTablaSimbolosAmbitoGlobal(TablaSimbolos *tabla, char *lexema)
{
    return (elementoTablaSimbolos *)get_value_from_hstable(tabla->global, lexema, strlen(lexema));
}

int abrirAmbito(TablaSimbolos *tabla)
{
    if (!tabla)
        return ERROR;

    if (tabla->current != tabla->global)
    {
        fprintf(stderr, "Error: no se puede abrir una tabla local dentro de una tabla local\n");
        // fprintf(fout, "-1\t%s\n", i->key);

        return ERROR;
    }
    tabla->current = NULL;
    tabla->current = creat_hash_table();

    if (!(tabla->current)) {
        fprintf(stderr, "Error: no se puede abrir una tabla local, error al alocar memoria\n");
        return ERROR;
    }

    return OK;
}

int cerrarAmbito(TablaSimbolos *tabla)
{
    if (!tabla)
        return ERROR;

    if (tabla->current != tabla->global)
    {
        free(tabla->current);
        tabla->current = tabla->global;
    }
    else
    {
        fprintf(stderr, "Error: El ámbito que estás intentando cerrar es el global");
        return ERROR;
    }

    return OK;
}

/*void checkValue(FILE *fout, TablaSimbolos *ts, char *aux_value, Instruction *i)
{
    int exists;
    int *aux = NULL, *aux2 = NULL;

    // buscar nodo
    exists = exists_value_from_hstable(ts->current, i->key, strlen(i->key));
    // Si la key no existe
    if (!exists)
    {
        aux = NULL;
        aux = (int *)malloc(sizeof(int));
        *aux = atoi(aux_value);
        i->value = atoi(aux_value);
        if (i->value >= 0)
        {

            insertValue(fout, ts, aux, i->key);
        }
        // if instruction = cierre -999
        else if (i->value == -999 && (strcmp(i->key, "cierre") == 0))
        {
            // cerrar table
            hash_table_delete(ts->current);
            ts->current = ts->global;
            fprintf(fout, "%s\n", i->key);
            free(aux);
        }
        else
        {

            if (ts->current == ts->global)
            {
                add_node2HashTable(ts->global, i->key, strlen(i->key), aux);
                // Create local table
                ts->current = creat_hash_table();
                // Insert function in local table
                aux2 = NULL;
                aux2 = (int *)malloc(sizeof(int));
                *aux2 = *aux;
                insertValue(fout, ts, aux2, i->key);
            }
            else
            {
                fprintf(stderr, "Error: no se puede abrir una tabla local dentro de una tabla local\n");
                fprintf(fout, "-1\t%s\n", i->key);
            }
        }
    }
    // Si la key si existe
    else
    {

        fprintf(stderr, "Error: variable ya declarada\n");
        fprintf(fout, "-1\t%s\n", i->key);
    }
}*/

/* int *searchValue(FILE *fout, TablaSimbolos *ts, Instruction *i)
{
    elementoTablaSimbolos *value = NULL;
    value = (elementoTablaSimbolos *)get_value_from_hstable(ts->current, i->key, strlen(i->key));
    // Si no enconttramos el valor en la tabla
    if ((ts->current != ts->global) && (value == NULL))
    {
        value = (elementoTablaSimbolos *)get_value_from_hstable(ts->global, i->key, strlen(i->key));
    }
    if (value == NULL)
    {
        // Buscar en la global
        fprintf(stderr, "Error: %s not found\n", i->key);
        fprintf(fout, "%s\t-1\n", i->key);
    }
    else // Encontramos el valor en la tabla
    {
        if (value->clase == VECTOR)
            strcpy(value_str, "VECTOR");
        else
        {
            if (value->tipo == BOOLEAN)
                strcpy(value_str, "BOOLEAN");
            else
                strcpy(value_str, "INT");
        }
        fprintf(fout, "%s\t%s\n", i->key, value_str);
    }
    return value;
}
*/

// main pero ya no es main y ahora no sabemos que hacer con el
/*int tablaSimbolos(int argc, char **argv)
{
    FILE *fin = NULL, *fout = NULL;
    Instruction i;
    TablaSimbolos *ts = NULL;
    ts = initTablaSimbolos();
    char buffer[BUFFER_SIZE];
    char *aux_value = NULL;

    // Checking args
    if (argc != 3)
    {
        char err_msg[BUFFER_SIZE];
        sprintf(err_msg, "Usage: %s <input_file> <output_file>", argv[0]);
        perror(err_msg);
        return -1;
    }

    // Opening the input file
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    // Error control
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
        i.value = NULL;
        // int sscanf(const char *str, const char *format, ...)
        i.key = (char *)strtok(buffer, " \t\n");

        aux_value = strtok(NULL, " \t\n");

        // Si buscamos un valor
        if (!aux_value)
        {
            searchValue(fout, ts, &i);
        }
        else
        {
            checkValue(fout, ts, aux_value, &i);
        }
        n_line++;
    }
    freeTablaSimbolos(ts);

    fclose(fin);
    fclose(fout);
    return 0;
}*/