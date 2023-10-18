#ifndef _ALFA_H
#define _ALFA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG_ID 100
#define MAX_TAMANIO_VECTOR 64

typedef enum
{
    VARIABLE = 0,
    PARAMETRO,
    FUNCION
} CATEGORIA;

typedef enum
{
    INT = 0,
    BOOLEAN
} TIPO;

typedef enum
{
    ESCALAR = 0,
    VECTOR
} CLASE;

typedef struct
{
    char lexema[MAX_LONG_ID + 1];
    TIPO tipo;
    int valor_entero;
    int es_direccion;
    int etiqueta;
} tipo_atributos;

#define OK 1
#define ERROR 0

#endif