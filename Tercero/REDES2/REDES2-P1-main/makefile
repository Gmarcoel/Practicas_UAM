IDIR =include
CC=gcc
CFLAGS=-Isrclib -Iinclude -Iobj -g

ODIR=obj
LDIR =srclib

LIBS=-lm -lpthread -lconfuse

_DEPS = pool_thread.h sockets.h picohttpparser.h http.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = pool_thread.o sockets.o server.o client.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SRC = pool_thread.c sockets.c server.c client.c
SRC = $(patsubst %,$(LDIR)/%,$(_SRC))

all: clean server

obj/pool_thread.o: $(LDIR)/pool_thread.c $(IDIR)/pool_thread.h 
	$(CC) $(CFLAGS) -c $(LDIR)/pool_thread.c $(IDIR)/pool_thread.h 
	mv pool_thread.o obj/pool_thread.o

obj/sockets.o: $(LDIR)/sockets.c $(IDIR)/sockets.h 
	$(CC) $(CFLAGS) -c $(LDIR)/sockets.c $(IDIR)/sockets.h 
	mv sockets.o obj/sockets.o

obj/server.o: src/server.c
	$(CC) $(CFLAGS) -c src/server.c
	mv server.o obj/server.o

obj/client.o: $(LDIR)/client.c
	$(CC) $(CFLAGS) -c $(LDIR)/client.c 
	mv client.o obj/client.o

obj/picohttpparser.o: $(LDIR)/picohttpparser.c $(IDIR)/picohttpparser.h 
	$(CC) $(CFLAGS) -c $(LDIR)/picohttpparser.c $(IDIR)/picohttpparser.h 
	mv picohttpparser.o obj/picohttpparser.o

obj/http.o: $(LDIR)/http.c $(IDIR)/http.h 
	$(CC) $(CFLAGS) -c $(LDIR)/http.c $(IDIR)/http.h 
	mv http.o obj/http.o


server: obj/server.o obj/pool_thread.o obj/sockets.o obj/picohttpparser.o obj/http.o
	ar rcs libsockets.a obj/sockets.o
	mv libsockets.a lib/libsockets.a
	ar rcs libpicohttpparser.a obj/picohttpparser.o
	mv libpicohttpparser.a lib/libpicohttpparser.a
	ar rcs libpool.a obj/pool_thread.o
	mv libpool.a lib/libpool.a
	$(CC) obj/server.o obj/http.o $(LIBS) -L./lib -lsockets -lpicohttpparser -lpool -o server $(IDIR)/sockets.h $(IDIR)/pool_thread.h $(IDIR)/picohttpparser.h 



.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f lib/*.a
