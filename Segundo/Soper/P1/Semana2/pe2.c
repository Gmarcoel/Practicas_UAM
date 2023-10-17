#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    char *argv[3] = {"mi-ls", "./", NULL};
	const char *a1 = "/usr/bin/ls";
	const char *a12 = "ls";
	const char *a2 = "./";
    pid_t pid;

	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) {
	    if (execl(a1,a1,a2,(char*)NULL)) {
            perror("execl");
            exit(EXIT_FAILURE);
        }
	}
	else {
		wait(NULL);
	}
    exit(EXIT_SUCCESS);
}
