# Ejemplo script, para P3 arq 2019-2020

#!/bin/bash

# inicializar variables
Ninicio=1024
Npaso=1024
# Nfinal=$((Ninicio + 100))
Nfinal=16384
#Nfinal=4000
fDAT=ex1/slow_fast_time.dat
fPNG=ex1/slow_fast_time.png

# borrar el fichero DAT y el fichero PNG
rm -f $fDAT fPNG

# generar el fichero DAT vacío
touch $fDAT

echo "Running slow and fast..."
# bucle para N desde P hasta Q 
#for N in $(seq $Ninicio $Npaso $Nfinal);



for ((N = Ninicio ; N <= Nfinal ; N += (Npaso*2))); 
do
	echo "N: $N / $Nfinal..."
	slowTime=0
	fastTime=0
	slowTime2=0
	fastTime2=0
	nextval=$(echo "$N + $Npaso" | bc)
	# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
	# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
	# tercera columna (el valor del tiempo). Dejar los valores enicio ; N <= Nfinal ; N += Npaso)); do
	echo "N: $N / $Nfinal..."n variables
	# para poder imprimirlos en la misma línea del fichero de datos
	for i in {1..10};
	do
		slowTime=$(echo "scale=10; $slowTime+$(./common/slow $N | grep 'time' | awk '{print $3}')" | bc)
		#if $N + $Npaso <= $Nfinal;
		if [ $nextval -le $Nfinal ];
		then
			slowTime2=$(echo "scale=10; $slowTime2+$(./common/slow $nextval  | grep 'time' | awk '{print $3}')" | bc)
			
		fi
		fastTime=$(echo "scale=10; $fastTime+$(./common/fast $N | grep 'time' | awk '{print $3}')" | bc)
		if [ $nextval -le $Nfinal ];
		then
			fastTime2=$(echo "scale=10; $fastTime2+$(./common/fast $nextval  | grep 'time' | awk '{print $3}')" | bc)
		fi
	done
	slowTime=$(echo "scale=10; $slowTime / 10" | bc)
	slowTime2=$(echo "scale=10; $slowTime2 / 10" | bc)
	fastTime=$(echo "scale=10; $fastTime / 10" | bc)
	fastTime2=$(echo "scale=10; $fastTime2 / 10" | bc)
	echo "$N	$slowTime	$fastTime" >> $fDAT
	if [ $nextval -le $Nfinal ];
	then
		echo "$nextval	$slowTime2	$fastTime2" >> $fDAT
	fi
done


echo "Generating plot..."
Rscript ex1/plot_slow_fast.r
eog $fPNG
























# R plotting

# R
# all<-read.table("slow_fast_time.dat",header=F)


# all.x<-all[1]
# all.y<-all[2]
# plot(all[,1],all[,2],xlab="x",ylab="y")

Rscript plot_slow_fast.r
eog slow_fast_plot.png