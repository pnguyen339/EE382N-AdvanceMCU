#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>


uint32_t dm(uint16_t target_addr);
int pm(uint16_t target_addr, int value);

#endif