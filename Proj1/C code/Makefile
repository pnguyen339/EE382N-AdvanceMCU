IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR) -g -std=c11

ODIR=obj
LDIR =./lib

LIBS=-lm

_DEPS = MemoryAccess.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = MemoryAccess.o testProgram.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Proj1: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~