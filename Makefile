CC= gcc
CFLGS= -W -Wall
EXEC= app
BIN=./bin
OBJ=./obj


all = $(EXEC)

$(EXEC): $(OBJ)/*.o
	@$(CC) -o $(BIN)/$(EXEC) $(OBJ)/*.o 

$(OBJ)/*.o: *.c *.h
	$(CC) -o $(OBJ)/obj.o -c *.c $(CFLGS)

clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXEC)
