
#ifndef SOCKETS_H
#define SOCKETS_H


#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int mySocket();
int myBind(int fd, int port);
int myListen(int fd);
int myAccept(int fd);
int mySend(int fd, char * msg);
int myRecv(int fd);

#endif