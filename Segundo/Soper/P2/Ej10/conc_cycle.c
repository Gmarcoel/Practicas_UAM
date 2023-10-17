#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <time.h>

#define SECS 100
#define SIZE 50
#define SEM_NAME "/sem_cycle"

pid_t crear_hijo();
void crear_semaforo(sem_t *sem, char *name);
void manejador_sigusr1(int sig);
void manejador_sigterm(int sig);
void esperar_senal(sigset_t *mask);
int check_param(int argc);
void sig_usr1(struct sigaction act);
void sig_int(struct sigaction act2);
void sig_term(struct sigaction act3);
void sig_alrm(struct sigaction act4);
void ciclo(pid_t pid, sigset_t mask_block, sem_t *sem, sem_t *semhijo, pid_t papa);

static volatile int flag_usr1 = 0;
static volatile int flag_term = 0;
pid_t papa;

/**
 * @brief 
 * 
 *
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
	pid_t pid = 0;
	int NUM_PROC;
	int i = 0;
	struct sigaction act, act2, act3, act4;
	sigset_t mask_block;
	sem_t *sem;
	sem_t *semhijo;

	/*Comienzo de la alarma*/
	alarm(SECS);
	/*Comprobamos el número de parámetros*/
	if (!check_param(argc))
		return 0;

	/*Inicializo el conjunto de mi máscara con todas las señales*/
	sigfillset(&mask_block);
	/*Elimino SIGUSR1 de la máscara*/
	sigdelset(&mask_block, SIGUSR1);
	/*Indicamos que la máscara resultante sea la indicada, en este caso mask_block*/
	sigprocmask(SIG_SETMASK, &mask_block, NULL);
	/*Sigaction para SIGUSR1*/
	sig_usr1(act);

	/*Guardamos el argumento en la variable NUM_PROC*/
	NUM_PROC = atoi(argv[1]) - 1;
	/*Guardamos el pid del papá*/
	papa = getpid();

	/*Bucle hasta alcanzar el valor de NUM_PROC*/
	while (i < NUM_PROC)
	{
		/*Creamos un hijo*/
		pid = crear_hijo();

		/*Caso último hijo*/
		if ((i == (NUM_PROC - 1)) && (pid == 0))
		{
			/*El último coge el pid del papá*/
			pid = papa;
			i++;

		}
		/*Caso Padre*/
		if (pid != 0)
		{
			/*
			   crear_semaforo(&sem, name);
			   crear_semaforo(&semhijo, hijo);
			   */

			if (getpid() == papa) /* El papa de todos*/
			{
				sig_int(act2);
				sig_alrm(act4);
				sigdelset(&mask_block, SIGINT);
				sigdelset(&mask_block, SIGALRM);

			}
			else
			{
				sig_term(act3);
				sigdelset(&mask_block, SIGTERM);
			}
			ciclo(pid, mask_block, sem, semhijo,papa);
			i++;
			break;
		}
		i++;
	}
}

void ciclo(pid_t pid, sigset_t mask_block, sem_t *sem, sem_t *semhijo, pid_t papa)
{
	int contador = 0;
	char name[SIZE];
	char hijo[SIZE];

	/*Llamar a semaforos*/
	sprintf(name, "%s_%i", SEM_NAME, getpid());
	sprintf(hijo, "%s_%i", SEM_NAME, pid);

	if (((sem) = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	if (((semhijo) = sem_open(hijo, O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	/*Inicializacion del semaforo*/
	if (getpid() == papa) /* El papa de todos*/
	{
		/*Enviamos SIGUSR1*/
		sleep(1);
		kill(pid, SIGUSR1);
		sem_post(semhijo);
	}
	/*BUCLE*/
	while (1)
	{
		esperar_senal(&mask_block);

		if (flag_usr1 == 1)
		{
			contador++;
			flag_usr1 = 0;
		}
		if (flag_term == 1)
		{

			kill(pid, SIGTERM);
			break;
			exit;
		}
		/*Enviamos al hijo SIGUSR1*/

		/*sleep(.1);*/
		kill(pid, SIGUSR1);
		sem_wait(sem);

		/*Imprimimos el número de ciclo y el PID*/
		printf("Num ciclo: %i, pid: %i\n", contador, getpid());

		sem_post(semhijo);
	}
	sem_close(sem);
	sem_close(semhijo);
	sem_unlink(name);

}

/**
 * @brief 
 * 
 */
void esperar_senal(sigset_t *mask)
{
	sigsuspend(mask);
	return;
}
/**
 * @brief Crea un hijo del proceso y devuelve su pid
 * 
 * @return pid_t pid del hijpo
 */
pid_t crear_hijo()
{
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return pid;
}
/**
 * @brief 
 * 
 * @param sig 
 */
void manejador_sigusr1(int sig)
{
	flag_usr1 = 1;
	return;
}
void manejador_sigterm(int sig)
{
	flag_term = 1;

	return;
}

/**
 * @brief Función que comprueba el número de parámetros introducidos
 * 
 * @param argc : número de parámetros
 * @return int : devuelve 1 si es correcto, 0 si es incorrecto
 */
int check_param(int argc)
{
	if (argc == 2)
		return 1;
	printf("Número incorrecto de argumentos\n");
	return 0;
}
/**
 * @brief 
 * 
 * @param act 
 */
void sig_usr1(struct sigaction act)
{
	act.sa_handler = manejador_sigusr1;
	sigemptyset(&(act.sa_mask));
	act.sa_flags = 0;

	if (sigaction(SIGUSR1, &act, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

void sig_int(struct sigaction act2)
{
	act2.sa_handler = manejador_sigterm;
	sigemptyset(&(act2.sa_mask));
	act2.sa_flags = 0;

	if (sigaction(SIGINT, &act2, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

void sig_term(struct sigaction act3)
{
	act3.sa_handler = manejador_sigterm;
	sigemptyset(&(act3.sa_mask));
	act3.sa_flags = 0;

	if (sigaction(SIGTERM, &act3, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

void sig_alrm(struct sigaction act4)
{
	act4.sa_handler = manejador_sigterm;
	sigemptyset(&(act4.sa_mask));
	act4.sa_flags = 0;
	if (sigaction(SIGALRM, &act4, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

