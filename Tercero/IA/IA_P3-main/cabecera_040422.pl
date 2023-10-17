write_log(S) :- open('error_logs.txt', append, Out), write(Out, S), write(Out, '\n'), close(Out).

/*
EJERCICIO 1.

% P18 (**):  Extract a slice from a list

% slice(L1,I,K,L2) :- L2 is the list of the elements of L1 between
%    index I and index K (both included).
%    (list,integer,integer,list) (?,+,+,?)

slice([X|_],1,1,[X]).
slice([X|Xs],1,K,[X|Ys]) :- K > 1, 
   K1 is K - 1, slice(Xs,1,K1,Ys).
slice([_|Xs],I,K,Ys) :- I > 1, 
   I1 is I - 1, K1 is K - 1, slice(Xs,I1,K1,Ys).
*/


/***************
* EJERCICIO 2. sum_pot_prod/4
*
*	ENTRADA:
*		X: Vector de entrada de numeros de valor real.
*		Y: Vector de entrada de numeros de valor real.
*		Potencia: Numero de valor entero, potencia.
*	SALIDA:
*		Resultado: Numero de valor real resultado de la operacion sum_pot_prod. 
*
****************/
sum_pot_prod( _, _, X, _) :- X < 0,
    write("ERROR 1.1 Potencia.").
sum_pot_prod( L1, L2, _, _) :- 
	write("ERROR 1.2 Longitud.").
sum_pot_prod(X, Y, Potencia, Resultado) :- Potencia > 0,
    /* Multiplicamos elementos de x e y */
    X = [X1|Xs], Y = [Y1|Ys],
    MUL is X1 * Y1,
    /* Potencia de  Mul elevado a Potencia */
    POW is MUL ** Potencia,
    /* Calculamos resto de la lista */
    sum_pot_prod(Xs, Ys, Potencia, Resto),
    /* Sumamos el resultado de la potencia con el resto */
    Resultado is POW + Resto.

/*
fact(0,1).
fact(X,Y) :- fact(X-1,Q), Y is Q*X
*/

/***************
* EJERCICIO 3. segundo_penultimo/3
*
*       ENTRADA:
*               L: Lista de entrada de numeros de valor real.
*       SALIDA:
*               X : Numero de valor real. Segundo elemento.
*		Y : Numero de valor real. Penultimo elemento.
*
****************/
segundo_penultimo(L, X, Y) :- segundo_elemento(L, X), penultimo_elemento(L, Y).
segundo_elemento([_|[]], _) :- write("ERROR 2.1 Longitud.").                        
segundo_elemento([_|L], X) :-
    L = [X|_].
penultimo_elemento([X,_], X).
penultimo_elemento([_|T], X) :- penultimo_elemento(T, X).

/***************
* EJERCICIO 4. sublista/5
*
*       ENTRADA:
*		L: Lista de entrada de cadenas de texto.
*		Menor: Numero de valor entero, indice inferior.
*		Mayor: Numero de valor entero, indice superior.
*		E: Elemento, cadena de texto.
*       SALIDA:
*		Sublista: Sublista de salida de cadenas de texto.
*
****************/
sublista(_, Menor, Mayor, _, _) :- Menor > Mayor, write("ERROR 3.2 Indices. "), false.
sublista(L, Menor, Mayor, E, Sublista) :- slice(L, Menor, Mayor, Sublista), miembro(E, Sublista).


slice([X|_],1,1,[X]).
slice([X|Xs],1,K,[X|Ys]) :- K > 1, 
   K1 is K - 1, slice(Xs,1,K1,Ys).
slice([_|Xs],I,K,Ys) :- I > 1, 
   I1 is I - 1, K1 is K - 1, slice(Xs,I1,K1,Ys).

miembro(_, []) :- write("ERROR 3.1 Elemento. "), false.
miembro(X, [X|_]).
miembro(X, [_|Ys]) :- miembro(X, Ys).

/***************
* EJERCICIO 5. espacio_lineal/4
*
*       ENTRADA:
*               Menor: Numero de valor entero, valor inferior del intervalo.
*               Mayor: Numero de valor entero, valor superior del intervalo.
*               Numero_elementos: Numero de valor entero, numero de valores de la rejilla.
*       SALIDA:
*               Rejilla: Vector de numeros de valor real resultante con la rejilla.
*
****************/
espacio_lineal(Menor, Mayor, _, _) :- Menor > Mayor, write("ERROR 4.1 Indices. "), false.
espacio_lineal( Menor, Mayor, Numero_elementos, Rejilla) :-
    /* Calculamos el intervalo */
    Intervalo = (Mayor - Menor) / (Numero_elementos - 1),
    /* Calculamos la lista con sumas */
    lista_suma(Menor, Intervalo, Numero_elementos, Rejilla).


/* Si el numero de elementos es 0 */
lista_suma(_,_,0,L) :- L = [].

lista_suma(Elemento, Intervalo, Numero_elementos, L) :-
    /* Calculamos la suma de los intervalos */
    Suma is Elemento + Intervalo,
    /* Calculamos el nuevo Elemento */
    Elemento1 is Suma,
    /* Calculamos el nuevo numero de elementos */
    Numero_elementos1 is Numero_elementos - 1,
    /* Calculamos la lista de sumas */
    lista_suma(Elemento1, Intervalo, Numero_elementos1, L1),
    /* Añadimos Elemento1 a L */
    append([Elemento], L1, L).

/***************
* EJERCICIO 6. normalizar/2
*
*       ENTRADA:
*		Distribucion_sin_normalizar: Vector de numeros reales de entrada. Distribucion sin normalizar.
*       SALIDA:
*		Distribucion: Vector de numeros reales de salida. Distribucion normalizada.
*
****************/
normalizar(Distribucion_sin_normalizar, Distribucion) :- 
    /* Calculamos la suma de los elementos de la lista */
    suma_positiva(Distribucion_sin_normalizar, Suma),
    /* Calculamos la lista de la normalizacion */
    normalizacion(Distribucion_sin_normalizar, Suma, Distribucion).
    /* Devolvemos la distribucion normalizada */

suma_positiva([], 0).
suma_positiva([X|_], _) :- X < 0, write("ERROR 5.1. Negativos. "), false.
suma_positiva([X|Xs], Suma) :- 
    suma_positiva(Xs, Suma1),
    Suma is Suma1 + X.

normalizacion([], _, []).
normalizacion([X|Xs], Suma, [Y|Ys]) :-
    Y is X / Suma,
    normalizacion(Xs, Suma, Ys).


/***************
* EJERCICIO 7. divergencia_kl/3
*
*       ENTRADA:
*		D1: Vector de numeros de valor real. Distribucion.
*		D2: Vector de numeros de valor real. Distribucion.
*       SALIDA:
*		KL: Numero de valor real. Divergencia KL.
*
****************/
divergencia_kl(D1, D2, KL) :- 
    comprobar_vector(D1,1),
    comprobar_vector(D2,1),
    divergencia_kl_aux(D1, D2, KL).

divergencia_kl_aux([], [], 0).
divergencia_kl_aux([X|_], _, _) :- 
    X =< 0, write("ERROR 6.1. Divergencia KL no definida. "), false.

divergencia_kl_aux(_, [Y|_], _) :- 
    Y =< 0, write("ERROR 6.1. Divergencia KL no definida. "), false.


divergencia_kl_aux(D1, D2, KL) :- 

    D1 = [D1C|D1B],
    D2 = [D2C|D2B],
    /* Calculamos D1C / D2C */
    DIV is D1C / D2C,
    /* Calculamos el logaritmo */
    log(DIV, Log),
    /* Multiplicamos logaritmo por D1C */
    KL1 is Log * D1C,
    /* Repetimos proceso con el resto de la lista */
    divergencia_kl(D1B, D2B, KL2),
    KL is KL1 + KL2.

/* Comprobar que el total del vector es 1 */
comprobar_vector([], 0).
comprobar_vector([], _) :- write("ERROR 6.2. Divergencia KL definida solo para distribuciones."), false.
comprobar_vector([X|Xs], Res) :- 
    Res1 is Res - X,
    comprobar_vector(Xs, Res1).



/***************
* EJERCICIO 8. producto_kronecker/3
*
*       ENTRADA:
*		Matriz_A: Matriz de numeros de valor real.
*		Matriz_B: Matriz de numeros de valor real.
*       SALIDA:
*		Matriz_bloques: Matriz de bloques (matriz de matrices) de numeros reales.
*
****************/
producto_kronecker(Matriz_A, Matriz_B, Matriz_bloques) :- 
    matriz_matriz(Matriz_A, Matriz_B, Matriz_bloques).

matriz_matriz([VA|[]], Matriz_B, [MF1]):-
    vector_matriz(VA, Matriz_B, MF1).
matriz_matriz([VA|MA], Matriz_B, [MF1|MF]) :- 
    vector_matriz(VA, Matriz_B, MF1),
    matriz_matriz(MA, Matriz_B, MF).

vector_matriz([A|[]], Matriz_B, [V1]):-
    elemento_matriz(A, Matriz_B, V1).
vector_matriz([A|VA], Matriz_B, [V1|V]) :-
    elemento_matriz(A, Matriz_B, V1),
    vector_matriz(VA, Matriz_B, V).

elemento_matriz(Elemento_A, [B|[]], [V1]):-
    elemento_vector(Elemento_A, B, V1).
elemento_matriz(Elemento_A, [B|MB], [V1|V]) :-
    elemento_vector(Elemento_A, B, V1),
    elemento_matriz(Elemento_A, MB, V).

elemento_vector(Elemento_A, [B|[]], [V1]):-
    elemento_elemento(Elemento_A, B, V1).
elemento_vector(Elemento_A, [B|VB1], [V1|V]) :-
    elemento_elemento(Elemento_A, B, V1),
    elemento_vector(Elemento_A, VB1, V).
    
elemento_elemento(A, _, _) :-
    A < 0, write("ERROR 7.1. Elemento menor que cero. "), false.
elemento_elemento(_, B, _) :-
    B < 0, write("ERROR 7.1. Elemento menor que cero. "), false.
elemento_elemento(Elemento_A, Elemento_B, V1) :-
    ELEMENTO is Elemento_A*Elemento_B,
    V1 is ELEMENTO.
    
    
/***************
* EJERCICIO 9a. distancia_euclidea/3
*
*       ENTRADA:
*               X1: Vector de numeros de valor real. 
*               X2: Vector de numeros de valor real.
*       SALIDA:
*               D: Numero de valor real. Distancia euclidea.
*
****************/
distancia_euclidea(X1, X2, D) :-
    distsq(X1, X2, D1),
    D is sqrt(D1).

distsq([], [], _).
distsq([X|Xs], [Y|Ys], D) :-
    distsq(Xs, Ys, D1),
    D is D1 + (X - Y) * (X - Y).




/***************
* EJERCICIO 9b. calcular_distancias/3
*
*       ENTRADA:
*               X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*               X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*
****************/
calcular_distancias(X_entrenamiento, X_test, Matriz_resultados) :- 
    matrix_vector(X_entrenamiento, X_test, Matriz_resultados).

matrix_vector(X, [Y|[]], [Z]):-
    vector_vector(X, Y, Z).
matrix_vector(X, [Y|Ys], [Z|Zs]) :-
    vector_vector(X, Y, Z),
    matrix_vector(X, Ys, Zs).

vector_vector([X|[]], Y, [Z]):-
    distancia_euclidea(X, Y, Z),

vector_vector([X|Xs], Y, [Z|Zs]) :-
    distancia_euclidea(X, Y, Z),
    vector_vector(Xs, Y, Zs).


/***************
* EJERCICIO 9c. predecir_etiquetas/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*       SALIDA:
*               Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
predecir_etiquetas(Y_entrenamiento, K, Matriz_resultados, Y_test) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 9d. predecir_etiqueta/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
predecir_etiqueta(Y_entrenamiento, K, Vec_distancias, Etiqueta) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 9e. calcular_K_etiquetas_mas_relevantes/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*		K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*
****************/
calcular_K_etiquetas_mas_relevantes(Y_entrenamiento, K, Vec_distancias, K_etiquetas) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 9f. calcular_etiqueta_mas_relevante/2
*
*       ENTRADA:
*               K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
calcular_etiqueta_mas_relevante(K_etiquetas, Etiqueta) :- 
    /* Calcular contadores */
    calcular_contadores(K_etiquetas, Contadores),
    /* Obtener etiqueta de mayor tamaño */
    obtener_etiqueta_mayor(Contadores, ['None',0], Etiqueta).

obtener_etiqueta_mayor([], Etiqueta, Etiqueta).

obtener_etiqueta_mayor([X|Xs], Mayor, Etiqueta) :-
    /* Comparar la etiqueta con la actual mayor */
    comparar_etiquetas(X, Mayor, Res),
    /* Recursiva */
    obtener_etiqueta_mayor(Xs, Res, Etiqueta).
comparar_etiquetas([_|Xs],[Y|Ys], Etiqueta) :-
    Xs < Ys,
    Etiqueta = Y.

comparar_etiquetas([X|_],_, X).


/*************************************/

calcular_contadores([],[]).
calcular_contadores(K_etiquetas, Contador_etiquetas) :-
    /* Extraer cada letra */
    K_etiquetas = [X|Xs],
    /* Contar las apariciones de cada letra */
    contar_apariciones(X, K_etiquetas, Cuenta),
    /* Eliminar X de la lista */
    eliminar_de_lista(X, Xs, K_etiquetas_sin_X),
    /* Llamada recursiva */
    calcular_contadores(K_etiquetas_sin_X, Contador_etiquetas1),
    crear_etiqueta(X,Cuenta, Etiqueta),
    /* Agregar etiqueta a la lista */
    append(Contador_etiquetas1, [Etiqueta], Contador_etiquetas).


contar_apariciones(_, [], 0).
contar_apariciones(Elemento, [Elemento|Xs], Cuenta) :-
    contar_apariciones(Elemento, Xs, Cuenta1),
    Cuenta is Cuenta1 + 1.
contar_apariciones(Elemento, [_|Xs] , Cuenta) :-
    contar_apariciones(Elemento, Xs, Cuenta).

eliminar_de_lista(_, [], []).
eliminar_de_lista(X, [X|Xs], L) :-
    eliminar_de_lista(X, Xs, L).
eliminar_de_lista(X, [Y|Ys], L) :-
    eliminar_de_lista(X, Ys, L1),
    append([Y], L1, L).

crear_etiqueta(E, C, Etiqueta):-
    Etiqueta = [E, C].

/*
calcular_contadores(K_etiquetas, Contador_etiquetas) :-
    analizar_letra(K_etiquetas, C2),
	actualizar_tuplas(C2, Contador_etiquetas).


analizar_letra([E|[]], [C]):-
    crear_etiqueta(E, C).
    
analizar_letra([E|KE], [C|CE]):-
    crear_etiqueta(E, C),
    analizar_letra(KE, CE).

crear_etiqueta(E, C):-
    C = [E, 0].

actualizar_tuplas([C2H|C2B], C):-
    comprobar_existencia(C2H, C),
    actualizar_tuplas(C2B, C).

comprobar_existencia(E, [CH|CB]):-
    CH = [X, N],
    E == X,
    N is N+1,
    comprobar_existencia(E, [CB]).
*/
/***************
* EJERCICIO 9g. k_vecinos_proximos/5
*
*       ENTRADA:
*		X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*		Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*		K: Numero de valor entero.
*		X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*		Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
k_vecinos_proximos(X_entrenamiento, Y_entrenamiento, K, X_test, Y_test) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 9h. clasifica_patrones/4
*
*       ENTRADA:
*		iris_patrones.csv: Fichero con los patrones a clasificar, disponible en Moodle.
*		iris_etiquetas.csv: Fichero con las etiquetas de los patrones a clasificar, disponible en Moodle.
*		K: Numero de valor entero.
*       SALIDA:
*		tasa_aciertos: Tasa de acierto promediada sobre las iteraciones leave-one-out
*
****************/
clasifica_patrones('iris_patrones.csv','iris_etiquetas.csv',K,Tasa_aciertos) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.
