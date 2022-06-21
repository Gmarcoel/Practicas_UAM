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
	pid_t ppid = getpid();
	pid = fork();
	for (i = 0; i < NUM_PROC; i++) {
		if (pid <   0) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) {
			printf("Hijo: %i\n",i);
			printf("	Id %d, Padre  %d\n", getpid(), ppid);
			ppid = getpid();
			pid = fork();
		}
		else if (pid > 0) {
			printf("Padre %i terminado\n",i);
		}
	}
		wait(NULL);
	exit(EXIT_SUCCESS);
}
