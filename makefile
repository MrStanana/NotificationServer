CC = gcc
CFLAGS = -g -Wall -iquote$(DIR_INC)
LIBS = -lpthread -lm -libmysqlclient

DIR_INC = ./include
DIR_SRC = ./src

OBJ_SERVER = server.o config.o json.o pipe.o queue.o connection.o control.o user.o module.o
OBJ_CLIENT = client.o

all: server client

server: $(OBJ_SERVER)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

client: $(OBJ_CLIENT)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: $(DIR_SRC)/%.c
	$(CC) -c $< $(CFLAGS) $(LIBS)

clean:
	rm -rf *.o server client
