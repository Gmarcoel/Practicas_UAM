CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: mmuls mmul1 mmul2 mmul3

mmuls: mmul_normal_serial.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

mmul1:  mmul_normal_par1.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

mmul2: mmul_normal_par2.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

mmul3: mmul_normal_par3.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)


ex3cluster:  mmul.sh
	qsub -q mv.q -pe openmp 8 mmul.sh

ex3cluster2:  mmul_graph.sh
	qsub -q mv.q -pe openmp 8 mmul_graph.sh

clean:
	rm -f *.o *~ mmuls mmul1 mmul2 mmul3

clear:
	rm -f *.o *~
