#!/bin/bash
# Tomar datos de la cantidad de fallos de caché producidos en la lectura y escritura de datos al 
# ejecutar las dos versiones (fast y slow) del programa que calcula las sumas de los elementos 
# de  una  matriz  para  matrices  de  tamaño  NxN,  con  N  variando  entre  1024+1024*P  y 
# 1024+1024*(P+1) y con un incremento en saltos de 256 unidades. Utilizar tamaños de caché 
# de primer nivel (tanto para datos como para instrucciones) de tamaño variable de 1024, 2048, 
# 4096 y 8192 Bytes (note que deben ser potencias de 2) y una caché de nivel superior de 
# tamaño fijo igual a 8 Mbytes. Para todas las cachés asumir que son de correspondencia directa 
# (es decir, con una única vía) y con tamaño de línea igual a 64 bytes. Como valgrind es un 
# emulador, solo es necesario ejecutar 1 vez el programa para cada configuración solicitada. 

# Numero 4
P=4
 ((    Ninicio=1024+1024*$P   ))
 ((    Nfinal=1024+1024*($P+1)   ))

# The first level cache sizes (data and instructions) to test are 1024, 
# 2048, 4096 y 8192 Bytes, and the second level cache size is 8 Mbytes.
# All caches are direct 
# mapped (1 way) and the block size is 64 bytes
small_cache_sizes="1024 2048 4096 8192"
large_cache_size=$((8*1024*1024))


for s in $small_cache_sizes;
do
    rm -f "ex2/ex2_data/cache_"$s".dat"
    for ((N=Ninicio; N<=Nfinal; N=N+256));
    do

        

        valgrind --tool=cachegrind --cachegrind-out-file=./ex2/out.dat  \
            --I1=$s,1,64 \
            --D1=$s,1,64 \
            --LL=$large_cache_size,1,64 \
            ./common/slow $N
        slowmr=$(cg_annotate ./ex2/out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        slowmw=$(cg_annotate ./ex2/out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        rm -f "out.dat"
        valgrind --tool=cachegrind --cachegrind-out-file=./ex2/out.dat \
            --I1=$s,1,64 \
            --D1=$s,1,64 \
            --LL=$large_cache_size,1,64 \
            ./common/fast $N 
        fastmr=$(cg_annotate ./ex2/out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        fastmw=$(cg_annotate ./ex2/out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        rm -f "ex2/out.dat"
        echo "$N $slowmr $slowmw $fastmr $fastmw" >> "ex2/ex2_data/cache_"$s".dat"
        

        # Guardar en <tamCache>.dat
        # Guardar como <N> <D1mr “slow”> <D1mw “slow”> <D1mr “fast”> <D1mw “fast”> 
    done
done

echo "Generating plot..."
Rscript ex2/ex2.r
eog ex2/cache_lectura.png
eog ex2/cache_escritura.png


