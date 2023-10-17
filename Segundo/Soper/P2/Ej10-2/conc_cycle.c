#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t crear_hijo();
void manejador_sigusr1(int sig);
void manejador_sigint(int sig);
void manejador_sigterm(int sig);
void esperar_señal();
int check_param(int argc);
void sig_usr1(struct sigaction act);
void sig_int(struct sigaction act2);
void sig_term(struct sigaction act3);
void ciclo(pid_t pid, sigset_t mask_block);


static volatile int flag_usr1 = 0;
static volatile int flag_int = 0;
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
	struct sigaction act, act2, act3;
	sigset_t mask_block;

	/*Comprobamos el número de parámetros*/
	if (!check_param(argc))
		return 0;

	sigfillset(&mask_block);
	/*mascara con todo*/
	sigprocmask(SIG_SETMASK,&mask_block,NULL);
	sigemptyset(&(act.sa_mask));
	act.sa_flags = 0;
	sigemptyset(&(act2.sa_mask));
	act2.sa_flags = 0;
	sigemptyset(&(act3.sa_mask));
	act3.sa_flags = 0;
	/*Sigaction para SIGUSR1*/
	sig_usr1(act);
	/*Guardamos el argumento en la variable NUM_PROC*/
	NUM_PROC = atoi(argv[1]) - 1;
	/*Guardamos el pid del papá*/
	papa = getpid();
	sigdelset(&mask_block,SIGUSR1);
	/*Bucle hasta alcanzar el valor de NUM_PROC*/
	while (i < NUM_PROC && pid==0)
	{
		/*Creamos un hijo*/
		pid = crear_hijo();
		i++;
	}
	/*Caso último hijo*/
	if (pid == 0)
	{
		/*El último coge el pid del papá*/
		pid = papa;

	} 
	/*Caso Padre*/
	if (papa ==getpid())
	{
		sig_int(act2);
		/*sig_alarm(act4);*/
		sigdelset(&mask_block,SIGINT);
		sigdelset(&mask_block,SIGALRM);
		/*ciclo(pid, mask_block);
		  i++;
		  break;*/
	}
	if (papa!=getpid()){
		sig_term(act3);
		sigdelset(&mask_block,SIGTERM);
	}
	ciclo(pid,mask_block);


}

void ciclo(pid_t pid, sigset_t mask_block)
{
	int contador = 0;

	while (1)
	{

		esperar_señal(&mask_block);

		if(flag_usr1 == 1)
		{
			contador ++;
			flag_usr1 = 0;
		}
		if((getpid()==papa) && (flag_int==1)){
			kill(pid,SIGTERM);
			break;
			exit;
		}
		if(flag_term == 1)
		{
			kill(pid,SIGTERM);
			break;
			exit;
		}
		/*Enviamos al hijo SIGUSR1*/
		kill(pid, SIGUSR1);
		/*Imprimimos el número de ciclo y el PID*/
		printf("Num ciclo: %i, pid: %i\n", contador, pid);


	}
}

/**
 * @brief 
 * 
 */
void esperar_señal(sigset_t *mask)
{
	sigsuspend(mask);
	return;
}
/**
 * @brief Crea un hijo del proceso y devuelve su pid
 * 
 * @return pid_t pid del hijo
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
void manejador_sigint(int sig){
	flag_int = 1;
	return;
}
void manejador_sigterm(int sig){
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

void sig_int(struct sigaction act2) {
	act2.sa_handler = manejador_sigint;
	sigemptyset(&(act2.sa_mask));
	act2.sa_flags = 0;

	if (sigaction(SIGINT, &act2, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

void sig_term(struct sigaction act3) {
	act3.sa_handler = manejador_sigint;
	sigemptyset(&(act3.sa_mask));
	act3.sa_flags = 0;

	if (sigaction(SIGTERM, &act3, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}
