CC = gcc
CFLAGS = -Wall -Wextra
aidan_sql: main.o database.o
	$(CC) $(CFLAGS) -o aidan_sql $^
main.o: main.c database.h
	$(CC) $(CFLAGS) -c main.c
database.o: database.c database.h
	$(CC) $(CFLAGS) -c database.c
clean:
	rm -f *.o aidan_sql
