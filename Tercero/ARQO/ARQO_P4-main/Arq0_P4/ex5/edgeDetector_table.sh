#!/bin/bash
#
#$ -S /bin/bash
#$ -cwd
#$ -o simple.out
#$ -j y
export OMP_NUM_THREADS=$NSLOTS


fDAT=edgeDetector_table.dat

rm edgeDetector_table.dat


images="Imagenes_Prueba/SD.jpg Imagenes_Prueba/HD.jpg Imagenes_Prueba/FHD.jpg Imagenes_Prueba/4k.jpg Imagenes_Prueba/8k.jpg"
echo "IMAGEN SERIAL MODIFIED PARALLEL FPS" >> $fDAT

for image in $images;
do
    tiempo=0
    tiempo_mod=0
    tiempo_par=0
	fps=0

    for i in {1..5};
    do
        tiempo_mod=$(echo "scale=10; $tiempo_mod+$(./edgeDetector_mod $image | grep Tiempo | awk '{print $2}')" | bc)
        tiempo=$(echo "scale=10; $tiempo+$(./edgeDetector $image | grep Tiempo | awk '{print $2}')" | bc)
        tiempo_par=$(echo "scale=10; $tiempo_par+$(./edgeDetector_par $image | grep Tiempo | awk '{print $2}')" | bc)
    done  
    tiempo=$(echo "scale=10; $tiempo / 5" | bc)
    tiempo_mod=$(echo "scale=10; $tiempo_mod / 5" | bc)
    tiempo_par=$(echo "scale=10; $tiempo_par / 5" | bc)
    fps=$(echo "scale=10; 1/$tiempo" | bc)



    echo "$image $tiempo $tiempo_mod $tiempo_par $fps" >> $fDAT
    echo "$image $tiempo $tiempo_mod $tiempo_par $fps"
    
done



