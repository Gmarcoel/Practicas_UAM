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
#include <unistd.h>

#define MQ_NAME "/mq_monitor"
#define SEM_NAME "/sem_net"
#define SECS 5

static volatile int flag = 0;
static volatile alarma = 0;

/* Manejador de la señal sigint */
void manejador_sigint(int sig)
{
    flag = 1;
    return;
}

void manejador_sigalrm(int sig)
{
    alarma = 1;
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

/* Inicializador de la señal sigalarm */
void sig_alrm(struct sigaction act)
{
    act.sa_handler = manejador_sigalrm;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    if (sigaction(SIGALRM, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    return;
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
            //printf("%d: %d;         \n", j, block->wallets[j]);
        }
        printf("\n\n\n");
    }
    printf("A total of %d blocks were printed\n", i);
}
/*
void print_blocks(Block *plast_block, int num_wallets)
{
	Block *block = NULL;
	int i, j;

	for (i = 0, block = plast_block; block != NULL; block = block->prev, i++)
	{
		printf("Block number: %d; Target: %ld;    Solution: %ld\n", block->id, block->target, block->solution);
		for (j = 0; j < num_wallets; j++)
		{
			printf("%d: %d;         \n", j, block->wallets[j]);
		}
		printf("\n\n\n");
	}
	printf("A total of %d blocks were printed\n", i);
}
*/

void main()
{
    pid_t pid;
    int fd[2], fichero;
    int i, found, prev = 0;
    Block buffer[10];
    Block last, chain[100]; // Que esto sea una cadena de 100 pinta meh
    int nbytes;
    char buf_fichero[200];
    struct sigaction act, act2;
    mqd_t cola;
    Block b;
    int net_shm;
    NetData *net;
    sem_t *sem;

    sig_int(act);
    sig_alrm(act2);

    net_shm = shm_open(SHM_NAME_NET, O_RDWR, 0);
    if (net_shm == -1)
    {
        perror("No miners in network");
        exit(EXIT_FAILURE);
    }
    /* Mapeamos	*/
    if ((net = mmap(NULL, sizeof(Block), PROT_READ | PROT_WRITE, MAP_SHARED, net_shm, 0)) == MAP_FAILED)
    {
        perror("mmap error");
        exit(EXIT_FAILURE);
    }
    /* Abrimos semáforo*/
    if ((sem = sem_open(SEM_NAME, O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    /* Damos de alta el monitor */
    sem_wait(sem);
    if (net->monitor_pid == -1)
    {
        net->monitor_pid = getpid();
    }
    else
    {
        printf("Ya existe monitor\n");
        flag = 1;
    }
    sem_post(sem);

    pipe(fd);
    pid = fork();
    /* Proceso hijo */
    if (pid == 0)
    {
        close(fd[1]);

        do
        {
            alarm(SECS);
            /* Copia bloque enviado por la cola*/
            nbytes = read(fd[0], &last, sizeof(Block));

            if (alarma == 0)
            {
                if (nbytes == -1)
                {
                    printf("read pipe error\n");
                }
                chain[prev].target = last.target;
                chain[prev].solution = last.solution;
                chain[prev].id = last.id;
                chain[prev].is_valid = last.is_valid;
                chain[prev].next = last.next;
                if (prev != 0)
                {
                    chain[prev].prev = &(chain[prev - 1]);
                }
                else
                {
                    chain[prev].prev = NULL;
                }
                prev++;
            }
            else
            {
                alarma = 0;
            }
            /* Imprimir en el archivo */
            //sleep(5);
            print_blocks(&(chain[prev - 1]), MAX_MINERS); // Aqui el numero de wallets a saber que es ???

        } while (nbytes != 0 && flag == 0);

        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    /* Proceso padre */
    close(fd[0]);

    //Estructura atributos cola
    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(b)};

    //Abrimos la cola
    (cola) = mq_open(MQ_NAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &attributes);
    if ((cola) == (mqd_t)-1)
    {
        perror("mqueue");
        return;
    }

    while (flag == 0)
    {
        //Lectura de la cola
        if (mq_receive(cola, (char *)&b, sizeof(b), NULL) == -1)
        {
            perror("Receive");
            return;
        }

        /* Hacer una copia del bloque */
        for (i = 0; i < 200; i++)
        {
            last.wallets[i] = b.wallets[i];
        }
        last.target = b.target;
        last.solution = b.solution;
        last.id = b.id;
        last.is_valid = b.is_valid;
        last.next = b.next;
        last.prev = b.prev;
        /* Comparar copia con los bloques del buffer*/
        for (i = 0, found = 0; i < 10; i++)
        {
            if (buffer[i].id == last.id)
            {
                if (buffer[i].target == last.target && buffer[i].solution == last.solution)
                {
                    printf("Verified block %i with solution %li for target %li\n", buffer[i].id, buffer[i].solution, buffer[i].target);
                }
                else
                {
                    printf("Error in block %i with solution %li for target %li\n", buffer[i].id, buffer[i].solution, buffer[i].target);
                }
                found = 1;
                break;
            }
        }
        /* Bloque no repetido */
        if (found == 0)
        {
            buffer[(prev % 10)].target = last.target;
            buffer[(prev % 10)].solution = last.solution;
            buffer[(prev % 10)].id = last.id;
            buffer[(prev % 10)].is_valid = last.is_valid;
            buffer[(prev % 10)].next = last.next;
            buffer[(prev % 10)].prev = last.prev;
            prev++;
        }

        /* El proceso padre envía por tubería una copia del bloque */
        nbytes = write(fd[1], &last, sizeof(Block));
        if (nbytes == -1)
            fprintf(stderr, "Error in monitor pipe\n");
    }

    sem_wait(sem);
    net->monitor_pid = -1;
    sem_post(sem);
    close(fd[0]);
    sem_close(sem);
    munmap(net, sizeof(net));
    close(net_shm);
    wait(NULL);
    /*Cerramos la cola*/
    mq_close(cola);
}
