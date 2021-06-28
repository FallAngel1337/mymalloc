CC=gcc
CFLAGS=-g -Wall

all:
	$(CC) $(CFLAGS) -c -o myalloc.o myalloc.c
	$(CC) $(CFLAGS) -o mymalloc mymalloc.c myalloc.o

clean:
	$(RM) *.o mymaalloc