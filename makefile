CC=gcc
CFLAGS=-I.
DEPS = threads.h
OBJ = main.o threads.o
EXEC = main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(EXEC) *.o *~ core
