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
P=0
# ((    Ninicio=1024   ))
# ((    Nfinal=1024+1024   ))
 ((    Ninicio=256+256*$P   ))
 ((    Nfinal=256+256*($P+1)   ))
Npaso=32
#Nfinal=4000
fDAT=ex3/mult.dat
fPNG1=ex3/mult_time.png
fPNG2=ex3/mult_cache.png
# The first level cache sizes (data and instructions) to test are 1024, 
# 2048, 4096 y 8192 Bytes, and the second level cache size is 8 Mbytes.
# All caches are direct 
# mapped (1 way) and the block size is 64 bytes

rm -f $fDAT fPNG
touch $fDAT

for ((N=Ninicio; N<=Nfinal; N += (Npaso*2)));
do

    echo "N: $N / $Nfinal..."
	normTime=0
	trasTime=0
	normTime2=0
	trasTime2=0
    normmr=0
    trasmr=0
    normmw=0
    trasmw=0
    normmr2=0
    trasmr2=0
    normmw2=0
    trasmw2=0
	nextval=$(echo "$N + $Npaso" | bc)
	

    valgrind --tool=cachegrind --cachegrind-out-file=out.dat ./ex3/ex3_normal $N
	normmr=$(cg_annotate out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	normmw=$(cg_annotate out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	rm -f "out.dat"
	if [ $nextval -le $Nfinal ];
	then
		valgrind --tool=cachegrind --cachegrind-out-file=out.dat ./ex3/ex3_normal $nextval
		normmr2=$(cg_annotate out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
		normmw2=$(cg_annotate out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        rm -f "out.dat"
	fi
	valgrind --tool=cachegrind --cachegrind-out-file=out.dat ./ex3/ex3_trasposed $N 
	trasmr=$(cg_annotate out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	trasmw=$(cg_annotate out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	rm -f "out.dat"

	if [ $nextval -le $Nfinal ];
	then

		valgrind --tool=cachegrind --cachegrind-out-file=out.dat ./ex3/ex3_trasposed $nextval 
		trasmr2=$(cg_annotate out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
		trasmw2=$(cg_annotate out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        rm -f "out.dat"
	fi
	
    for i in {1..10};
	do
		
		normTime=$(echo "scale=10; $normTime+$(./ex3/ex3_normal $N | grep 'time' | awk '{print $3}')" | bc)
		#if $N + $Npaso <= $Nfinal;
		if [ $nextval -le $Nfinal ];
		then
			normTime2=$(echo "scale=10; $normTime2+$(./ex3/ex3_normal $nextval  | grep 'time' | awk '{print $3}')" | bc)
			
		fi
		trasTime=$(echo "scale=10; $trasTime+$(./ex3/ex3_trasposed $N | grep 'time' | awk '{print $3}')" | bc)
		if [ $nextval -le $Nfinal ];
		then
			trasTime2=$(echo "scale=10; $trasTime2+$(./ex3/ex3_trasposed $nextval  | grep 'time' | awk '{print $3}')" | bc)
		fi
	done

	normTime=$(echo "scale=10; $normTime / 10" | bc)
	normTime2=$(echo "scale=10; $normTime2 / 10" | bc)
	trasTime=$(echo "scale=10; $trasTime / 10" | bc)
	trasTime2=$(echo "scale=10; $trasTime2 / 10" | bc)


    echo "$N $normTime $normmr $normmw $trasTime $trasmr $trasmw" >> $fDAT
	if [ $nextval -le $Nfinal ];
	then
    	echo "$nextval $normTime2 $normmr2 $normmw2 $trasTime2 $trasmr2 $trasmw2" >> $fDAT
	fi
    
done

echo "Generating plot..."
Rscript ex3/ex3.r
eog $fPNG1
eog $fPNG2


