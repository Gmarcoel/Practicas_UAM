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


// Function designed for chat between client and server.
//int process(int * fd, char *name);
int process(int *fd, char *name);
