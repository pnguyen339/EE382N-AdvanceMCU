

KDIR= /usr/src/linux-3.10.17.1
LIBPATH=$(KDIR)/lib
INCPATH=$(KDIR)/include

CC := arm-linux-gnueabihf-gcc 

//obj-m	:= mx21_gpio.o

//KDIR	:= /home/mcdermot/yocto_kernel/

PWD		:= $(shell pwd)
CFLAGS=  -I$(INCPATH) -L$(LIBPATH)

//STRIP=$(PROC)-$(TYPE)-strip

smb:
	$(CC) $(CFLAGS)  smb.c  -o $@

clean:
	rm smb
