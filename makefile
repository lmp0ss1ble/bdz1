CC = gcc
CFLAGS = -Wall -Wextra

all: client server

client: client.o
	$(CC) client.o -o client -lws2_32

server: server.o
	$(CC) server.o -o server -lws2_32

client.o: client.c client.h
	$(CC) $(CFLAGS) -c client.c

server.o: server.c server.h
	$(CC) $(CFLAGS) -c server.c

clean:
	del *.o client.exe server.exe
