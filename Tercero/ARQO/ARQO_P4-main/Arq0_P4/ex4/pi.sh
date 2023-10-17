#!/bin/bash
#
#$ -S /bin/bash
#$ -cwd
#$ -o simple.out
#$ -j y
export OMP_NUM_THREADS=$NSLOTS
N=2000
fDAT=pi.dat


rm -f $fDAT fPNG
touch $fDAT

echo "Executing pi algorithm"


pis=0
pi1=0
pi2=0
pi3=0
pi4=0
pi5=0
pi6=0
pi7=0

for i in {1..10};
do
	pis=$(echo "scale=10; $pis+$(./pi_serie | grep 'Tiempo' | awk '{print $2}')" | bc)
	pi1=$(echo "scale=10; $pi1+$(./pi_par1 | grep 'Tiempo' | awk '{print $2}')" | bc)
    pi2=$(echo "scale=10; $pi2+$(./pi_par2 | grep 'Tiempo' | awk '{print $2}')" | bc)
    pi3=$(echo "scale=10; $pi3+$(./pi_par3 | grep 'Tiempo' | awk '{print $2}')" | bc)
    pi4=$(echo "scale=10; $pi4+$(./pi_par4 | grep 'Tiempo' | awk '{print $2}')" | bc)
    pi5=$(echo "scale=10; $pi5+$(./pi_par5 | grep 'Tiempo' | awk '{print $2}')" | bc)
    pi6=$(echo "scale=10; $pi6+$(./pi_par6 | grep 'Tiempo' | awk '{print $2}')" | bc)
    pi7=$(echo "scale=10; $pi7+$(./pi_par7 | grep 'Tiempo' | awk '{print $2}')" | bc)
done
pis=$(echo "scale=10; $pis / 10" | bc)
pi1=$(echo "scale=10; $pi1 / 10" | bc)
pi2=$(echo "scale=10; $pi2 / 10" | bc)
pi3=$(echo "scale=10; $pi3 / 10" | bc)
pi4=$(echo "scale=10; $pi4 / 10" | bc)
pi5=$(echo "scale=10; $pi5 / 10" | bc)
pi6=$(echo "scale=10; $pi6 / 10" | bc)
pi7=$(echo "scale=10; $pi7 / 10" | bc)

echo "$pis $pi1 $pi2 $pi3 $pi4 $pi5 $pi6 $pi7" >> $fDAT
# echo "Generating plot..."
# Rscript ex3/ex3.r
# eog $fPNG1
