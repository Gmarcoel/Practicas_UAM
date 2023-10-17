#!/bin/bash
#
#$ -S /bin/bash
#$ -cwd
#$ -o simple.out
#$ -j y
export OMP_NUM_THREADS=$NSLOTS

N=1000
fDAT=mmul1000.dat

P=4


touch $fDAT

echo "Times for matrix of size $N"

# Serial time for # threads = 1
times=0
for i in {1..10};
do
	times=$(echo "scale=10; $times+$(./mmuls $N | grep 'time' | awk '{print $3}')" | bc)
done
times=$(echo "scale=10; $times / 10" | bc)

# Parallel times for all # threads
for threads in {1..4};
do
	
    time1=0
    time2=0
    time3=0
    for i in {1..10};
	do
		
		time1=$(echo "scale=10; $time1+$(./mmul1 $N $threads | grep 'time' | awk '{print $3}')" | bc)
        time2=$(echo "scale=10; $time2+$(./mmul2 $N $threads | grep 'time' | awk '{print $3}')" | bc)
        time3=$(echo "scale=10; $time3+$(./mmul3 $N $threads | grep 'time' | awk '{print $3}')" | bc)

	done
    time1=$(echo "scale=10; $time1 / 10" | bc)
    time2=$(echo "scale=10; $time2 / 10" | bc)
    time3=$(echo "scale=10; $time3 / 10" | bc)



    echo "$threads $times $time1 $time2 $time3" >> $fDAT
	times="-"
    
done

N=2000
fDAT=mmul2000.dat

P=4

rm -f $fDAT
touch $fDAT

echo "Times for matrix of size $N"

# Serial time for # threads = 1
times=0
for i in {1..10};
do
	times=$(echo "scale=10; $times+$(./mmuls $N | grep 'time' | awk '{print $3}')" | bc)
done
times=$(echo "scale=10; $times / 10" | bc)

# Parallel times for all # threads
for threads in {1..4};
do
	
    time1=0
    time2=0
    time3=0
    for i in {1..10};
	do
		
		time1=$(echo "scale=10; $time1+$(./mmul1 $N $threads | grep 'time' | awk '{print $3}')" | bc)
        time2=$(echo "scale=10; $time2+$(./mmul2 $N $threads | grep 'time' | awk '{print $3}')" | bc)
        time3=$(echo "scale=10; $time3+$(./mmul3 $N $threads | grep 'time' | awk '{print $3}')" | bc)

	done
    time1=$(echo "scale=10; $time1 / 10" | bc)
    time2=$(echo "scale=10; $time2 / 10" | bc)
    time3=$(echo "scale=10; $time3 / 10" | bc)



    echo "$threads $times $time1 $time2 $time3" >> $fDAT
	times="-"
    
done










# echo "Generating plot..."
# Rscript ex3/ex3.r
# eog $fPNG1

