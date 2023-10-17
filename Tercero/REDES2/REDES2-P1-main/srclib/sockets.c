#include "sockets.h"
#define SA struct sockaddr

int mySocket(){
    //socket(AF_INET, SOCK_STREAM, 0);
    socket(AF_INET, SOCK_STREAM, 0);
}


/**
* @arg fd return the socket()
*/
int myBind(int fd, int port){
    struct sockaddr_in servaddr;
    if ( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0 )
        return -1;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    return bind(fd, (SA*)&servaddr, sizeof(servaddr));
}



/**
    Argumento cola maxima de conexiones pendientes
*/
int myListen(int fd){
    return listen(fd, 200);
}

int myAccept(int fd){
    struct sockaddr cli;
    int len=sizeof(cli);
    return accept(fd, (struct sockaddr *)&cli, (socklen_t*)&len);
}

int mySend(int fd, char * msg){
    return send(fd, msg, sizeof(msg), 0);
}

int myRecv(int fd){
    char buff[800];
    int ret=0;
    ret=recv(fd, buff, sizeof(buff), 0);
    printf("%s\n", buff);
    return ret;
}