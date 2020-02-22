CC= gcc
CFLGS= -W -Wall -Werrors
EXEC= pong
BIN=./bin



all = $(EXEC)

$(EXEC): pong.o
	@$(CC) -o $(BIN)/pong pong.o 

pong.o: pong.c pong.h
	$(CC) -o pong.o -c pong.c $(CFLGS)

clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXEC)
