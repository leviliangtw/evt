// bigen_v1.h
#ifndef __BIGEN_V1_H_ 
#define __BIGEN_V1_H_
#include "../interpreter/reg.h"

unsigned char *binary_generator_v1(reg *, int);

struct bi_translations {
    char * codes;
    int len; 
} typedef bi_translations;

#endif  /* __BIGEN_V1_H_ */