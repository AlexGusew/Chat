all: clean

all: server.o client.o
	g++ server.o client.o -o client

server.o: server.c
	g++ -c server.c

client.o: client.c
	g++ -c client.c
