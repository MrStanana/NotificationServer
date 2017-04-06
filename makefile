CC = gcc
#CPPFLAGS =
CFLAGS = -Wall -iquote$(DIR_INC) #-g
LIBS = -lpthread -lm -lmysqlclient
#sudo apt-get install libmysqlclient-dev

DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_EXE = ./bin
#DIR_LIB = ./lib

_OBJ_SERVER = server.o config.o json.o database.o connection.o control.o user.o module.o
OBJ_SERVER = $(patsubst %, $(DIR_OBJ)/%, $(_OBJ_SERVER))
_OBJ_CLIENT = client.o
OBJ_CLIENT = $(patsubst %, $(DIR_OBJ)/%, $(_OBJ_CLIENT))

.PHONY: folders clean

all: folders $(DIR_EXE)/server $(DIR_EXE)/client

$(DIR_EXE)/server: $(OBJ_SERVER)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(DIR_EXE)/client: $(OBJ_CLIENT)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

folders:
	mkdir -p $(DIR_OBJ)
	mkdir -p $(DIR_EXE)

clean:
	rm -rf $(DIR_OBJ) $(DIR_EXE)
