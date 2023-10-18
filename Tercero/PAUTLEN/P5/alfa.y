%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "alfa.h"
    #include "generacion.h"
    #include "tablaSimbolos.h"
    void yyerror(char * s);
    int yylex(void);
    extern int line, col;
    extern int yyleng;
    extern char* yytext;
    extern int morph_error;
    extern FILE *out;
    extern TablaSimbolos *ts;
    
    int tipo_actual;
    int clase_actual;
    int tamanio_vector_actual;
    int pos_variable_local_actual;
    int num_parametros_actual;
    int pos_parametro_actual;
    int num_variables_locales_actual;
    
    int en_explist;
    int num_parametros_llamada_actual;

    int etiqueta = 0, etiq_actual = 0;
    int retorno = 0;

    // Array auxiliar
    char aux_lex[2*BUFFER_SIZE], aux_vector_index[2*BUFFER_SIZE];
    
%}

%union { tipo_atributos atributos; }

%type <atributos> condicional
%type <atributos> comparacion
%type <atributos> elemento_vector
%type <atributos> exp
%type <atributos> constante
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> identificador
%type <atributos> numero
%type <atributos> fn_name
%type <atributos> fn_declaration
%type <atributos> funcion
%type <atributos> idf_llamada_funcion
%type <atributos> bucle_exp
%type <atributos> if_exp
%type <atributos> if_else

%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN
     
/* Símbolos */
%token TOK_PUNTOYCOMA          
%token TOK_COMA                
%token TOK_PARENTESISIZQUIERDO 
%token TOK_PARENTESISDERECHO   
%token TOK_CORCHETEIZQUIERDO   
%token TOK_CORCHETEDERECHO     
%token TOK_LLAVEIZQUIERDA      
%token TOK_LLAVEDERECHA        
%token TOK_ASIGNACION          
%token TOK_MAS                 
%token TOK_MENOS               
%token TOK_DIVISION            
%token TOK_ASTERISCO           
%token TOK_AND                 
%token TOK_OR                  
%token TOK_NOT                 
%token TOK_IGUAL               
%token TOK_DISTINTO            
%token TOK_MENORIGUAL          
%token TOK_MAYORIGUAL          
%token TOK_MENOR               
%token TOK_MAYOR               

/* Identificadores  */
%token <atributos> TOK_IDENTIFICADOR     

/* Constantes */ 

%token <atributos> TOK_CONSTANTE_ENTERA  
%token TOK_TRUE                
%token TOK_FALSE    

/* Errores */
%token TOK_ERROR

/* Prioridades */
%left TOK_OR
%left TOK_AND
%left TOK_DISTINTO
%left TOK_MAS TOK_MENOS
%left TOK_ASTERISCO TOK_DIVISION
%right TOK_NOT

/* %token <atributos> TOK_CONSTANTE_REAL */

%%
 
programa: init_ts TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escritura1 funciones escritura2 sentencias TOK_LLAVEDERECHA 
    {
        fprintf(out, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");

        /*Llamada a funciones para escribir el fin del fichero fichero_ensamblador*/
        escribir_fin(out);
    };

init_ts: 
    { 
        /* Regla auxiliar para inicializar tabla y subseccion data/bss */
        ts = initTablaSimbolos();
        escribir_subseccion_data(out);
        escribir_cabecera_bss(out);
    };

escritura1: 
    {
        /*Llamada a funciones para escribir la sección data con los mensajes generales, y la tabla de símbolos así como todo lo necesario para que
          lo siguiente que haya que escribirse sea "main:"*/
        escribir_segmento_codigo(out);
    };

escritura2: 
    {
        /*Llamar a funcion que escribe inicio main*/
        escribir_inicio_main(out);
    };

declaraciones: declaracion {fprintf(out, ";R2:\t<declaraciones> ::= <declaracion>\n");} 
    | declaracion declaraciones {fprintf(out, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");};
declaracion: clase identificadores TOK_PUNTOYCOMA {fprintf(out, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");};

clase: clase_escalar 
    {
        clase_actual = ESCALAR;
        fprintf(out, ";R5:\t<clase> ::= <clase_escalar>\n");
    }
    | clase_vector 
    {
        clase_actual = VECTOR;
        fprintf(out, ";R7:\t<clase> ::= <clase_vector>\n");
    };

clase_escalar: tipo {fprintf(out, ";R9:\t<clase_escalar> ::= <tipo>\n");};

tipo: TOK_INT 
    {
        tipo_actual = INT;
        fprintf(out, ";R10:\t<tipo> ::= int\n");
    } 
    | TOK_BOOLEAN 
    {
        tipo_actual = BOOLEAN;
        fprintf(out, ";R11:\t<tipo> ::= boolean\n");
        
    };

clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO 
    {
        tamanio_vector_actual = $4.valor_entero;
        fprintf(out, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");
    };
identificadores: identificador {fprintf(out, ";R18:\t<identificadores> ::= <identificador>\n");} 
    | identificador TOK_COMA identificadores {fprintf(out, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");};

funciones: funcion funciones {fprintf(out, ";R20:\t<funciones> ::= <funcion> <funciones>\n");} 
    | {fprintf(out, ";R21:\t<funciones> ::=\n");};


fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR 
    {
        /* Buscar el identificador en el ámbito actual (el exterior a la función). Generar un error  */
        if (buscarTablaSimbolosAmbitoActual(ts, $3.lexema) != NULL) {
            yyerror("Declaracion duplicada.");
            return -1;
        }
        /*
        Si no ha habido error, abrir un ámbito nuevo. Esta operación implica: 
        insertar el identificador de la función en el ámbito actual (el exterior a la función) 
        crear un nuevo ámbito (el de la función) e insertar en él el identificador de la función.
        */
        if (insertarTablaSimbolosAmbitos(ts, $3.lexema, FUNCION, clase_actual, tipo_actual, -1, -1, -1, -1, -1) == ERROR) {
            yyerror(NULL);
            return -1;
        }

        if (abrirAmbito(ts) == ERROR) {
            yyerror(NULL);
            return -1;
        }
        // Si esto da fallos en el futuro, tener en cuenta que puede devolver un vector y que ahora mismo no estamos especificando su tamaño
        if (insertarTablaSimbolosAmbitos(ts, $3.lexema, FUNCION, clase_actual, tipo_actual, -1, -1, -1, -1, -1) == ERROR) {
            yyerror(NULL);
            return -1;
        }
        num_variables_locales_actual = 0;
        pos_variable_local_actual = 1;
        num_parametros_actual = 0;
        pos_parametro_actual = 0;

        /* Propagar a la parte izquierda de la regla el lexema del identificador de la función para su posterior uso en la acción del punto marcado como (2) */
        strcpy($$.lexema, $3.lexema);

        fprintf(out, ";R23:\t<fn_name> ::= function <tipo> <identificador>\n");

    };

fn_declaration: fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion
    {
        /*
        Acceder al identificador de la función en el ámbito actual (el de la función) y actualizar la 
        información correspondiente al número de parámetros. 
        El acceso al identificador se puede realizar haciendo uso del lexema guardado como 
        atributo del no terminal fn_name que se propagó en la acción . 
        Propagar a la parte izquierda de la regla el lexema del identificador de la función para su 
        posterior uso en la acción del punto marcado como
        */
        elementoTablaSimbolos *elemento = NULL;
        elemento = buscarTablaSimbolosAmbitoActual(ts, $1.lexema);
        if (elemento == NULL) {
            sprintf(aux_lex, "Acceso a función no declarada (%s).", $1.lexema);
            yyerror(aux_lex);
            return -1;
        }
        elemento->n_param = num_parametros_actual;
        strcpy($$.lexema, $1.lexema);

        declararFuncion(out, $1.lexema, num_variables_locales_actual);

        fprintf(out, ";R22.1:\t<fn_declaracion> ::= <fn_nombre> ( <parametros_funcion> ) { <declaraciones_funcion>\n");

    };
funcion: fn_declaration sentencias TOK_LLAVEDERECHA
    {
        if (cerrarAmbito(ts) == ERROR) {
            yyerror(NULL);
            return -1;
        }
        if (!retorno) {
            sprintf(aux_lex, "Funcion %s sin sentencia de retorno.", $1.lexema);
            yyerror(aux_lex);
            return -1;
        }
        elementoTablaSimbolos *elemento = NULL;
        elemento = buscarTablaSimbolosAmbitoActual(ts, $1.lexema);
        if (elemento == NULL) {
            sprintf(aux_lex, "Acceso a función no declarada (%s).", $1.lexema);
            yyerror(aux_lex);
            return -1;
        }
        elemento->n_param = num_parametros_actual;
        strcpy($$.lexema, $1.lexema);

        retorno = 0;
        fprintf(out, ";R22:\t<funcion> ::=  <declaraciones_funcion> <sentencias> }\n");
    };
parametros_funcion: parametro_funcion resto_parametros_funcion {fprintf(out, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");} 
    | {fprintf(out, ";R24:\t<parametros_funcion> ::= \n");};
resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(out, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");} 
    | {fprintf(out, ";R26:\t<resto_parametros_funcion> ::=\n");};
parametro_funcion: tipo idpf {fprintf(out, ";R27:\t<parametro_funcion> ::= <tipo> <idpf>\n");};
declaraciones_funcion: declaraciones {fprintf(out, ";R28:\t<declaraciones_funcion> ::= <tipo> <identificador>\n");} 
    | {fprintf(out, ";R29:\t<declaraciones_funcion> ::=\n");};
sentencias: sentencia {fprintf(out, ";R30:\t<sentencias> ::= <sentencia>\n");} 
    | sentencia sentencias {fprintf(out, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");};
sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(out, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
    | bloque {fprintf(out, ";R33:\t<sentencia> ::= <bloque>\n");};
sentencia_simple: asignacion {fprintf(out, ";R34:\t<sentencia_simple> ::= <asignacion>\n");} 
    | lectura {fprintf(out, ";R35:\t<sentencia_simple> ::= <lectura>\n");} 
    | escritura {fprintf(out, ";R36:\t<sentencia_simple> ::= <escritura>\n");} 
    | retorno_funcion {fprintf(out, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");};

bloque: condicional {fprintf(out, ";R40:\t<bloque> ::= <condicional>\n");} 
    | bucle {fprintf(out, ";R41:\t<bloque> ::= <bucle>\n");};

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp 
    {
        elementoTablaSimbolos *p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, $1.lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, $1.lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", $1.lexema);
                yyerror(aux_lex);
                return -1;
            }
        }

        if (p_s->categoria == FUNCION || p_s->clase == VECTOR) {
            yyerror("Asignacion incompatible.");
            return -1;
        }

        if (p_s->tipo != $3.tipo) {
            yyerror("Asignacion incompatible.");
            return -1;
        }
        if (estoyEnAmbitoGlobal(ts))
            asignar(out, $1.lexema, $3.es_direccion);
        else {
            escribirVariableLocal(out, p_s->local_position);
            asignarDestinoEnPila(out, $3.es_direccion);
        }            

        fprintf(out, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");
    } 
    | elemento_vector TOK_ASIGNACION exp 
    {
        elementoTablaSimbolos *p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, $1.lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, $1.lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", $1.lexema);
                yyerror(aux_lex);
                return -1;
            }
        }
        
        if (p_s->tipo != $3.tipo) {
            yyerror("Asignacion incompatible.");
            return -1;
        }
        if ($1.valor_entero != -1) {
            sprintf(aux_lex, "%d", $1.valor_entero);
            // Push index
            escribir_operando(out, aux_lex, 0);
        } else
            // Index is variable
            escribir_operando(out, aux_vector_index, 1);

        // Pop index and push address
        escribir_elemento_vector(out, $1.lexema, p_s->size, $1.es_direccion);
        asignarDestinoEnPila(out, $3.es_direccion);
        
        fprintf(out, ";R44:\t<asignación> ::= <elemento_vector> = <exp>\n");
    };
     
elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO
    {
        elementoTablaSimbolos *p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, $1.lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, $1.lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", $1.lexema);
                yyerror(aux_lex);
                return -1;
            }
        }

        if (p_s->clase != VECTOR) {
            yyerror("Intento de indexacion de una variable que no es de tipo vector.");
            return -1;
        }
        
        if (INT != $3.tipo) {
            yyerror("El indice en una operacion de indexacion tiene que ser de tipo entero.");
            return -1;
        }

        $$.tipo = p_s->tipo;
        $$.es_direccion = $3.es_direccion;
        $$.valor_entero = $3.valor_entero;
        // Index is variable
        if ($$.valor_entero == -1)
            strcpy(aux_vector_index, $3.lexema);
        strcpy($$.lexema, $1.lexema);
        
        // Check index (?)
        escribir_elemento_vector(out, $1.lexema, p_s->size, $3.es_direccion);
        fprintf(out,";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");
    };

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp 
    {
        if ($3.tipo == INT) {
            yyerror("Condicional con condicion de tipo int.");
            return -1;
        }
        $$.etiqueta = $3.etiqueta;
        $$.tipo = $3.tipo;
        ifthen_inicio(out, $3.es_direccion, $3.etiqueta);
    };

if_else: if_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA TOK_ELSE
    {
        $$.etiqueta = $1.etiqueta;
        $$.tipo = $1.tipo;
        ifthenelse_fin_then(out, $1.etiqueta);
    };

condicional: if_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA
    {
        ifthen_fin(out, $1.etiqueta);
        $$.etiqueta = $1.etiqueta;
        $$.tipo = $1.tipo;
        fprintf(out, ";R50:\tcondicional ::= if ( <exp> ) { <sentencias> } \n");
    }
    | if_else TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA
    {
        ifthenelse_fin(out, $1.etiqueta);
        $$.etiqueta = $1.etiqueta;
        $$.tipo = $1.tipo;
        fprintf(out, ";R51:\tcondicional ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
    };

bucle_inicio: TOK_WHILE 
    {
        while_inicio(out, etiqueta);
    };

bucle_exp: bucle_inicio TOK_PARENTESISIZQUIERDO exp 
    {
        if ($3.tipo == INT) {
            yyerror("Bucle con condicion de tipo int.");
            return -1;
        }
        $$.etiqueta = $3.etiqueta;
        $$.tipo = $3.tipo;
        while_exp_pila(out, $3.es_direccion, $3.etiqueta);
    };
    
bucle: bucle_exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA 
    {
        while_fin(out, $1.etiqueta);
        fprintf(out, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
    };

lectura: TOK_SCANF TOK_IDENTIFICADOR 
    {
        // Buscar en la tabla de símbolos (todos los ámbitos abiertos) el identificador $2.lexema
        // Si no existe
        //     MOSTRAR MENSAJE ERROR SEMÁNTICO
        //     TERMINAR CON ERROR
        elementoTablaSimbolos *elemento = NULL;
        int isGlobal = 0;
        if ((elemento = buscarTablaSimbolosAmbitoActual(ts, $2.lexema)) == NULL)
        {
            isGlobal = 1;
            if ((elemento = buscarTablaSimbolosAmbitoGlobal(ts, $2.lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", $2.lexema);
                yyerror(aux_lex);
                return -1;
            }
        }
        else
            isGlobal = estoyEnAmbitoGlobal(ts);
        // En caso contrario hacer lo correspondiente a la producción
        //     COMPROBACIONES SEMÁNTICAS
        //         Si el identificador es una función → ERROR SEMÁNTICO
        //         Si el identificador es un vector → ERROR SEMÁNTICO
        if (elemento->categoria == FUNCION || elemento->clase == VECTOR)
        {
            sprintf(aux_lex, "No esta permitido el uso de vectores o llamadas o funciones como parametro de lectura (%s).", $2.lexema);
            yyerror(aux_lex);
            return -1;
        }
        //     GENERACIÓN DE CÓDIGO: APILAR LA DIRECCIÓN DEL IDENTIFICADOR
        //         Si el identificador en una variable global , su dirección es su lexema
        //         Si el identificador es un parámetro o una variable local, su dirección se expresa en función de ebp y la posición del parámetro o variable local
        if (isGlobal)
            leer(out, elemento->lexema, elemento->tipo);
        else {
            if (elemento->categoria == PARAMETRO) {
                escribirParametro(out, elemento->param_position, num_parametros_actual);
            }
            else {
                escribirVariableLocal(out, elemento->local_position);
            }
            llamarFuncion(out, elemento->tipo == INT ? "scan_int" : "scan_boolean", 1);
        }
        //     GENERACIÓN DE CÓDIGO: LLAMAR A LA FUNCIÓN DE LA LIBRERÍA ALFALIB.O
        //         Si el identificador es de tipo entero llamar a scan_int
        //         Si el identificador es de tipo lógico llamar a scan_boolean
        //         Restaurar la pila

        fprintf(out, ";R54:\t<lectura> ::= scanf <identificador>\n");
    };

escritura: TOK_PRINTF exp 
    {
        escribir(out, $2.es_direccion, $2.tipo);
    };

retorno_funcion: TOK_RETURN exp 
    {
        if (estoyEnAmbitoGlobal(ts)) {
            yyerror("Sentencia de retorno fuera del cuerpo de una función.");
            return -1;
        }
        retornarFuncion(out, $2.es_direccion);
        retorno = 1;
        fprintf(out, ";R61:\t<retorno_funcion> ::= return <exp>\n");
    };

exp: exp TOK_MAS exp 
    {
        if ($1.tipo != INT || $3.tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        sumar(out, $1.es_direccion, $3.es_direccion);
        fprintf(out, ";R72:\t<exp> ::= <exp> + <exp>\n");
    }             
    | exp TOK_MENOS exp 
    {
        if ($1.tipo != INT || $3.tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        restar(out, $1.es_direccion, $3.es_direccion);
        fprintf(out, ";R73:\t<exp> ::= <exp> - <exp>\n");
    }
    | exp TOK_DIVISION exp 
    {
        if ($1.tipo != INT || $3.tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        dividir(out, $1.es_direccion, $3.es_direccion);
        fprintf(out, ";R74:\t<exp> ::= <exp> / <exp>\n");
    }       
    | exp TOK_ASTERISCO exp 
    {
        if ($1.tipo != INT || $3.tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        multiplicar(out, $1.es_direccion, $3.es_direccion);
        fprintf(out, ";R75:\t<exp> ::= <exp> * <exp>\n");
    }
    | TOK_MENOS exp 
    {
        if ($2.tipo != INT) {
            yyerror("Operacion aritmetica con operandos boolean.");
            return -1;
        }
        $$.tipo = INT;
        $$.es_direccion = 0;
        cambiar_signo(out, $2.es_direccion);
        fprintf(out, ";R76:\t<exp> ::= - <exp>\n");
    }
    | exp TOK_AND exp 
    {
        if ($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
            yyerror("Operacion logica con operandos int.");
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        y(out, $1.es_direccion, $3.es_direccion);
        fprintf(out, ";R77:\t<exp> ::= <exp> && <exp>\n");
    }
    | exp TOK_OR exp 
    {
        if ($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
            yyerror("Operacion logica con operandos int.");
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        o(out, $1.es_direccion, $3.es_direccion);
        fprintf(out, ";R78:\t<exp> ::= <exp> || <exp>\n");
    }
    | TOK_NOT exp 
    {
        if ($2.tipo != BOOLEAN) {
            yyerror("Operacion logica con operandos int.");
            return -1;
        }
        $$.tipo = BOOLEAN;
        $$.es_direccion = $2.es_direccion;
        etiq_actual = etiqueta++;
        $$.etiqueta = etiq_actual;
        $2.etiqueta = etiq_actual;
        no(out, $2.es_direccion, etiq_actual);
        fprintf(out, ";R79:\t<exp> ::= ! <exp>\n");
    }
    | TOK_IDENTIFICADOR 
    {   
        elementoTablaSimbolos * p_s = NULL;
        if ((p_s = buscarTablaSimbolosAmbitoActual(ts, $1.lexema)) == NULL)
        {
            if ((p_s = buscarTablaSimbolosAmbitoGlobal(ts, $1.lexema)) == NULL)
            {
                sprintf(aux_lex, "Acceso a variable no declarada (%s).", $1.lexema);
                yyerror(aux_lex);
                return -1;
            }
        }

        if (p_s->categoria == FUNCION) {
            yyerror("No esta permitido el uso de llamadas a funciones como parametros de otras funciones.");
            return -1;
        }
        if (p_s->clase == VECTOR) {
            yyerror("Expresion no puede ser vector.");
            return -1;
        }

        $$.es_direccion = 1;
        $$.tipo = p_s->tipo;
        $$.valor_entero = -1;
        
        if (estoyEnAmbitoGlobal(ts)) {
            escribir_operando(out, $1.lexema, 1);
            if (en_explist) {
                operandoEnPilaAArgumento(out, 1);
                $$.es_direccion = 0;
            }
        }
        else if (p_s->categoria == PARAMETRO)
            escribirParametro(out, p_s->param_position, num_parametros_actual);
        else
            escribirVariableLocal(out, p_s->local_position);
            
        strcpy($$.lexema, $1.lexema);
        
        fprintf(out, ";R80:\t<exp> ::= <identificador>\n");
    }             
    | constante 
    {
        $$.es_direccion = $1.es_direccion;
        $$.valor_entero = $1.valor_entero;
        $$.tipo = $1.tipo;
        strcpy($$.lexema, $1.lexema);
        escribir_operando(out, $1.lexema, 0);
        fprintf(out, ";R81:\t<exp> ::= <constante_entera>\n");
    }              
    | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO 
    {
        $$.tipo = $2.tipo;
        $$.valor_entero = $2.valor_entero;
        $$.es_direccion = $2.es_direccion;
        $$.etiqueta = $2.etiqueta;
        strcpy($$.lexema, $2.lexema);
        fprintf(out, ";R82:\t<exp> ::= ( <exp> )\n");
    } 
    | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO 
    {
        $$.tipo = $2.tipo;
        $$.valor_entero = $2.valor_entero;
        $$.es_direccion = $2.es_direccion;
        $$.etiqueta = $2.etiqueta;
        strcpy($$.lexema, $2.lexema);
        fprintf(out, ";R83:\t<exp> ::= ( <comparacion> )\n");
    } 
    | elemento_vector 
    {
        $$.es_direccion = $1.es_direccion;
        $$.valor_entero = $1.valor_entero;
        $$.tipo = $1.tipo;
        strcpy($$.lexema, $1.lexema);

        if (en_explist) {
            operandoEnPilaAArgumento(out, $$.es_direccion);
        }
        fprintf(out, ";R85:\t<exp> ::= <elemento_vector>\n");
    }
    | idf_llamada_funcion TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO
    {
        /* Comprobar que el numero de parametros de la llamada es correcto
        comprobando el valor de la variable num_parametros_llamada_actual con la informacion
        almacenada en la tabla de simbolos */
        elementoTablaSimbolos * p_s = NULL;
        p_s = buscarTablaSimbolosAmbitoActual(ts ,$1.lexema);
        if (p_s == NULL) {
            sprintf(aux_lex, "Acceso a variable no declarada (%s).", $1.lexema);
            yyerror(aux_lex);
            return -1;
        }
        if (p_s->n_param != num_parametros_llamada_actual) {
            yyerror("Numero incorrecto de parametros en llamada a funcion.");
            return -1;
        }
        /* Resetear a 0 la variable en_explist */
        en_explist = 0;

        /* Propagar el tipo del retorno de la funcion almacenada en la tabla de simbolos */
        $$.tipo = p_s->tipo;

        /* Propagar direccion a 0 */
        $$.es_direccion = 0;

        llamarFuncion(out, $1.lexema, num_parametros_llamada_actual);

        fprintf(out, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");
    };

idf_llamada_funcion: TOK_IDENTIFICADOR
    {
        /* buscar identificador en la tabla simbolos*/
        elementoTablaSimbolos * p_s = NULL;
        p_s = buscarTablaSimbolosAmbitoActual(ts, $1.lexema);
        if (p_s == NULL) {
            sprintf(aux_lex, "Acceso a variable no declarada (%s).", $1.lexema);
            yyerror(aux_lex);
            return -1;
        }
        /* Comprobar que el identificador es de categoria funcion */
        if (p_s->categoria != FUNCION) {
            sprintf(aux_lex, "Intento de llamada a variable que no es función (%s).", $1.lexema);
            yyerror(aux_lex);
            return -1;
        }
        /* Comprobar que la variable en_explist no valga 1 para asegurar que la actual
            llamada a la funcion no es un parametro de la llamada a funcion */
        if (en_explist == 1) { 
            sprintf(aux_lex, "No esta permitido el uso de llamadas a funciones como parametros de otras funciones. (%s).", $1.lexema);
            yyerror(aux_lex);
            return -1;
        }
        /*
        Iniciar a 0 num_parametros_llamada_actual
        Iniciar a 1 la variable en_explist
        */
        num_parametros_actual = p_s->n_param;
        num_parametros_llamada_actual = 0;
        en_explist = 1;
        /*
        Propagar el lexema del identifiacdor 
        */
        strcpy($$.lexema, $1.lexema);
    };

lista_expresiones: exp resto_lista_expresiones
    {
        fprintf(out, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");
        num_parametros_llamada_actual++;
    } 
    | {fprintf(out, ";R90:\t<lista_expresiones> ::= \n");};

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones 
    {
        fprintf(out, ";R91:\t<resto_lista_expresiones> ::= <exp> <resto_lista_expresiones\n");
        num_parametros_llamada_actual++;
    } 
    | {fprintf(out, ";R92:\t<resto_lista_expresiones> ::= \n");};

comparacion: exp TOK_IGUAL exp 
    {
        if ($1.tipo == BOOLEAN || $3.tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        $$.tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        $$.es_direccion = 0;
        $$.etiqueta = etiq_actual;
        igual(out, $1.es_direccion, $3.es_direccion, etiq_actual);
        fprintf(out, ";R93:\t<comparacion> ::= <exp> == <exp>\n");
    }    
    | exp TOK_DISTINTO exp 
    {
        if ($1.tipo == BOOLEAN || $3.tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        $$.tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        $$.es_direccion = 0;
        $$.etiqueta = etiq_actual;
        distinto(out, $1.es_direccion, $3.es_direccion, etiq_actual);
        fprintf(out, ";R94:\t<comparacion> ::= <exp> != <exp>\n");
    }
    | exp TOK_MENORIGUAL exp 
    {
        if ($1.tipo == BOOLEAN || $3.tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        $$.tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        $$.es_direccion = 0;
        $$.etiqueta = etiq_actual;
        menor_igual(out, $1.es_direccion, $3.es_direccion, etiq_actual);
        fprintf(out, ";R95:\t<comparacion> ::= <exp> <= <exp>\n");
    }                
    | exp TOK_MAYORIGUAL exp 
    {
        if ($1.tipo == BOOLEAN || $3.tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        $$.tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        $$.es_direccion = 0;
        $$.etiqueta = etiq_actual;
        mayor_igual(out, $1.es_direccion, $3.es_direccion, etiq_actual);
        fprintf(out, ";R96:\t<comparacion> ::= <exp> >= <exp>\n");
    }                
    | exp TOK_MENOR exp 
    {
        if ($1.tipo == BOOLEAN || $3.tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        $$.tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        $$.es_direccion = 0;
        $$.etiqueta = etiq_actual;
        menor(out, $1.es_direccion, $3.es_direccion, etiq_actual);
        fprintf(out, ";R97:\t<comparacion> ::= <exp> < <exp>\n");
    }                      
    | exp TOK_MAYOR exp 
    {
        if ($1.tipo == BOOLEAN || $3.tipo == BOOLEAN) {
            yyerror("Comparacion con operandos boolean.");
            return -1;
        }

        $$.tipo = BOOLEAN;
        etiq_actual = etiqueta++;
        $$.es_direccion = 0;
        $$.etiqueta = etiq_actual;
        mayor(out, $1.es_direccion, $3.es_direccion, etiq_actual);
        fprintf(out, ";R98:\t<comparacion> ::= <exp> > <exp>\n");
    };

constante: constante_logica 
    {
        $$.valor_entero = $1.valor_entero;
        $$.tipo = $1.tipo;
        $$.es_direccion = $1.es_direccion;
        sprintf(aux_lex, "%d", $$.valor_entero);
        strcpy($$.lexema, aux_lex);
        fprintf(out, ";R99:\t<constante> ::= <constante_logica>\n");
    } 
    | constante_entera 
    {
        $$.valor_entero = $1.valor_entero;
        $$.tipo = $1.tipo;
        $$.es_direccion = $1.es_direccion;
        sprintf(aux_lex, "%d", $$.valor_entero);
        strcpy($$.lexema, aux_lex);
        fprintf(out, ";R100:\t<constante> ::= <constante_entera>\n");
    };

constante_logica: TOK_TRUE 
    {
        $$.valor_entero = 1;
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        fprintf(out, ";R102:\t<constante_logica> ::= true\n");
    }
    | TOK_FALSE 
    {
        $$.valor_entero = 0;
        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
        fprintf(out, ";R103:\t<constante_logica> ::= false\n");
    };

constante_entera: numero 
    {
        $$.valor_entero = $1.valor_entero;
        $$.tipo = INT;
        $$.es_direccion = 0;
        fprintf(out, ";R104:\t<constante_entera> ::= <numero>\n");
    };

numero: TOK_CONSTANTE_ENTERA 
    {
        $$.valor_entero = $1.valor_entero;
        fprintf(out, ";R105:\t<numero> ::= <digito>\n");
    }
    | numero TOK_CONSTANTE_ENTERA {fprintf(out, ";R106:\t<numero> ::= <numero> <digito>\n");};
    
identificador: TOK_IDENTIFICADOR 
    {
        if (buscarTablaSimbolosAmbitoActual(ts, $1.lexema) != NULL)
        {
            yyerror("Declaracion duplicada.");
            return -1;
        } else
        {
            if (clase_actual == VECTOR && ((tamanio_vector_actual < 1 ) || (tamanio_vector_actual > MAX_TAMANIO_VECTOR))) {
                // Semantic error vector size
                sprintf(aux_lex, "El tamanio del vector %s[%d] excede los limites permitidos (1,64).", $1.lexema, tamanio_vector_actual);
                yyerror(aux_lex);
                return -1;
            }

            if (!estoyEnAmbitoGlobal(ts)) {

                if (clase_actual != ESCALAR) {
                    yyerror("Variable local de tipo no escalar.");
                    return -1;
                }

                insertarTablaSimbolosAmbitos(ts, $1.lexema, VARIABLE, clase_actual, tipo_actual, -1, -1, pos_variable_local_actual, -1, -1);
                pos_variable_local_actual++;
                num_variables_locales_actual++;
            }
            else {
                int size = (clase_actual == VECTOR ? tamanio_vector_actual : 1);
                insertarTablaSimbolosAmbitos(ts, $1.lexema, VARIABLE, clase_actual, tipo_actual, size, -1, -1, -1, -1);
                declarar_variable(out, $1.lexema, tipo_actual, size);
            }


            fprintf(out, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
            $$.tipo = tipo_actual;
            $$.es_direccion = 1;
            strcpy($$.lexema, $1.lexema);

        }
    };

idpf: TOK_IDENTIFICADOR 
    {
    fprintf(out, ";R109:\t<idpf> ::= TOK_IDENTIFICADOR\n");
    /* Se comprueba que el identificador no exista en el ámbito actual (el de la función). Si 
    existiera, se genera un mensaje de error semántico y se termina el proceso de compilación 
    con error. */
    if (buscarTablaSimbolosAmbitoActual(ts, $1.lexema) != NULL) 
    {
        yyerror("Declaracion duplicada.");
        return -1;
    }
    
    /* Si no hay error semántico se realiza la inserción sin olvidar el uso de la variable global 
    pos_parametro_actual. */
    insertarTablaSimbolosAmbitos(ts, $1.lexema, PARAMETRO, ESCALAR, tipo_actual, -1, -1, -1, -1, pos_parametro_actual++);
    /*
    Se incrementa en uno el valor de las siguientes variables globales:  */
    /*num_parametros_actual (esta variable almacena el número de parámetros de una función) */
    num_parametros_actual++;
    /*Se asume que estas variables son correctamente inicializadas (consultar documentación de la gestión 
    de identificadores de funciones) */
    };


%%

void yyerror(char *s)
{
    col -= yyleng;
    if (!morph_error) {
        if (!strcmp(s, "syntax error"))
            fprintf(stdout, "****Error sintactico en [lin %d, col %d]\n", line, col);
        else
            fprintf(stdout, "****Error semantico en [lin %d, col %d]: %s\n", line, col, s);
    }
}
