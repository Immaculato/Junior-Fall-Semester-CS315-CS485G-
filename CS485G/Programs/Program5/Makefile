CFLAGS = -Wall 
CPPFLAGS = -Wall -g

all: server mcput mcget mcdel mclist

csapp.h:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/include/csapp.h

csapp.c:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/src/csapp.c

csapp.o: csapp.h csapp.c

server: server.c csapp.o 
	gcc $(CPPFLAGS) server.c csapp.o -lpthread -o server

mcput: mcput.c csapp.o 
	gcc $(CPPFLAGS) mcput.c csapp.o -lpthread -o mcput

mcget: mcget.c csapp.o
	gcc $(CPPFLAGS) mcget.c csapp.o -lpthread -o mcget

mcdel: mcdel.c csapp.o
	gcc $(CPPFLAGS) mcdel.c csapp.o -lpthread -o mcdel

mclist: mclist.c csapp.o
	gcc $(CPPFLAGS) mclist.c csapp.o -lpthread -o mclist

.PHONY: clean
clean:
	/bin/rm -rf csapp.h csapp.c *.o server mcput mcget mcdel mclist
