
CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: pescalar_serie pescalar_par1 pescalar_par2 pescalar_par3 threshold_serial threshold_parallel

pescalar_serie: pescalar_serie.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pescalar_par1: pescalar_par1.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pescalar_par2: pescalar_par2.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pescalar_par3: pescalar_par3.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

threshold_serial: threshold_serial.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

threshold_parallel: threshold_parallel.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

ex2cluster:  threshold_analysis.sh
	qsub -pe openmp 8 -q mv.q threshold_analysis.sh

clean:
	rm -f *.o *~ pescalar_serie pescalar_par1 pescalar_par2 pescalar_par3 threshold_serial threshold_parallel
	
clear:
	rm -f *.o *~