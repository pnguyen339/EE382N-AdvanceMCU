

KDIR= /usr/src/linux-3.10.17.1
LIBPATH=$(KDIR)/lib
INCPATH=$(KDIR)/include

CC := arm-linux-gnueabihf-gcc 

PWD		:= $(shell pwd)
CFLAGS=  -I$(INCPATH) -L$(LIBPATH)

//STRIP=$(PROC)-$(TYPE)-strip

pm:
	$(CC) $(CFLAGS)  pm.c  -o $@

clean:
	rm pm

