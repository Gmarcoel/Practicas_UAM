/**
 * @file generacion.c
 * @authors Guillermo Martín Coello, Ángel Quiles Vadillo, Guillermo de Andrés Pérez, Javier Wang Zhou
 * @date 23/09/2021
 * @brief C file to define all functions from header file generacion.h
 **/

#include "generacion.h"
#include <errno.h>

#define OK 1
#define ERR -1

/******* FIRST PART *******/
void escribir_cabecera_bss(FILE *fpasm)
{
    if (fpasm == NULL)
    {
        perror("Null file error in write bss function\n");
        return;
    }
    fprintf(fpasm, "\n; escribir_cabecera_bss:\n");

    fprintf(fpasm, "segment .bss \n; uninitalised varables\n");

    fprintf(fpasm, "\t__esp resd 1\n");
    return;
}

void escribir_subseccion_data(FILE *fpasm)
{
    if (fpasm == NULL)
    {
        perror("Null file error in write data function\n");
        return;
    }
    fprintf(fpasm, "\n; escribir_cabecera_data:\n");

    fprintf(fpasm, "segment .data \n; initialised varables\n");
    fprintf(fpasm, "\tfunc_dividir_error0_message db \"Division by zero\", 10,13,0\n");
    fprintf(fpasm, "\tvector_out_of_bounds_message db \"Vector index out of bounds\", 10,13,0\n\n");
    return;
}
/*
Declaración (con directiva db) de las variables que contienen el texto de los
mensajes para la identificación de errores en tiempo de ejecución.
En este punto, al menos, debes ser capaz de detectar la división por 0.
*/
void declarar_variable(FILE *fpasm, char *nombre, int tipo, int tamano)
{
    /*
    Para ser invocada en la sección .bss cada vez que se quiera declarar una
    variable:
    - El argumento nombre es el de la variable.
    - tipo puede ser ENTERO o BOOLEANO (observa la declaración de las constantes
    del principio del fichero).
    - Esta misma función se invocará cuando en el compilador se declaren
    vectores, por eso se adjunta un argumento final (tamano) que para esta
    primera práctica siempre recibirá el valor 1.
    */
    if (!fpasm || !nombre)
    {
        perror("ERROR:\"declarar_variable function arguments are NULL\"\n");
        return;
    }

    if ((tipo != 0 && tipo != 1) || tamano <= 0)
    {
        perror("ERROR: Type isn't ENTERO nor BOOLEANO\n");
        return;
    }

    if (tipo == ENTERO)
        fprintf(fpasm, "\t_%s resd %d", nombre, tamano);

    else if (tipo == BOOLEANO)
        fprintf(fpasm, "\t_%s resb %d", nombre, tamano);

    fprintf(fpasm, "\t; declarar_variable(%s, %d, %d):\n", nombre, tipo, tamano);
}
void escribir_segmento_codigo(FILE *fpasm)
{
    if (fpasm == NULL)
    {
        perror("Null file error in write code function\n");
        return;
    }
    fprintf(fpasm, "\n; escribir segmento codigo:\n");

    fprintf(fpasm, "segment .text\n");
    fprintf(fpasm, "global main\n");
    fprintf(fpasm, "extern print_int, print_boolean, print_string, print_blank, print_endofline, scan_int, scan_boolean\n");
    return;
}
/*
Para escribir el comienzo del segmento .text, básicamente se indica que se
exporta la etiqueta main y que se usarán las funciones declaradas en la librería
alfalib.o
*/

void escribir_inicio_main(FILE *fpasm)
{

    if (fpasm == NULL)
    {
        perror("Null file error in write code function\n");
        return;
    }
    fprintf(fpasm, "\n; escribir inicio main:\n");

    fprintf(fpasm, "main:\n");
    fprintf(fpasm, "\tmov [__esp], esp\n");
}
/*
En este punto se debe escribir, al menos, la etiqueta main y la sentencia que
guarda el puntero de pila en su variable (se recomienda usar __esp).
*/

void escribir_fin(FILE *fpasm)
{
    if (fpasm == NULL)
    {
        perror("Null file error in write end function\n");
        return;
    }
    fprintf(fpasm, "\n; escribir fin:\n");

    fprintf(fpasm, "end_prog:\n");
    fprintf(fpasm, "\tmov esp, [__esp]\n");
    fprintf(fpasm, "\tret\n");

    fprintf(fpasm, "\nfunc_dividir_error0:\n"); /* Division error control */
    fprintf(fpasm, "\tpush dword func_dividir_error0_message\n\tcall print_string\n\tcall print_endofline\n\tadd esp, 4\n\tjmp end_prog\n");

    fprintf(fpasm, "\nvector_out_of_bounds:\n"); /* Vector out of bounds error control */
    fprintf(fpasm, "\tpush dword vector_out_of_bounds_message\n\tcall print_string\n\tcall print_endofline\n\tadd esp, 4\n\tjmp end_prog\n");
}
/*
Al final del programa se escribe:
- El código NASM para salir de manera controlada cuando se detecta un error
en tiempo de ejecución (cada error saltará a una etiqueta situada en esta
zona en la que se imprimirá el correspondiente mensaje y se saltará a la
zona de finalización del programa).
- En el final del programa se debe:
·Restaurar el valor del puntero de pila (a partir de su variable __esp)
·Salir del programa (ret).
*/

void escribir_operando(FILE *fpasm, char *nombre, int es_variable)
{
    if (fpasm == NULL || nombre == NULL || es_variable == -1)
    {
        perror("Null file error in write operand function\n");
        return;
    }
    fprintf(fpasm, "\n\t; escribir operando(nombre=%s, es_variable=%d):\n", nombre, es_variable);

    if (es_variable == 1)
        fprintf(fpasm, "\tmov dword eax, _%s\n", nombre);
    else
        fprintf(fpasm, "\tmov dword eax, %s\n", nombre);
    fprintf(fpasm, "\tpush dword eax\n");
}
/*
Función que debe ser invocada cuando se sabe un operando de una operación
aritmético-lógica y se necesita introducirlo en la pila.
- nombre es la cadena de caracteres del operando tal y como debería aparecer
en el fuente NASM
- es_variable indica si este operando es una variable (como por ejemplo b1)
con un 1 u otra cosa (como por ejemplo 34) con un 0. Recuerda que en el
primer caso internamente se representará como _b1 y, sin embargo, en el
segundo se representará tal y como esté en el argumento (34).
*/

void asignar(FILE *fpasm, char *nombre, int es_variable)
{
    if (fpasm == NULL || nombre == NULL || es_variable == -1)
    {
        perror("Null file error in assign function\n");
        return;
    }
    fprintf(fpasm, "\n\t; asignar(nombre=%s,es_variable=%d):\n", nombre, es_variable);

    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable == 1)
        fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tmov [_%s], eax\n", nombre);
}
/*
- Genera el código para asignar valor a la variable de nombre nombre.
- Se toma el valor de la cima de la pila.
- El último argumento es el que indica si lo que hay en la cima de la pila es
una referencia (1) o ya un valor explícito (0).
*/

/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */
/*
En todas ellas se realiza la operación como se ha resumido anteriormente:
- Se extrae de la pila los operandos
- Se realiza la operación
- Se guarda el resultado en la pila
Los dos últimos argumentos indican respectivamente si lo que hay en la pila es
una referencia a un valor o un valor explícito.

Deben tenerse en cuenta las peculiaridades de cada operación. En este sentido
sí hay que mencionar explícitamente que, en el caso de la división, se debe
controlar si el divisor es “0” y en ese caso se debe saltar a la rutina de error
controlado (restaurando el puntero de pila en ese caso y comprobando en el retorno
que no se produce “Segmentation Fault”)
*/
void sumar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL)
    {
        perror("Null file error in sum function");
        return;
    }
    fprintf(fpasm, "\n\t; sumar(es_variable_1=%i, es_variable_1=%i)\n", es_variable_1, es_variable_2);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable_2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable_1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tadd eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}

void restar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL)
    {
        perror("Null file error in subtraction function\n");
        return;
    }
    fprintf(fpasm, "\n\t; resta(es_variable_1=%i, es_variable_2=%i)\n", es_variable_1, es_variable_2);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable_2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable_1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tsub eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}

void multiplicar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL)
    {
        perror("Null file error in multiplication function\n");
        return;
    }
    fprintf(fpasm, "\n\t; multiplicar(es_variable_1=%i,es_variable_2=%i)\n", es_variable_1, es_variable_2);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable_2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable_1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\timul eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}

void dividir(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL)
    {
        perror("Null file error in division function\n");
        return;
    }
    fprintf(fpasm, "\n\t; division(es_variable_1=%i,es_variable_2=%i):\n", es_variable_1, es_variable_2);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable_2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tcmp ebx, 0\n\tje func_dividir_error0\n");

    fprintf(fpasm, "\tmov eax, %s\n", (es_variable_1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tmov edx, 0\n"); /* div => edx:eax / operand */
    fprintf(fpasm, "\tdiv ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}
void o(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL)
    {
        perror("Null file error in OR function\n");
        return;
    }
    fprintf(fpasm, "\n\t; o(es_variable_1=%i, es_variable_1=%i):\n", es_variable_1, es_variable_2);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable_2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable_1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tor eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}
void y(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    if (fpasm == NULL)
    {
        perror("Null file error in AND function\n");
        return;
    }
    fprintf(fpasm, "\n\t; y(es_variable_1=%i, es_variable_1=%i):\n", es_variable_1, es_variable_2);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable_2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable_1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tand eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}
void cambiar_signo(FILE *fpasm, int es_variable)
{
    if (fpasm == NULL)
    {
        perror("Null file error in sign change function\n");
        return;
    }
    fprintf(fpasm, "\n\t; cambiar signo(es_variable=%i):\n", es_variable);

    fprintf(fpasm, "\tpop dword eax\n");
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tneg eax\n");
    fprintf(fpasm, "\tpush dword eax\n");
}
/*
Función aritmética de cambio de signo.
Es análoga a las binarias, excepto que sólo requiere de un acceso a la pila
que sólo usa un operando.
*/
void no(FILE *fpasm, int es_variable, int cuantos_no)
{
    if (fpasm == NULL)
    {
        perror("Null file error in not function\n");
        return;
    }
    fprintf(fpasm, "\n\t; no(es_variable=%i, cuantos_no=%i):\n", es_variable, cuantos_no);

    fprintf(fpasm, "\tpop dword eax\n");
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tcmp eax, 0\n"); /* if eax == 0 jmp end_no_0*/
    fprintf(fpasm, "\tje no_0_%d\n", cuantos_no);

    fprintf(fpasm, "\tmov ebx, 0\n"); /* else */
    fprintf(fpasm, "\tjmp end_no_%d\n", cuantos_no);

    fprintf(fpasm, "no_0_%d:\n", cuantos_no);
    fprintf(fpasm, "\tmov ebx, 1\n");

    fprintf(fpasm, "end_no_%d:\n", cuantos_no);
    fprintf(fpasm, "\tpush dword ebx\n");
}
/*
Función monádica lógica de negación. No hay un código de operación de la ALU
que realice esta operación por lo que se debe codificar un algoritmo que, si
encuentra en la cima de la pila un 0 deja en la cima un 1 y al contrario.
El último argumento es el valor de etiqueta que corresponde (sin lugar a dudas,
la implementación del algoritmo requerirá etiquetas). Véase en los ejemplos de
programa principal como puede gestionarse el número de etiquetas cuantos_no.
*/

/* FUNCIONES COMPARATIVAS */
/*
Todas estas funciones reciben como argumento si los elementos a comparar son o
no variables. El resultado de las operaciones, que siempre será un booleano (“1”
si se cumple la comparación y “0” si no se cumple), se deja en la pila como en el
resto de operaciones. Se deben usar etiquetas para poder gestionar los saltos
necesarios para implementar las comparaciones.
*/
void igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm, "\n\t; igual(es_variable1=%d, es_variable2=%d, etiqueta=%d):\n", es_variable1, es_variable2, etiqueta);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tje func_igual_true%i\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp func_igual_final%i\n", etiqueta);

    fprintf(fpasm, "func_igual_true%i: \n\tpush dword 1\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tjmp func_igual_final%i\n", etiqueta);

    fprintf(fpasm, "func_igual_final%i:\n", etiqueta);
}
void distinto(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm, "\n\t; distinto(es_variable1=%d, es_variable2=%d, etiqueta=%d):\n", es_variable1, es_variable2, etiqueta);
    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjne func_distinto_true%i\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp func_distinto_final%i\n", etiqueta);

    fprintf(fpasm, "func_distinto_true%i: \n\tpush dword 1\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tjmp func_distinto_final%i\n", etiqueta);

    fprintf(fpasm, "func_distinto_final%i:\n", etiqueta);
}
void menor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm, "\n\t; menor igual(es_variable1=%d, es_variable2=%d, etiqueta=%d):\n", es_variable1, es_variable2, etiqueta);
    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjle func_menor_igual_true%i\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp func_menor_igual_final%i\n", etiqueta);

    fprintf(fpasm, "func_menor_igual_true%i: \n\tpush dword 1\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tjmp func_menor_igual_final%i\n", etiqueta);

    fprintf(fpasm, "func_menor_igual_final%i:\n", etiqueta);
}
void mayor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm, "\n\t; mayor igual(es_variable1=%d, es_variable2=%d, etiqueta=%d):\n", es_variable1, es_variable2, etiqueta);
    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjge func_mayor_igual_true%i\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp func_mayor_igual_final%i\n", etiqueta);

    fprintf(fpasm, "func_mayor_igual_true%i: \n\tpush dword 1\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tjmp func_mayor_igual_final%i\n", etiqueta);

    fprintf(fpasm, "func_mayor_igual_final%i:\n", etiqueta);
}
void menor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm, "\n\t; menor(es_variable1=%d, es_variable2=%d, etiqueta=%d):\n", es_variable1, es_variable2, etiqueta);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjl func_menor_true%i\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp func_menor_final%i\n", etiqueta);

    fprintf(fpasm, "func_menor_true%i: \n\tpush dword 1\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tjmp func_menor_final%i\n", etiqueta);

    fprintf(fpasm, "func_menor_final%i:\n", etiqueta);
}
void mayor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm, "\n\t; mayor(es_variable1=%d, es_variable2=%d, etiqueta=%d):\n", es_variable1, es_variable2, etiqueta);

    fprintf(fpasm, "\tpop dword ebx\n\tpop dword eax\n");
    fprintf(fpasm, "\tmov ebx, %s\n", (es_variable2 == 1 ? "[ebx]" : "ebx"));
    fprintf(fpasm, "\tmov eax, %s\n", (es_variable1 == 1 ? "[eax]" : "eax"));

    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjg func_mayor_true%i\n", etiqueta);
    fprintf(fpasm, "\tpush dword 0\n");
    fprintf(fpasm, "\tjmp func_mayor_final%i\n", etiqueta);

    fprintf(fpasm, "func_mayor_true%i: \n\tpush dword 1\n", etiqueta);
    fprintf(fpasm, "\tpush dword 1\n");
    fprintf(fpasm, "\tjmp func_mayor_final%i\n", etiqueta);

    fprintf(fpasm, "func_mayor_final%i:\n", etiqueta);
}

/* FUNCIONES DE ESCRITURA Y LECTURA */
/*
Se necesita saber el tipo de datos que se va a procesar (ENTERO o BOOLEANO) ya
que hay diferentes funciones de librería para la lectura (idem. escritura) de cada
tipo.
Se deben insertar en la pila los argumentos necesarios, realizar la llamada
(call) a la función de librería correspondiente y limpiar la pila.
*/
void leer(FILE *fpasm, char *nombre, int tipo)
{
    if (fpasm == NULL || nombre == NULL)
    {
        perror("Null file error in READ function\n");
        return;
    }
    fprintf(fpasm, "\n\t; leer(nombre=%s,tipo=%i)\n", nombre, tipo);

    fprintf(fpasm, "\tpush dword _%s\n", nombre);
    fprintf(fpasm, "\tcall scan_%s\n", (tipo == ENTERO ? "int" : "boolean"));
    fprintf(fpasm, "\tadd esp, 4\n");
}

void escribir(FILE *fpasm, int es_variable, int tipo)
{
    if (fpasm == NULL)
    {
        perror("Null file error in WRITE function\n");
        return;
    }
    fprintf(fpasm, "\n\t; escribir(es_variable=%i,tipo=%i):\n", es_variable, tipo);

    fprintf(fpasm, "\tpop dword eax\n%s\tpush dword eax\n", (es_variable == 1 ? "\tmov eax, [eax]\n" : ""));
    fprintf(fpasm, "\tcall print_%s\n", (tipo == ENTERO ? "int" : "boolean"));
    fprintf(fpasm, "\tadd esp, 4\n");
    fprintf(fpasm, "\tcall print_endofline\n");
}

/******* SECOND PART *******/
void ifthenelse_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    if (fpasm == NULL)
    {
        perror("Null file error in WRITE function\n");
        return;
    }
    fprintf(fpasm, "\n\t; ifthenelse_inicio(exp_es_variable=%d, etiqueta=%d)\n", exp_es_variable, etiqueta);

    fprintf(fpasm, "\tpop eax\n");
    fprintf(fpasm, "\tmov eax, %s\n", (exp_es_variable == 1 ? "[eax]" : "eax"));
    fprintf(fpasm, "\tcmp eax, 1\n");                   /* Compara con 1 para ver si la condición previamente realizada se ha cumplido */
    fprintf(fpasm, "\tjne func_if_else%i\n", etiqueta); /* Si la condición no se cumple entra en el else, si se cumpliese seguiria al then sin saltar */
}
/*
Generación de código para el inicio de una estructura if-then-else
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void ifthen_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    if (!fpasm)
    {
        perror("ERROR: \"ifthen_inicio()\"");
        return;
    }
    fprintf(fpasm, "\n\t; ifthen_inicio(exp_es_variable=%d,etiqueta=%d)\n", exp_es_variable, etiqueta);

    fprintf(fpasm, "\tpop eax\n");
    fprintf(fpasm, "\tmov eax, %s\n", (exp_es_variable == 1 ? "[eax]" : "eax"));
    fprintf(fpasm, "\tcmp eax, 1\n");                    /* Compara con 1 para ver si la condición previamente realizada se ha cumplido */
    fprintf(fpasm, "\tjne func_if_final%i\n", etiqueta); /* Si la condición no se cumple no entra en el if */
}
/*
Generación de código para el inicio de una estructura if-then
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void ifthen_fin(FILE *fpasm, int etiqueta)
{
    if (!fpasm)
    {
        perror("ERROR: \"ifthen_fin()\"");
        return;
    }
    fprintf(fpasm, "\n; ifthen_fin(etiqueta=%d)\n", etiqueta);

    fprintf(fpasm, "func_if_final%i:\n", etiqueta);
}
/*
Generación de código para el fin de una estructura if-then
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/

void ifthenelse_fin_then(FILE *fpasm, int etiqueta)
{
    if (!fpasm)
    {
        perror("ERROR: \"ifthenelse_fin_then()\"");
        return;
    }
    fprintf(fpasm, "\n\t; ifthenelse_fin_then(etiqueta=%d)\n", etiqueta);
    fprintf(fpasm, "\tjmp func_if_final%i\n", etiqueta);
    fprintf(fpasm, "func_if_else%i:\n", etiqueta);
}
/*
Generación de código para el fin de la rama then de una estructura if-then-else
Sólo necesita usar la etiqueta adecuada, aunque es el final de una rama, luego debe venir
otra (la rama else) antes de que se termine la estructura y se tenga que ajustar las etiquetas
por lo que sólo se necesita que se utilice la etiqueta que corresponde al momento actual.
*/

void ifthenelse_fin(FILE *fpasm, int etiqueta)
{
    if (!fpasm)
    {
        perror("ERROR: \"ifthenelse_fin()\"");
        return;
    }
    fprintf(fpasm, "\n; ifthenelse_fin(etiqueta=%d):\n", etiqueta);
    fprintf(fpasm, "func_if_final%d:\n", etiqueta);
}
/*
Generación de código para el fin de una estructura if-then-else
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/

void while_inicio(FILE *fpasm, int etiqueta)
{
    if (!fpasm)
    {
        perror("ERROR: \"while_inicio()\"");
        return;
    }

    fprintf(fpasm, "\n; while_inicio(etiqueta=%d)", etiqueta);

    fprintf(fpasm, "\n; inicio del while %d:\n", etiqueta);
    fprintf(fpasm, "func_while_inicio%d:\n", etiqueta);
}
/*
Generación de código para el inicio de una estructura while
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void while_exp_pila(FILE *fpasm, int exp_es_variable, int etiqueta)
{

    fprintf(fpasm, "\n\t; while_exp_pila(exp_es_variable=%d, etiqueta=%d):\n", exp_es_variable, etiqueta);
    fprintf(fpasm, "\tpop eax\n");

    if (exp_es_variable)
    {
        fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }

    fprintf(fpasm, "\tcmp eax, 1\n");
    fprintf(fpasm, "\tjne func_while_final%d\n", etiqueta);
}
/*
Generación de código para el momento en el que se ha generado el código de la expresión
de control del bucle
Sólo necesita usar la etiqueta adecuada, por lo que sólo se necesita que se recupere el valor
de la etiqueta que corresponde al momento actual.
exp_es_variable
Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
o elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void while_fin(FILE *fpasm, int etiqueta)
{
    fprintf(fpasm, "\n\t; while_fin(etiqueta=%d):\n", etiqueta);
    fprintf(fpasm, "\tjmp func_while_inicio%d\n", etiqueta);

    fprintf(fpasm, "func_while_final%d:\n", etiqueta);
}
/*
Generación de código para el final de una estructura while
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/

void escribir_elemento_vector(FILE *fpasm, char *nombre_vector,
                              int tam_max, int exp_es_direccion)
{
    if (!fpasm || !nombre_vector)
    {
        perror("\"escribir_elemento_vector\":ERROR  --> Null pointers in the arguments");
        return;
    }

    fprintf(fpasm, "\n\t; escribir elemento vector(nombre_vector=%s, tam_max=%d, exp_es_direccion=%d)\n", nombre_vector, tam_max, exp_es_direccion);

    // We pop the index value to a registry
    fprintf(fpasm, "\tpop dword eax\n");

    // Depending on if it is a reference or not
    if (exp_es_direccion == 1)
        fprintf(fpasm, "\tmov dword eax, [eax]\n"); // Value of the ítem in eax

    // Run-time error control in case the index is out of range
    fprintf(fpasm, "\tcmp eax, 0\n");
    fprintf(fpasm, "\tjl vector_out_of_bounds\n");

    fprintf(fpasm, "\tcmp eax, %d\n", tam_max - 1);
    fprintf(fpasm, "\tjg vector_out_of_bounds\n");

    fprintf(fpasm, "\tmov dword edx, _%s\n", nombre_vector);
    fprintf(fpasm, "\tlea eax, [edx + eax * 4]\n"); // Value * 4 bytes + vectors’ address (1st element)

    fprintf(fpasm, "\tpush dword eax\n"); // We push this reference to the item
}
/*
Generación de código para indexar un vector
Cuyo nombre es nombre_vector
Declarado con un tamaño tam_max
La expresión que lo indexa está en la cima de la pila
Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
Puede ser un valor concreto (en ese caso exp_es_direccion vale 0)
Según se especifica en el material, es suficiente con utilizar dos registros para realizar esta
tarea.
*/

void declararFuncion(FILE *fd_asm, char *nombre_funcion, int num_var_loc)
{
    if (!fd_asm || !nombre_funcion)
    {
        perror("\"declararFuncion\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fd_asm, "\n; declararFuncion(nombre_funcion=%s, num_var_loc=%d)\n", nombre_funcion, num_var_loc);

    fprintf(fd_asm, "%s:\n", nombre_funcion);
    fprintf(fd_asm, "\tpush ebp\n");
    fprintf(fd_asm, "\tmov ebp, esp\n");
    fprintf(fd_asm, "\tsub esp, %d\n", 4 * num_var_loc);
}
/*
Generación de código para iniciar la declaración de una función.
Es necesario proporcionar
Su nombre
Su número de variables locales
*/

void retornarFuncion(FILE *fd_asm, int es_variable)
{
    if (!fd_asm || es_variable < 0 || es_variable > 1)
    {
        perror("\"retornarFuncion\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fd_asm, "\n\t; retornarFuncion(int es_variable=%d)\n", es_variable);

    fprintf(fd_asm, "\tpop eax\n"); // Get return value
    if (es_variable == 1)
        fprintf(fd_asm, "\tmov dword eax, [eax]\n"); // Get actual value

    fprintf(fd_asm, "\tmov esp, ebp\n"); // Restore original esp
    fprintf(fd_asm, "\tpop ebp\n");      // Restore ebp
    fprintf(fd_asm, "\tret\n");          // End function
}
/*
Generación de código para el retorno de una función.
La expresión que se retorna está en la cima de la pila.
Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
Puede ser un valor concreto (en ese caso exp_es_direccion vale 0)
*/

void escribirParametro(FILE *fpasm, int pos_parametro, int num_total_parametros)
{
    if (!fpasm || num_total_parametros < 0)
    {
        perror("\"escribirParametro\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fpasm, "\n\t; escribirParametro(pos_parametro=%d, num_total_parametros=%d)\n", pos_parametro, num_total_parametros);

    fprintf(fpasm, "\tlea eax, [ebp + %d]\n", 4 * (1 + (num_total_parametros - pos_parametro))); // ebp contains the original value of stack_top
    fprintf(fpasm, "\tpush dword eax\n");                                                        // Push value to stack
}
/*
Función para dejar en la cima de la pila la dirección efectiva del parámetro que ocupa la
posición pos_parametro (recuerda que los parámetros se ordenan con origen 0) de un total
de num_total_parametros
*/

void escribirVariableLocal(FILE *fpasm, int posicion_variable_local)
{
    if (!fpasm)
    {
        perror("\"escribirVariableLocal\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fpasm, "\n\t; escribirVariableLocal(int posicion_variable_local=%d)\n", posicion_variable_local);

    fprintf(fpasm, "\tlea eax, [ebp - %i]\n", 4 * posicion_variable_local); /* Local variables are in minus numbers*/
    fprintf(fpasm, "\tpush eax\n");
}
/*
Función para dejar en la cima de la pila la dirección efectiva de la variable local que ocupa
la posición posicion_variable_local (recuerda que ordenadas con origen 1)
*/

void asignarDestinoEnPila(FILE *fpasm, int es_variable)
{
    if (!fpasm || es_variable < 0 || es_variable > 1)
    {
        perror("\"asignarDestinoEnPila\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fpasm, "\n\t; asignarDestinoEnPila(es_variable=%d)\n", es_variable);

    fprintf(fpasm, "\tpop dword ebx\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if (es_variable == 1)
        fprintf(fpasm, "\tmov eax, [eax]\n");
    fprintf(fpasm, "\tmov dword [ebx], eax\n");
}
/*
Función para poder asignar a un destino que no es una variable “global” (tipo _x) por
ejemplo parámetros o variables locales (ya que en ese caso su nombre real de alto nivel, no
se tiene en cuenta pues es realmente un desplazamiento a partir de ebp: ebp+4 o ebp-8 por
ejemplo).
Se debe asumir que en la pila estará
Primero (en la cima) lo que hay que asignar
Debajo (se ha introducido en la pila antes) la dirección donde hay que asignar
es_variable
Es 1 si la expresión que se va a asignar es algo asimilable a una variable
(identificador, o elemento de vector)
Es 0 en caso contrario (constante u otro tipo de expresión)
*/

void operandoEnPilaAArgumento(FILE *fd_asm, int es_variable)
{
    if (!fd_asm || es_variable < 0 || es_variable > 1)
    {
        perror("\"operandoEnPiLaAArgumento\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fd_asm, "\n\t; operandoEnPilaAArgumento(int es_variable=%d)\n", es_variable);

    if (es_variable == 1)
    {
        fprintf(fd_asm, "\tpop eax\n");        // Pop parameter
        fprintf(fd_asm, "\tmov eax, [eax]\n"); // Get value of address in parameter
        fprintf(fd_asm, "\tpush eax\n");       // Push the value
    }
}
/*
Como habrás visto en el material, nuestro convenio de llamadas a las funciones asume que
los argumentos se pasan por valor, esto significa que siempre se dejan en la pila “valores” y
no “variables”
Esta función realiza la tarea de dado un operando escrito en la pila y sabiendo si es variable
o no (es_variable) se deja en la pila el valor correspondiente
*/

void llamarFuncion(FILE *fd_asm, char *nombre_funcion, int num_argumentos)
{
    if (!fd_asm || !nombre_funcion || num_argumentos < 0)
    {
        perror("\"llamarFuncion\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fd_asm, "\n\t; llamarFuncion(nombre_funcion=%s, num_argumentos=%d)\n", nombre_funcion, num_argumentos);

    fprintf(fd_asm, "\tcall %s\n", nombre_funcion); // Call nombre_funcion
    limpiarPila(fd_asm, num_argumentos);
}
/*
Esta función genera código para llamar a la función nombre_funcion asumiendo que los
argumentos están en la pila en el orden fijado en el material de la asignatura.
Debe dejar en la cima de la pila el retorno de la función tras haberla limpiado de sus
argumentos
Para limpiar la pila puede utilizar la función de nombre limpiarPila
*/

void limpiarPila(FILE *fd_asm, int num_argumentos)
{
    if (!fd_asm || num_argumentos < 0)
    {
        perror("\"limpiarPila\":ERROR  --> Null pointers in the arguments");
        return;
    }
    fprintf(fd_asm, "\n\t; limpiarPila(num_argumentos=%d)\n", num_argumentos);

    fprintf(fd_asm, "\tadd esp, %d\n", num_argumentos * 4); // Clean stack
    fprintf(fd_asm, "\tpush dword eax\n");                  // Store return
}
/*
Genera código para limpiar la pila tras invocar una función
Esta función es necesaria para completar la llamada a métodos, su gestión dificulta el
conocimiento por parte de la función de llamada del número de argumentos que hay en la
pila
*/
