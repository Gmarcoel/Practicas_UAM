#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tabla.h"
#include "y.tab.h"

// #include <errno.h>
#ifndef TABLA_SIMBOLOS
#define TABLA_SIMBOLOS

#define BUFFER_SIZE 100

typedef struct TablaSimbolos
{
    Hash_Table *global;
    Hash_Table *current;
} TablaSimbolos;

typedef struct elemento
{
    char lexema[MAX_LONG_ID + 1]; // nombre
    CATEGORIA categoria;   // variable
    CLASE clase;    // int
    TIPO tipo;  // escalar
    int size; /*cambio el nombre de la variable para no poner una ñ como nombre de variable*/
    int n_locales;
    int local_position;
    int n_param;
    int param_position;

} elementoTablaSimbolos;

typedef struct Instruction
{
    char *key;
    elementoTablaSimbolos *value;
} Instruction;

/*************************************/
TablaSimbolos *initTablaSimbolos();
void freeTablaSimbolos(TablaSimbolos *ts);
void insertValue(FILE *fout, TablaSimbolos *ts, int *aux, char *key);
void checkValue(FILE *fout, TablaSimbolos *ts, char *aux_value, Instruction *i);
int *searchValue(FILE *fout, TablaSimbolos *ts, Instruction *i);
elementoTablaSimbolos *buscarTablaSimbolosAmbitoActual(TablaSimbolos *tabla, char *lexema);
elementoTablaSimbolos *buscarTablaSimbolosAmbitoGlobal(TablaSimbolos *tabla, char *lexema);
int insertarTablaSimbolosAmbitos(TablaSimbolos *tabla, char *lexema, CATEGORIA categoria, CLASE clase, TIPO tipo, int size, int n_locales, int local_posicion, int n_param, int param_position);
int abrirAmbito(TablaSimbolos *tabla);
int cerrarAmbito(TablaSimbolos *tabla);
int estoyEnAmbitoGlobal(TablaSimbolos *ts);

#endif