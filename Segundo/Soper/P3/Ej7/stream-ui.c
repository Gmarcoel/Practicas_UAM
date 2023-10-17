#include <stdio.h>
#include <stdlib.h>

#include <fcnl.h>
#include <mqueue.h>
#include <sys/stat.h>

#include <sys/mman.h>
#include <unistd.h>

typedef struct {
	char buffer[5];
	int post_pos=0, get_pos=0;
} Shm;
/*Inicialización de funciones privadas*/
pid_t crear_hijo();


int main(void) {
	int fd;
	Shm * shm_struct= NULL;
	pid_t stream-server stream-client;
	
	/*Inicializacion de memoria compartida*/
	if ((fd = shm_open(SHM_NAME,O_RDWR | O_CREAT | O_EXECL, S_IRUSR | S_IWUSR))== -1)	{
		perror("shm_open");
		exit(EXIT_FAILURE);
	}
	/*Inicialización de hijos*/
	stream_server = crear_hijo();
	if(stream_server == 0 ) {
		
	}

	stream_client = crear_hijo();
	if(stream_client == 0 ) {

	}


}
void ejecutar(char * name) {
	if (execlp(stream_server,name)) {
	{
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	return;
}
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

