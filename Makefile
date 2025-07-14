CC = clang
CFLAGS = -std=c11  -w



build: main
	$(CC) $(CFLAGS) -o database main.c database.c fileHandler.c


main: main.c database.c
	$(CC) $(CFLAGS) -o database database.c fileHandler.c main.c

clean:
	rm -f database *.o *.json