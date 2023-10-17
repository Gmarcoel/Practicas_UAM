#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "sockets.h"
#include "pool_thread.h"
#include <pthread.h>
#include "confuse.h"
#include "picohttpparser.h"
#include "http.h"
#include <signal.h>
#define SA struct sockaddr

void han(int sg) {}

// Driver function
int main()
{

    static char *root = NULL;
    static long int port = 0;
    static char *signature = NULL;
    static long int nthreads = 0;
    int sockfd, connfd, len, pid;
    struct sockaddr_in servaddr, cli;
    cfg_t *cfg;
    struct sigaction sg;
    sigset_t new_mask, old_mask;
    //pool_thread *pt = NULL;
    pool_thread pt;

    cfg_opt_t opts[] = {
        CFG_SIMPLE_STR("root", &root),
        CFG_SIMPLE_INT("port", &port),
        CFG_SIMPLE_STR("signature", &signature),
        CFG_SIMPLE_INT("nthreads", &nthreads),
        CFG_END()};

    cfg = cfg_init(opts, 0);
    cfg_parse(cfg, "./server.conf");
    cfg_free(cfg);

    sg.sa_handler = han;
    sigemptyset(&(sg.sa_mask));
    sg.sa_flags = 0;

    sigemptyset(&new_mask);                             // inicializo un set de señales vacío
    sigaddset(&new_mask, SIGTERM);                      // añado al set una señal
    pthread_sigmask(SIG_SETMASK, &new_mask, &old_mask); // bloqueo la señal para que los hilos-cliente la ignoren
    sigaction(SIGUSR1, &sg, NULL);                      // hace falta un manejador vacío para desbloquear el hilo-principal al recibir la señal
    sigaction(SIGTERM, &sg, NULL);                      // hace falta un manejador vacío para desbloquear el hilo-principal al recibir la señal
    signal(SIGPIPE, SIG_IGN);

    //pt = pool_th_ini(MAX_THREADS);
    pool_th_ini(&pt, nthreads);

    // socket create and verification
    sockfd = mySocket();

    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Binding newly created socket to given IP and verification
        if (myBind(sockfd, port) != 0)
        {
            printf("socket bind failed...\n");
            exit(0);
        }
        else
            printf("Socket successfully binded..\n");

        if ((myListen(sockfd)) != 0)
        {
            printf("Listen failed...\n");
            exit(0);
        }
        else
            printf("Server listening..\n");



        // Now server is ready to listen and verification
        
        len = sizeof(cli);
        // Wait for a signal

        // Accept the data packet from client and verification
    while (1)
    {
        
        
        printf("Waiting for connection...\n");
        connfd = myAccept(sockfd);
        if (connfd < 0)
        {
            printf("server accept failed...\n");
            continue;
        }
        else
        {
            printf("server accept the client...\n");
            poolSubmit(&pt, process, &connfd, signature);
        }
    }
    // sigsuspend(&old_mask);

    // Fork the process for multi threading

    // Function for chatting between client and server
    // func(connfd);

    // After chatting close the socket
    pool_th_destroy(pt);
    free(signature);
    close(sockfd);
    return 0;
}