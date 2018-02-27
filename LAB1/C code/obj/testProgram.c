
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "MemoryAccess.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define LFSR 0x43C00000
#define BRAM_CTRL_0 0x40000000
#define BRAM_CTRL_1 0x40002000
#define GPIO 0x41200008


void test1(uint32_t loop)
{
    uint32_t offset, value, readval;
    //reset LFSRs
    pm(LFSR, 0);
    pm(LFSR+4, 0);

	pm(GPIO, 0);
    printf("Starting test 1\n");
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd == -1)
	{
		printf("Unable to open /dev/urandom.\n");
		return;
	}
    uint32_t random = 0;
     
    for(int i =0; i < loop; i++){
        offset = dm(LFSR + 4) << 2;
        value = dm(LFSR);
	    printf("address : %x value : %x\n", BRAM_CTRL_0 + offset, value);
        pm(BRAM_CTRL_0 + offset, value);
    }

    read(fd, &random,4);	
 	random = random & 0xf;
    close(fd);
    //sleep for some time
    sleep(random);
    //reset LFSRs
    pm(LFSR, 0);
    pm(LFSR+4, 0);

    for(int i =0; i < loop; i++){
        offset = dm(LFSR + 4) << 2;
        value = dm(LFSR);
    	readval = dm(BRAM_CTRL_0 + offset);
        printf("address : %x value : %x\n", BRAM_CTRL_0 + offset, value);
    	printf("read value : %x\n", readval);
        if(readval != value)
        {
            pm(GPIO,1);
            return;
        }
    }
    pm(GPIO,2);
}

void test2(int loop)
{
    uint32_t offset, value, readval;
    //reset LFSRs
    pm(LFSR, 0);
    pm(LFSR+4, 0);

    pm(GPIO, 0);
	printf("Starting test 2");
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd == -1)
	{
		printf("Unable to open /dev/urandom.\n");
		return;
	}

	uint32_t random = 0;
     
    for(int i =0; i < loop; i++){
        offset = dm(LFSR + 4) << 2;
        value = dm(LFSR);
        printf("address : %x value : %x\n", BRAM_CTRL_0 + offset, value);
        pm(BRAM_CTRL_0 + offset, value);
        

    }
    read(fd, &random,4);    
    random = random & 0xf;
    close(fd);
    //sleep for some time
    sleep(random);
    //reset LFSRs
    pm(LFSR, 0);
    pm(LFSR+4, 0);

    for(int i =0; i < loop; i++){
        offset = dm(LFSR + 4) << 2;
        value = dm(LFSR);
        readval = dm(BRAM_CTRL_1 + offset);
        printf("address : %x value : %x\n", BRAM_CTRL_1 + offset, value);
        printf("read value : %x\n", readval);
        if(readval != value)
        {
            pm(GPIO,1);
            return;
        }
    }
    pm(GPIO,2);
}

void test3(int loop)
{
    uint32_t offset, value, readval;
    //reset LFSRs
    pm(LFSR, 0);
    pm(LFSR+4, 0);

    printf("Starting test 2");
	pm(GPIO, 0);
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd == -1)
	{
		printf("Unable to open /dev/urandom.\n");
		return;
	}

    uint32_t random = 0;
     
    for(int i =0; i < loop; i++){
        offset = dm(LFSR + 4) << 2;
        value = dm(LFSR);
        printf("address : %x value : %x\n", BRAM_CTRL_1 + offset, value);
        pm(BRAM_CTRL_1 + offset, value);
        

    }
    read(fd, &random,4);    
    random = random & 0xf;
    close(fd);
    //sleep for some time
    sleep(random);
    //reset LFSRs
    pm(LFSR, 0);
    pm(LFSR+4, 0);

    for(int i =0; i < loop; i++){
        offset = dm(LFSR + 4) << 2;
        value = dm(LFSR);
        readval = dm(BRAM_CTRL_0 + offset);
        printf("address : %x value : %x\n", BRAM_CTRL_0 + offset, value);
        printf("read value : %x\n", readval);
        if(readval != value)
        {
            pm(GPIO,1);
            return;
        }
    }
    pm(GPIO,2);
}


int main(int argc, char * argv[]) {

    if(argc != 3){
        printf("USAGE: (option) (n)\n");
		printf("Option:\n");
		printf("	1: run test1 for n count\n");
		printf("	2: run test2 for n count\n");
		printf("	3: run test3 for n count\n");
		printf("	4: reset the the LSFR either for (0)32 bit, (1)10 bit, or (2)both\n");
		printf("	5: output to GPIO n which gpios\n");
		//printf("	6: reset the GPIO to 0\n");
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
			case 4: 
				if(loop == 2){
					pm(LFSR, 0);
					pm(LFSR+4, 0);
				}
				else if(loop == 1){
					pm(LFSR+4, 0);
				}
				else if(LFSR == 0){
					pm(LFSR,0);
				}
				break;
	   case 5: pm(GPIO, loop);break;
	   //case 6: pm(GPIO, 0);break;
           
       }
    }


}
