

all: minero monitor

minero: miner.o
	gcc miner.o -o minero -lpthread -lrt

monitor: monitor.o
	gcc monitor.o -o monitor -lpthread -lrt

miner.o: miner.c miner.h
	gcc -c miner.c -g -lpthread -lrt

monitor.o:  monitor.c
	gcc -c monitor.c -g -lprthread -lrt
clean:
	rm *.o
	rm minero
