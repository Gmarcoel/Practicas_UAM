all: conc_cycle
conc_cycle: conc_cycle.o
	gcc conc_cycle.o -o conc_cycle -pthread
conc_cycle.o: conc_cycle.c
	gcc -c conc_cycle.c -g