CC = gcc
CFLAGS=-Wall -g -I --debug[v]
DEPS = first.h
OBJ = first.o first.o

%.o: %.c $(DEPS)
	$(CC) -c -o $< $(CFLAGS)

hellomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

all: first.c second.c
	gcc -g -Wall -o First first.c && gcc -g -Wall -o Second second.c

clean:
	rm -f First Second
