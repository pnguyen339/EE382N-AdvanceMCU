CC=gcc
CFLAGS=-g -std=c11
DEPS = MemoryAccess.h
OBJ = MemoryAccess.o testProgram.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

proj1: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
