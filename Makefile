CC= gcc
CFLGS= -W -Wall -Werror
EXEC= pong
BIN=./bin
OBJ=./obj


all = $(EXEC)

$(EXEC): $(OBJ)/pong.o
	@$(CC) -o $(BIN)/pong $(OBJ)/pong.o 

$(OBJ)/pong.o: pong.c pong.h
	$(CC) -o $(OBJ)/pong.o -c pong.c $(CFLGS)

clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXEC)
