CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: omp1 omp2

omp1: omp1.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

omp2: omp2.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)
	
clean:
	rm -f *.o *~ omp1 omp2
	
clear:
	rm -f *.o *~