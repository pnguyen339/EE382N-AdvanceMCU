
 #include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "MemoryAccess.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define LFSR 0x43C00000
#define BRAM_CTRL_0 0x40000000
#define BRAM_CTRL_1 0x40002000
#define GPIO 0x41200000


void test1(int loop){
    printf("Starting test 1");
    int fd = open("/dev/random", O_RDONLY);
    if(fd == -1)
	{
		printf("Unable to open /dev/random.\n");
		return;
	}

    volatile unsigned int *addr = (unsigned int *)mmap(NULL, 0, PROT_READ, MAP_SHARED, fd, 0);
	



    for(int i =0; i < loop; i++){
        int offset = dm(LFSR + 4);
        int value = dm(LFSR);
        pm(BRAM_CTRL_0+offset, value);
         
        int waitTime = 0;
        //exec("/dev/RandomGenerator",&waitTime);
        sleep(*addr);
        if(dm(BRAM_CTRL_0+offset) != value)
            pm(GPIO,1);
        
    }
    close(fd);
}

void test2(int loop)
{
    printf("Starting test 2");
    int fd = open("/dev/random", O_RDONLY);
    if(fd == -1)
	{
		printf("Unable to open /dev/random.\n");
		return;
	}

    volatile unsigned int *addr = (unsigned int *)mmap(NULL, 0, PROT_READ, MAP_SHARED, fd, 0);

    
    for(int i =0; i < loop; i++){
        int offset = dm(LFSR + 4);
        int value = dm(LFSR);
        pm(BRAM_CTRL_0+offset, value);
         
        int waitTime = 0;
        sleep(*addr);
        if(dm(BRAM_CTRL_1+offset) != value)
            pm(GPIO,1);
        
    }
    close(fd);
}

void test3(int loop)
{
    printf("Starting test 2");

    int fd = open("/dev/random", O_RDONLY);
    if(fd == -1)
	{
		printf("Unable to open /dev/random.\n");
		return;
	}

   
    volatile unsigned int *addr = (unsigned int *)mmap(NULL, 0, PROT_READ, MAP_SHARED, fd, 0);

    for(int i =0; i < loop; i++){
        int offset = dm(LFSR + 4);
        int value = dm(LFSR);
        pm(BRAM_CTRL_1+offset, value);
         
        int waitTime = 0;
        sleep(*addr);
        if(dm(BRAM_CTRL_0+offset) != value)
            pm(GPIO,1);
        
    }
    close(fd);
}


int main(int argc, char * argv[]) {

    if(argc != 3){
        printf("USAGE: (test) (how many)\n");
    }
    else {
       unsigned int target = strtoul(argv[1], 0, 0);
       unsigned int loop = strtoul(argv[2], 0, 0);
       switch(target){
            case 1: test1(loop);
                    break;
            case 2: test2(loop);
                    break;
            case 3: test3(loop);
                    break;
           
       }
    }


}
