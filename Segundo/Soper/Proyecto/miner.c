#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "miner.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>

#define PRIME 99997669
#define BIG_X 435679812
#define BIG_Y 100001819
#define SEM_NAME "/sem_net"
#define SEM_VOTE_NAME "/sem_vote"
#define SEM_UPDATE_NAME "/sem_update"
#define SEM_SINCRO "/sem_sincro"
#define MQ_NAME "/mq_monitor"

static volatile int flag = 0;
static volatile int end = 0; // para acabar de manera limpia

/* Estructura que envía el hilo principal a los demás hilos*/
typedef struct _Info
{
	int target;
	long solution;
	NetData *net;
	Block *block;
	//Block *private_block;
	sem_t *sem;
	int index;
	int winner;
} Info;

/* Manejador de la señal sigint */
void manejador_sigint(int sig)
{
	end = 1;
	return;
}

/* Inicializador de la señal sigint */
void sig_int(struct sigaction act)
{
	act.sa_handler = manejador_sigint;
	sigemptyset(&(act.sa_mask));
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

/* Manejador de la señal sigusr1 */
void manejador_sigusr1(int sig)
{
	return;
}

/* Inicializador de la señal sigusr1 */
void sig_usr1(struct sigaction act1)
{
	act1.sa_handler = manejador_sigusr1;
	sigemptyset(&(act1.sa_mask));
	act1.sa_flags = 0;

	if (sigaction(SIGUSR1, &act1, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

/* Manejador de la señal sigusr2 */
void manejador_sigusr2(int sig)
{
	flag = 1;
	return;
}

/* Inicializador de la señal sigusr2 */
void sig_usr2(struct sigaction act2)
{
	act2.sa_handler = manejador_sigusr2;
	sigemptyset(&(act2.sa_mask));
	act2.sa_flags = 0;

	if (sigaction(SIGUSR2, &act2, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return;
}

/* Funcion dar de baja */
void baja(Info *info, pid_t net_shm, NetData *net, pid_t block_shm, sem_t * sem, sem_t * sem_vote, sem_t * sem_update_block, sem_t * sem_sincro, mqd_t cola)
{
	sem_wait(sem);
	net->miners_pid[info->index] = -1;
	fprintf(stderr, "\nSearch completed with result %ld\n", info->solution);
	sem_post(sem);
	close(block_shm);
	close(net_shm);
	mq_close(cola);
	//shm_unlink(SHM_NAME_BLOCK);
	//shm_unlink(SHM_NAME_NET);
	sem_close(sem);
	sem_close(sem_vote);
	sem_close(sem_update_block);
	sem_close(sem_sincro);
	//sem_unlink(SEM_NAME);
	//sem_unlink(SEM_NAME);
	//sem_unlink(SEM_NAME);
	//sem_unlink(SEM_NAME);
	exit(EXIT_SUCCESS);
}

/* Función tipo hash */
long int simple_hash(long int number)
{
	long int result = (number * BIG_X + BIG_Y) % PRIME;
	return result;
}

/* Escribe los bloques existentes ?? */
void print_blocks(Block *plast_block, int num_wallets)
{
	Block *block = NULL;
	int i, j;

	for (i = 0, block = plast_block; block != NULL; block = block->prev, i++)
	{
		printf("Block number: %d; Target: %ld;    Solution: %ld\n", block->id, block->target, block->solution);
		for (j = 0; j < num_wallets; j++)
		{
			printf("%d: %d;         ", j, block->wallets[j]);
		}
		printf("\n\n\n");
	}
	printf("A total of %d blocks were printed\n", i);
}

/* Función minera */
void *mining(void *voidInfo)
{
	int i, j;
	Info *info = voidInfo;

	for (i = 0; i < PRIME; i++)
	{
		if (flag == 1)
		{
			/***************************************/
			/* TEST 02: Fin de hilos */
			printf("\x1b[32m"); // VERDE
			printf("***************************\n");
			printf("\x1b[33m"); // AMARILLO
			printf("TEST 02: Fin de hilos\n");
			printf("\x1b[31m"); // ROJO
			printf("-----------------------\n");
			printf("\x1b[34m"); // AZUL
			printf("INFO:\n");
			printf("	Hilo de minero %i finalizado con éxito\n", info->index);
			printf("\x1b[32m"); // VERDE
			printf("***************************\n");
			printf("\x1b[0m"); // NEGRO

			/***************************************/

			return NULL;
		}
		if (end == 1)
		{
			flag = 1; // Sale de aquí para terminar bien los hilos
		}
		fprintf(stdout, "Searching... %6.2f%%\r", 100.0 * i / PRIME);

		if (info->target == simple_hash(i))
		{
			fprintf(stdout, "\nSolution: %d\n", i);
			flag = 1;
			info->solution = i;
			sem_wait(info->sem);

			for (j = 0; j < info->net->total_miners; j++)
			{
				if (!(j == info->index))
				{
					/***************************************/
					/* TEST 03: Envío de señales*/
					printf("\x1b[32m"); // VERDE
					printf("***************************\n");
					printf("\x1b[33m"); // AMARILLO
					printf("TEST 03: Envío de señales\n");
					printf("\x1b[31m"); // ROJO
					printf("-----------------------\n");
					printf("\x1b[34m"); // AZUL
					printf("INFO:\n");
					printf("	Señal enviada a minero número %i con pid %i\n", j, info->net->miners_pid[j]);
					printf("\x1b[32m"); // VERDE
					printf("***************************\n");
					printf("\x1b[0m"); // NEGRO

					/***************************************/
					kill(info->net->miners_pid[j], SIGUSR2);
					printf("Signal %i sent\n", j);
				}
			}
			/* Subir el resultado como ganador	*/
			info->winner = 1;
			info->block->solution = i;

			sem_post(info->sem);
			return NULL;
		}
	}
}

/* Main donde se inicializan los ilos y demás */
int main(int argc, char *argv[])
{
	long target;
	int workers, i;
	pthread_t h[MAX_WORKERS];
	int error;
	struct sigaction act;
	struct sigaction act1;
	struct sigaction actint;
	Info info;
	Block *block;
	Block *private_block = NULL, *aux;
	NetData *net;
	pid_t block_shm, net_shm;
	sem_t *sem, *sem_vote, *sem_update_block, *sem_sincro;
	pid_t last_winner;
	sigset_t mask_block12, mask_block1, mask_block2;
	int n_votes, n_rounds;
	mqd_t cola;



	sig_usr2(act);
	sig_usr1(act1);
	sig_int(actint);

	/*Inicialización de la máscara vacía*/
	sigemptyset(&mask_block2);
	/*Añadimos la señar sigusr1 y sigusr2*/
	sigaddset(&mask_block2, SIGUSR2);
	/*Inicialización de la máscara vacía*/
	sigemptyset(&mask_block12);
	/*Añadimos la señar sigusr1 y sigusr2*/
	sigaddset(&mask_block12, SIGUSR1);
	sigaddset(&mask_block12, SIGUSR2);
	/*Indicamos que la máscara resultante sea mask_block12*/
	sigprocmask(SIG_SETMASK, &mask_block12, NULL);

	/*Inicialización de la máscara vacía*/
	sigemptyset(&mask_block1);
	/*Añadimos la señar sigusr1*/
	sigaddset(&mask_block1, SIGUSR1);
	/*Indicamos que la máscara resultante sea mask_block1*/
	sigprocmask(SIG_SETMASK, &mask_block1, NULL);

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <TARGET>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	workers = atol(argv[2]);
	n_rounds = atol(argv[1]); // esto en un futuro va a ser el número de rondas a realizar

	if ((sem = sem_open(SEM_NAME, O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	if ((sem_vote = sem_open(SEM_VOTE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	if ((sem_update_block = sem_open(SEM_UPDATE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}

	if ((sem_update_block = sem_open(SEM_UPDATE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	if ((sem_sincro = sem_open(SEM_SINCRO, O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	/*Inicializacion de memoria compartida*/
	block_shm = shm_open(SHM_NAME_BLOCK, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (block_shm == -1)
	{
		if (errno == EEXIST)
		{
			block_shm = shm_open(SHM_NAME_BLOCK, O_RDWR, 0);
			if (net_shm == -1)
			{
				perror("Error opening the shared memory segment");
				exit(EXIT_FAILURE);
			}
			/*Mapeamos el segmento de memoria compartida*/
			if ((block = mmap(NULL, sizeof(Block), PROT_READ | PROT_WRITE, MAP_SHARED, block_shm, 0)) == MAP_FAILED)
			{
				perror("mmap error");
			}
		}
		else
		{
			perror("Error creating the shared memory segment\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Shared memory segment created\n");
		/*Ampliamos el espacio*/
		if (ftruncate(block_shm, sizeof(Block)) == -1)
		{
			perror("ftruncate");
			close(block_shm);
			exit(EXIT_FAILURE);
		}
		/*Mapeamos el segmento de memoria compartida*/
		if ((block = mmap(NULL, sizeof(Block), PROT_READ | PROT_WRITE, MAP_SHARED, block_shm, 0)) == MAP_FAILED)
		{
			perror("mmap error");
		}
		/* Inicializamos bloque */
		sem_wait(sem);
		block->id = 1;
		block->is_valid = 0;
		block->next = NULL;
		block->prev = NULL;
		block->solution = -1;
		block->target = 1;
		for (i = 0; i < 200; i++)
		{
			block->wallets[i] = 0;
		}
		sem_post(sem);
	}
	net_shm = shm_open(SHM_NAME_NET, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (net_shm == -1)
	{
		if (errno == EEXIST)
		{
			net_shm = shm_open(SHM_NAME_NET, O_RDWR, 0);
			if (net_shm == -1)
			{
				perror("Error opening the shared memory segment");
				exit(EXIT_FAILURE);
			}
			/* Mapeamos	*/
			if ((net = mmap(NULL, sizeof(NetData), PROT_READ | PROT_WRITE, MAP_SHARED, net_shm, 0)) == MAP_FAILED)
			{
				perror("mmap error");
			}
		}
		else
		{
			perror("Error creating the shared memory segment\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Shared memory segment created\n");
		/*Ampliamos el espacio*/
		if (ftruncate(net_shm, sizeof(NetData)) == -1)
		{
			perror("ftruncate");
			close(net_shm);
			exit(EXIT_FAILURE);
		}
		/* Mapeamos	*/
		if ((net = mmap(NULL, sizeof(NetData), PROT_READ | PROT_WRITE, MAP_SHARED, net_shm, 0)) == MAP_FAILED)
		{
			perror("mmap error");
		}
		/* Inicializamos net	*/

		sem_wait(sem);
		net->last_miner = -1;
		net->total_miners = 0;
		net->monitor_pid = -1;
		net->last_winner = -1;
		net->counter = 0;
		for (i = 0; i < MAX_MINERS; i++)
		{
			net->miners_pid[i] = 0;
			net->voting_pool[i] = -1;
		}
		sem_post(sem);
	}

	//Estructura atributos cola
    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(*private_block)};
	//Abrimos la cola
	(cola) = mq_open(MQ_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attributes);
	if ((cola) == (mqd_t)-1)
	{
		perror("mqueue");
		return -1;
	}

	/*	Dar de alta al minero	*/
	sem_wait(sem);
	if (net->last_winner == -1)
		net->last_winner = getpid(); // Para que haya un ganador de la ronda anterior en caso de que sea la primera ronda
	net->total_miners++;
	net->last_miner = (net->total_miners) - 1;
	net->miners_pid[net->last_miner] = getpid();
	info.index = net->last_miner; // guardamos el indice de la net en la estructura info
	sem_post(sem);

	/*	Inicializamos info */
	info.net = net;
	info.sem = sem;
	info.block = block;
	info.winner = 0;
	sem_wait(sem);
	info.target = block->target;
	sem_post(sem);

	/* TEST 01: Pre-ronda 1 */
	printf("\x1b[32m"); // VERDE
	printf("***************************\n");
	printf("\x1b[33m"); // AMARILLO
	printf("TEST 01: Pre-ronda 1\n");
	printf("\x1b[31m"); // ROJO
	printf("-----------------------\n");
	printf("\x1b[34m"); // AZUL
	printf("INFO:\n");
	printf("	Target: %i\n	Solution: %li\n	NetData: %i\n	Block: %i\n	Sem: %i\n	Index: %i\n	Winner: %i\n", info.target, info.solution, info.net, info.block, info.sem, info.index, info.winner);
	sem_wait(sem);
	printf("PROCESOS\n	%i, %i\n", net->miners_pid[0], net->miners_pid[1]);
	sem_post(sem);
	printf("INDEX %i\n", info.index);
	printf("\x1b[32m"); // VERDE
	printf("***************************\n");
	printf("\x1b[0m"); // NEGRO
	while (n_rounds != 0)
	{
		/*Indicamos que la máscara resultante sea mask_block1*/
		sigprocmask(SIG_SETMASK, &mask_block1, NULL);
		sem_wait(sem);
		info.target = block->target;
		sem_post(sem);

		/*	Creación de hilos*/
		for (i = 0; i < workers; i++)
		{
			error = pthread_create(&h[i], NULL, mining, &info);
			if (error != 0)
			{
				fprintf(stderr, "pthread_create\n");
			}
		}
		/* Limpieza de hilos */
		for (i = 0; i < workers; i++)
		{
			error = pthread_join(h[i], NULL);
		}
		if (end == 1)
		{
			baja(&info,net_shm, net, block_shm, sem, sem_vote, sem_update_block, sem_sincro, cola);
		}
		/* Verificar solución*/
		printf("Salimos de los hilos\n");

		/* Ultimo ganador hace el quorum de la votación */
		sem_wait(sem);
		last_winner = net->last_winner;
		sem_post(sem);
		if (getpid() == last_winner) // si se borra el minero que es last winner otro debería hacer esto
		{
			printf("Aquí está el último minero haciendo el quorum\n");
			sem_wait(sem);
			net->total_miners = 0;
			net->counter = 0;
			for (i = 0; i < MAX_MINERS; i++)
			{
				if ((net->miners_pid[i] != 0) && (kill(net->miners_pid[i], SIGUSR1) == 0))
				{
					(net->total_miners)++;
					(net->counter)++; // usamos el counter para sincronizar los procesos
					printf("	señal 1 mandada\n");
				}
				else
				{
					net->miners_pid[i] = 0; // Si no está activo se da de baja
				}
			}
			printf("	El quorum da %i mineros activos\n", net->total_miners);
			(net->counter)--; // la de el proceso que hace el quorum
			sem_post(sem);
			sigprocmask(SIG_SETMASK, &mask_block12, NULL);
			sem_post(sem_vote);
			while (1)
			{
				sem_wait(sem);
				printf("el counter está a: %i\n", net->counter);
				if (net->counter == 0)
					break; //Espera a que todos los procesos esten sincronizados y tengan nueva máscara
				sem_post(sem);
			}
			sem_post(sem);
		}
		else
		{
			sigprocmask(SIG_SETMASK, &mask_block12, NULL);
			printf("	Espero a la señal 1\n");
			sigsuspend(&mask_block2); // Aquí se espera a que llegue sigusr1 para añadir a la máscara la sigusr2
			printf("	He esperado a la señal 1\n");

			sem_wait(sem);
			(net->counter)--;
			sem_post(sem);
		}

		/* Votación*/
		printf("Aqui empieza la votación con winner: %i\n", info.winner);
		if (info.winner == 1)
		{
			printf("	Aquí está entrando el ganador...\n");

			sem_wait(sem_vote);
			printf("	Aquí entra el ganador\n");

			sem_wait(sem);
			for (i = 0; i < MAX_MINERS; i++)
			{
				if (net->miners_pid[i] != getpid() && (net->miners_pid[i] != 0))
				{
					kill(net->miners_pid[i], SIGUSR2); // Manda señal 2 para comenzar votación
					printf("		Enviamos señal fresh a index %i id %i\n", i, net->miners_pid[i]);
				}
			}
			/* El ganador también vota */
			net->voting_pool[info.index] = 1;
			printf("El counter estaba a %i\n", net->counter);
			net->counter++;

			sem_post(sem);

			while (1)
			{
				sem_wait(sem);
				if (net->counter == (net->total_miners)) // Espera a que todos hayan votado
					break;
				printf("counter: %i total: %i\n", net->counter, net->total_miners);
				sem_post(sem);
			}
			sem_post(sem);
			n_votes = 0; // A uno porque el ganador vota que si??? pero eso lo hace arriba ay madre se lia todo mal
			sem_wait(sem);
			for (i = 0; i < MAX_MINERS; i++)
			{
				if (net->voting_pool[i] == 1) // Cuenta los votos
					n_votes++;
			}
			sem_post(sem);
			printf("Han salido %i número de votos\n", n_votes);
			if (n_votes / net->total_miners >= 0.5)
			{
				block->is_valid = 1;
				block->solution = info.solution;
				printf("bloque válido\n");
			}
			else
			{
				block->is_valid = 0;
				printf("bloque no válido\n");
			}
			for (i = 0; i < net->total_miners; i++) // Esto habría que rehacerlo para que funcione en los mineros concretos y no los n primeros (con una lista encadenada de vacios??)
			{
				sem_post(sem_update_block); //abre tantos semáforos como mineros queden (esto huele a peligro)
				printf("Lanzamos un sem update\n");
			}
			sem_post(sem);
			printf("Se han hecho %i posts\n", i);
		}
		else
		{
			printf("	A la espera de recibir la señal 2\n");
			sigdelset(&mask_block1, SIGUSR2);
			sigsuspend(&mask_block1);
			printf("	He recibido la señal de votacion\n");
			sem_wait(sem);
			printf("comienza el hashing\n");
			if (simple_hash(block->solution) == info.target)
			{
				printf("Hashing si\n");
				net->voting_pool[info.index] = 1;
			}
			else
			{
				printf("Hashing no\n");
				net->voting_pool[info.index] = 0;
			}
			printf("el counter en el perdedor estaba a %i\n", net->counter);
			net->counter++;
			sem_post(sem);
		}

		sem_wait(sem_update_block);
		sem_wait(sem);
		info.solution = block->solution;
		(net->counter)--; // Cuando llegue a cero significa que todos han guardado el bloque correctamente
		if (block->is_valid == 1)
		{
			if (private_block == NULL)
			{
				printf("Se guarda bloque fresco\n");
				private_block = (Block *)malloc(1 * sizeof(private_block));
				for (i = 0; i < 200; i++)
				{
					private_block->wallets[i] = block->wallets[i];
				}
				private_block->target = block->target;
				private_block->solution = block->solution;
				private_block->id = block->id;
				private_block->is_valid = block->is_valid;
				private_block->next = NULL;
				private_block->prev = NULL;
			}
			else
			{
				while (private_block != NULL)
				{
					aux = private_block;
					private_block = private_block->next;
				}
				private_block = (Block *)malloc(1 * sizeof(private_block));
				for (i = 0; i < MAX_MINERS; i++)
				{
					private_block->wallets[i] = block->wallets[i];
				}
				private_block->target = block->target;
				private_block->solution = block->solution;
				info.target = block->solution; // Cambiamos el target
				private_block->id = block->id;
				private_block->is_valid = block->is_valid;
				private_block->next = NULL;
				private_block->prev = aux;
				aux->next = private_block;
			}
		}
		sem_post(sem);

		/* Inicializar nuevo bloque	*/
		if (info.winner == 1)
		{
			while (1)
			{
				sem_wait(sem);
				if (net->counter == 0) // espera a que sea 0 para inicializar el nuevo bloque (CHAPUZA)
					break;
				sem_post(sem);
			}

			// Aqui falta lo que sea que haya que hacer con las wallets
			if (private_block != NULL)
				block->target = private_block->solution;
			block->solution = -1;
			(block->id)++; //Otra cosa que no explican jeje salu3
			block->is_valid = 0;

			/* Actualizamos net*/
			net->last_winner = getpid();
			for (i = 0; i < MAX_MINERS; i++)
			{
				net->voting_pool[i] = -1;
			}
			sem_post(sem);
		}

		/* Cosas del monitor */
		//Chequear si hay un proceso monitor activo

		printf("Vamos a ver como esta el private:\n");
		print_blocks(private_block, 0);

		sem_wait(sem);
		if (net->monitor_pid != -1) // esto cuando nos cargamos el monitor a la mitad se puede liar
		{

			if (mq_send((cola), (char *)private_block, sizeof(Block), 1) == -1) // gestionar prioridad
			{
				printf("error sending");
			}
		}
		sem_post(sem);
		/* Imprimir bloques */

		n_rounds--;

		/* Sincronización*/
		int counter = 0;
		if (info.winner == 1)
		{
			for (i = 0; i < MAX_MINERS; i++)
			{
				sem_wait(sem);
				if ((net->miners_pid[i] != 0))
				{
					(net->counter)++; // usamos el counter para sincronizar los procesos
					counter++;
				}
				sem_post(sem);
			}
			sem_wait(sem);
			(net->counter)--; // El anfitrión también cuenta
			sem_post(sem);
			if (net->counter == 0)
			{
				for (i = 0; i < counter; i++)
				{ // Envía semáforo de sincronización
					sem_post(sem_sincro);
				}
			}
			sem_wait(sem);
		}
		else
		{
			sem_wait(sem);
			(net->counter)--; // guardamos en una variable
			sem_post(sem);
		}
		sem_wait(sem_sincro);
	}

	/* Destrucción de todo */

	baja(&info,net_shm, net, block_shm, sem, sem_vote, sem_update_block, sem_sincro, cola);
	/*
	sem_wait(sem);
	net->miners_pid[info.index] = -1;
	sem_post(sem);

	fprintf(stderr, "\nSearch completed with result %ld\n", info.solution);
	close(block_shm);
	close(net_shm);
	mq_close(cola);
	//shm_unlink(SHM_NAME_BLOCK);
	//shm_unlink(SHM_NAME_NET);
	sem_close(sem);
	sem_close(sem_vote);
	sem_close(sem_update_block);
	sem_close(sem_sincro);
	//sem_unlink(SEM_NAME);
	//sem_unlink(SEM_NAME);
	//sem_unlink(SEM_NAME);
	//sem_unlink(SEM_NAME);
	exit(EXIT_SUCCESS);
	*/
}
