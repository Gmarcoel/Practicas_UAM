#!/bin/bash
#
#$ -S /bin/bash
#$ -cwd
#$ -o simple.out
#$ -j y
export OMP_NUM_THREADS=$NSLOTS 

N=2000
fDAT=mmul_graph.dat
fPNG1=mmul.png
P=4

rm -f $fDAT fPNG
touch $fDAT



((    Ninicio=512+$P+1024   ))
((    Nfinal=1024+512+$P+1024   ))
Npaso=64


rm -f $fDAT fPNG
touch $fDAT

for ((N=Ninicio; N<=Nfinal; N += (Npaso*2)));
do

    echo "N: $N / $Nfinal..."
	
	
    times=0
    timeb=0
    for i in {1..5};
	do
        times=$(echo "scale=10; $times+$(./mmuls $N | grep 'time' | awk '{print $3}')" | bc)
        timeb=$(echo "scale=10; $timeb+$(./mmul3 $N 4 | grep 'time' | awk '{print $3}')" | bc)

	done
    times=$(echo "scale=10; $times / 5" | bc)
    timeb=$(echo "scale=10; $timeb / 5" | bc)


    echo "$N $times $timeb" >> $fDAT
    
done



echo "Generating plot..."
Rscript mmul_graph.r
eog $fPNG1

