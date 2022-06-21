#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEM_NAME_A "/example_sem_1"
#define SEM_NAME_B "/example_sem_2"

int main(void) {
	sem_t *sem1 = NULL;
	sem_t *sem2 = NULL;
	pid_t pid;
	/*Semaforo 1*/
	if ((sem1 = sem_open(SEM_NAME_A, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED) {
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	/*Semaforo 2*/
	if ((sem2 = sem_open(SEM_NAME_B, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED) {
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	/*Creamos hijo*/
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	/*Hijo*/
	if (pid == 0) {
        /* Rellenar Código A */
		printf("1\n");
        /* Rellenar Código B */
		sem_post(sem1);
		sem_wait(sem2);
		
		printf("3\n");
        /* Rellenar Código C */
		sem_post(sem1);

		sem_close(sem1);
		sem_close(sem2);
	}
	/*Padre*/
	else {
        /* Rellenar Código D */
		sem_wait(sem1);

		printf("2\n");
        /* Rellenar Código E */
		sem_post(sem2);
		sem_wait(sem1);

		printf("4\n");
        /* Rellenar Código F */

		sem_close(sem1);
		sem_close(sem2);
		sem_unlink(SEM_NAME_A);
		sem_unlink(SEM_NAME_B);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}
