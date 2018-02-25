CC=gcc
CFLAGS=-I, -g, -Wall.
DEPS = MemoryAccess.h
OBJ = MemoryAccess.o testProgram.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)