// reg.h

#ifndef __REG_H_ 
#define __REG_H_
#include <stdio.h>
#include <stdlib.h>

struct reg
{
    /* data */
    unsigned char * rIP;
    int32_t rA;
    int32_t rL;
} typedef reg;

#endif  /* __REG_H_ */