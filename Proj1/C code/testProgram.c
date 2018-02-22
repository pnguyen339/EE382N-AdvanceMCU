

#include "stdio.h"
#include "stdlib.h"
#include "MemoryAccess.h"

#define LFSR 0x43C00000
#define BRAM_CTRL_0 0x40000000
#define BRAM_CTRL_1 0x40002000
#define GPIO 0x41200000


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


void test1(int loop){
    printf("Starting test 1");

    for(int i =0; i < loop; i++){
        int offset = dm(LFSR + 4);
        int value = dm(LFSR);
        pm(BRAM_CTRL_0+offset, value);
         
        int waitTime = 0;
        exec("/dev/RandomGenerator",&waitTime);
        wait(waitTime);
        if(dm(BRAM_CTRL_0+offset) != value)
            pm(GPIO,1);
        
    }
}

void test2(int loop)
{
    printf("Starting test 2");

    for(int i =0; i < loop; i++){
        int offset = dm(LFSR + 4);
        int value = dm(LFSR);
        pm(BRAM_CTRL_0+offset, value);
         
        int waitTime = 0;
        exec("/dev/RandomGenerator",&waitTime);
        wait(waitTime);
        if(dm(BRAM_CTRL_1+offset) != value)
            pm(GPIO,1);
        
    }
}

void test3(int loop)
{
    printf("Starting test 2");

    for(int i =0; i < loop; i++){
        int offset = dm(LFSR + 4);
        int value = dm(LFSR);
        pm(BRAM_CTRL_1+offset, value);
         
        int waitTime = 0;
        exec("/dev/RandomGenerator",&waitTime);
        wait(waitTime);
        if(dm(BRAM_CTRL_0+offset) != value)
            pm(GPIO,1);
        
    }
}
