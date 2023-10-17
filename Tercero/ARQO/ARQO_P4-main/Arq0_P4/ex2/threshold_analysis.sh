#!/bin/bash
#
#$ -S /bin/bash
#$ -cwd
#$ -o simple.out
#$ -j y
export OMP_NUM_THREADS=$NSLOTS

rm -f "threshold_serial.dat"
rm -f "threshold_parallel.dat"
mi=10000
mf=100000
for M in $(seq $mi 10000 $mf)
do

	tiempos=0
	tiempop=0
    for i in {1..50};
	do
        tiempos=$(echo "scale=10; $tiempos+$(./threshold_serial $M | grep Tiempo | awk '{print $2}')" | bc)
        tiempop=$(echo "scale=10; $tiempop+$(./threshold_parallel $M | grep Tiempo | awk '{print $2}')" | bc)
    done  

	tiempos=$(echo "scale=10; $tiempos / 50" | bc)
	tiempop=$(echo "scale=10; $tiempop / 50" | bc)
    echo "$M $tiempos " >> "threshold_serial.dat"
    echo "$M $tiempop " >> "threshold_parallel.dat"
done

# Rscript threshold_analysis.r
