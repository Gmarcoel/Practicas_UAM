#!/bin/bash
#
#$ -S /bin/bash
#$ -cwd
#$ -o simple.out
#$ -j y
export OMP_NUM_THREADS=$NSLOTS

image="image.jpg"

tiempo=0
tiempo_mod=0
tiempo_par=0
for i in {1..50};
do
    tiempo_mod=$(echo "scale=10; $tiempo_mod+$(./edgeDetector_mod $image | grep Tiempo | awk '{print $2}')" | bc)
    tiempo=$(echo "scale=10; $tiempo+$(./edgeDetector $image | grep Tiempo | awk '{print $2}')" | bc)
    tiempo_par=$(echo "scale=10; $tiempo_par+$(./edgeDetector_par $image | grep Tiempo | awk '{print $2}')" | bc)
done  
tiempo=$(echo "scale=10; $tiempo / 50" | bc)
tiempo_mod=$(echo "scale=10; $tiempo_mod / 50" | bc)
tiempo_par=$(echo "scale=10; $tiempo_par / 50" | bc)
    # echo "$M $tiempos " >> "threshold_serial.dat"
    # echo "$M $tiempop" >> "threshold_parallel.dat"
    echo "Original time " $tiempo
    echo "Modified time " $tiempo_mod
    echo "Parallel time " $tiempo_par
