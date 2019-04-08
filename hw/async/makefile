all: libWriteToClient.so server.c 
	gcc -o ./server ./server.c -L. -lWriteToClient

libWriteToClient.so: writeToClient.c
	gcc -shared -fPIC ./writeToClient.c -o libWriteToClient.so
