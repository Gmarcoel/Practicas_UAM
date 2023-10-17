all: proc_shell abort
	proc_shell: proc_shell.o
	gcc proc_shell.o -o proc_shell -lpthread

abort: abort.o
	gcc abort.o -o abort

proc_shell.o: proc_shell.c
	gcc -c proc_shell.c

abort.o: abort.c
	gcc -c abort.c

clean:
	rm *.o proc_shell abort
