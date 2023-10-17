/**
 *  * @file proc_shell.c
 *   * @author Elena Balseiro & Guillermo Martín-Coello
 *    * @brief Práctica 1, ejercicio 13
 *     * @version 1.0
 *      * @date 2021-03-08
 *       * 
 *        * @copyright Copyright (c) 2021
 *         * 
 *          */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 80
#define NARG 30
#define FILE1 "log.txt"

/**
 *  * @brief Estructura que incluye un string con finalidad de contener los comandos y un array para separarlos por elementos.
 *   * 
 *    */
typedef struct
{
	char string[SIZE];
	char *array[NARG];
} Est;

/**
 *  * @brief Función para separar los diferentes elementos del comando escrito e introduciorlos en un array.
 *   * 
 *    * @param arg estructura que incluye tanto el string con el comando como el array resultante.
 *     * @return void* 
 *      */
void *chop(void *arg)
{
	Est *est = arg;
	int i = 1;
	est->array[0] = strtok(est->string, " ");

	while (((est->array[i]) = strtok(NULL, " ")) != NULL)
	{
		i++;
	}

	est->array[i] = NULL;
}

/**
 *  * @brief Programa que lee comandos (hasta indicar EOF) y lo ejecuta a modo de terminal.
 *   *        También guarda un historial de los comandos junto con el estado de su salida.
 *    * 
 *     * @return int 
 *      */

int main()
{
	int status, error, i = 0, j = 0;
	pid_t pid, logpid;
	Est est;
	pthread_t h1;

	int pipe_status;
	int fd[2];
	ssize_t nbyte;
	char readpipe[120];

	int file;
	int nbytes=0;
	size_t target_size;
	ssize_t size_written, total_size_written;
	char message[SIZE];

	/*Creamos la tubería*/
	pipe_status = pipe(fd);
	if (pipe_status == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	/*Creamos el proceso encargado de gestionar el log.txt*/
	logpid = fork();
	if (logpid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	else if (logpid == 0)
	{
		close(fd[1]);

		if ((file = open(FILE1, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		nbytes=0;
		do
		{
			nbytes = read(fd[0], readpipe, sizeof(readpipe));

			if (nbytes == -1)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}

			if (nbytes > 0)
			{
				dprintf(file, "%s", readpipe);
			}

		} while (nbytes != 0);


		close(fd[0]);
		close(file);

	}
	else if (logpid > 0)
	{
		/*Pedimos al usuario que inserte el comando deseado*/
		close(fd[0]);
		printf("\033[0;36mInserte línea de comando\033[0;31m:\033[0m");
		while (fgets(est.string, SIZE, stdin) != NULL)
		{




			i = 0;
			while (est.string[i] != '\n')
			{
				i++;
			}
			est.string[i] = '\0';


			/*Escribimos el comando utilizado en la tubería para que lo reciba el hijo*/
			nbytes = write(fd[1], est.string, strlen(est.string) + 1);
			if (nbytes == -1)
			{
				perror("write");
				exit(EXIT_FAILURE);
			}

			/*Creamos un hilo encargado de ejecutar la función "chop" */
			error = pthread_create(&h1, NULL, chop, &est);
			if (error != 0)
			{
				dprintf(fd[1], "pthread_create: %s\n", strerror(error));
			}

			error = pthread_join(h1, NULL);
			if (error != 0)
			{
				dprintf(fd[1], "pthread_join: %s\n", strerror(error));
			}

			/*Creamos un proceso encargado de ejecutar el comando*/
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}

			else if (pid == 0)
			{
				/*Ejecutamos el comando*/
				if (execvp(est.array[0], est.array))
				{
					perror("execvp");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid > 0)
			{
				/*Imprimimos el valor de salida*/
				wait(&status);
				if (WIFEXITED(status))
				{
					dprintf(fd[1], "\nExited with value %d\n\n", WEXITSTATUS(status));
				}
				else if (WIFSIGNALED(status))
				{
					dprintf(fd[1], "\nTerminated by signal %d\n\n", WTERMSIG(status));
				}
			}

			est.string[0] = '\0';
			printf("\033[0;36mInserte línea de comando\033[0;31m:\033[0m");
		}
		close(fd[1]);
		wait(NULL);
		printf("\n\033[0;31mExited\n\033[0m");
	}

	return 0;
}
