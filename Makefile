CC= gcc
CFLGS= -W -Wall
EXEC= app
BIN=./bin
OBJ=./obj
SYSLIBS= -lncurses

all = $(EXEC)

$(EXEC): $(OBJ)/pong.o $(OBJ)/ponglib.o
	@$(CC) -o $(BIN)/$(EXEC) $(OBJ)/pong.o $(OBJ)/ponglib.o $(SYSLIBS)

$(OBJ)/ponglib.o: ponglib.c 
	$(CC) -o $(OBJ)/ponglib.o -c ponglib.c $(CFLGS) 

$(OBJ)/pong.o: pong.c ponglib.c
	$(CC) -o $(OBJ)/pong.o -c pong.c $(CFLGS)

clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXEC)
