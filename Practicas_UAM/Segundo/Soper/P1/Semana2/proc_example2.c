#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#define  NUM_PROC 3

int  main(void) {
	int i;
	pid_t  pid;
	pid_t pid_padre;
	pid_padre = getpid();	
		for (i = 0; i < NUM_PROC; i++) {
			pid = fork();
			if (pid <   0) {
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0) {
				printf("Hijo %d, Padre  %d\n", getpid(), pid_padre);
				exit(EXIT_SUCCESS);
			}
			else if (pid > 0) {
				printf("Padre  %d\n", i);
			}
		}
		wait(NULL);
	exit(EXIT_SUCCESS);
}
