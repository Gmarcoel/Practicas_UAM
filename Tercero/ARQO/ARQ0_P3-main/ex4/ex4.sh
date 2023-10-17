#!/bin/bash

# Experiment 1
# Change associativity on a cache
# ----------------------------------------------------------------------------------

P=4
 ((    Ninicio=256 ))
 ((    Nfinal=1024 + 256))

small_cache_size="1024"
((	large_cache_size=(8*1024*1024)	))


for ((associativity=1; associativity<=8; associativity=2*associativity));
do
    rm -f "ex4/ex4_data/associativity_"$associativity".dat"
    for ((N=Ninicio; N<=Nfinal; N=N+256));
    do

        

        valgrind --tool=cachegrind --cachegrind-out-file=ex4/out.dat  \
            --I1=$small_cache_size,$associativity,64 \
            --D1=$small_cache_size,$associativity,64 \
            --LL=$large_cache_size,$associativity,64 \
            ./ex3/ex3_normal $N
        normalmr=$(cg_annotate ex4/out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        normalmw=$(cg_annotate ex4/out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        rm -f "ex4/out.dat"


        valgrind --tool=cachegrind --cachegrind-out-file=ex4/out.dat \
            --I1=$small_cache_size,$associativity,64 \
            --D1=$small_cache_size,$associativity,64 \
            --LL=$large_cache_size,$associativity,64 \
            ./ex3/ex3_trasposed $N
        transposedmr=$(cg_annotate ex4/out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        transposedmw=$(cg_annotate ex4/out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
        rm -f "ex4/out.dat"
        echo "$N $normalmr $normalmw $transposedmr $transposedmw" >> "ex4/ex4_data/associativity_"$associativity".dat"
        
        # Guardar como <N> <D1mr “slow”> <D1mw “slow”> <D1mr “fast”> <D1mw “fast”> 
    done
done


# Experiment 2
# Change cache size on small cache with fixed matrix size
 ((    N=512  ))
 (( cache_inicial=128 ))
 (( cache_final=1024 ))
((	large_cache_size=(8*1024*1024)	))


#Nfinal=4000
fDAT=ex4/exp2.dat
fPNG1=ex4/exp2/mult_time.png
fPNG2=ex4/exp2/mult_cache.png
# The first level cache sizes (data and instructions) to test are 1024, 
# 2048, 4096 y 8192 Bytes, and the second level cache size is 8 Mbytes.
# All caches are direct 
# mapped (1 way) and the block size is 64 bytes

rm -f $fDAT fPNG
touch $fDAT

for ((cache=cache_inicial; cache<=cache_final; cache=cache*2));
do

    echo "N: $cache / $cache_final..."
	normTime=0
	trasTime=0
    normmr=0
    trasmr=0
    normmw=0
    trasmw=0
	

    valgrind --tool=cachegrind --cachegrind-out-file=ex4/out.dat \
        --I1=$cache,1,64 \
        --D1=$cache,1,64 \
        --LL=$large_cache_size,1,64 \
        ./ex3/ex3_normal $N
	normmr=$(cg_annotate ex4/out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	normmw=$(cg_annotate ex4/out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	rm -f "ex4/out.dat"

	valgrind --tool=cachegrind --cachegrind-out-file=ex4/out.dat \
        --I1=$cache,1,64 \
        --D1=$cache,1,64 \
        --LL=$large_cache_size,1,64 \
        ./ex3/ex3_trasposed $N 
	trasmr=$(cg_annotate ex4/out.dat --show=D1mr | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	trasmw=$(cg_annotate ex4/out.dat --show=D1mw | head -n 30 | grep -n TOTALS | awk '{print $1}' | sed 's/,//g' | sed 's/18://g')
	rm -f "ex4/out.dat"

	
    for i in {1..10};
	do
		
		normTime=$(echo "scale=10; $normTime+$(./ex3/ex3_normal $N | grep 'time' | awk '{print $3}')" | bc)
		#if $N + $Npaso <= $Nfinal;
		trasTime=$(echo "scale=10; $trasTime+$(./ex3/ex3_trasposed $N | grep 'time' | awk '{print $3}')" | bc)
	done

	normTime=$(echo "scale=10; $normTime / 10" | bc)
	trasTime=$(echo "scale=10; $trasTime / 10" | bc)


    echo "$cache $normTime $normmr $normmw $trasTime $trasmr $trasmw" >> $fDAT
    
done

echo "Generating plot..."
Rscript ex4/ex4.r
eog $fPNG1
eog $fPNG2f
eog ex4/exp1/cache_lectura.png
eog ex4/exp1/cache_escritura.png
