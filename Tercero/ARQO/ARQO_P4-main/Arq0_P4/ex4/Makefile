CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: pi_serie pi_par1 pi_par2 pi_par3 pi_par4 pi_par5 pi_par6 pi_par7

pi_serie: pi_serie.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pi_par1: pi_par1.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pi_par2: pi_par2.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pi_par3: pi_par3.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pi_par4: pi_par4.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pi_par5: pi_par5.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pi_par6: pi_par6.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pi_par7: pi_par7.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)


ex4cluster: pi.sh
	qsub -q mv.q -pe openmp 8 pi.sh


clean:
	rm -f *.o *~ pi_serie pi_par1 pi_par2 pi_par3 pi_par4 pi_par5 pi_par6 pi_par7 
	
clear:
	rm -f *.o *~
