// bigen_v1.h
#ifndef __BIGEN_H_ 
#define __BIGEN_H_
#include "../interpreter/reg.h"

unsigned char *binary_generator_v1(reg *, int);
unsigned char *binary_generator_v2(unsigned char *, int, unsigned char **);
void BACK7_chain(unsigned char *, unsigned char *, int);

struct bi_translations {
    char * codes;
    int len; 
} typedef bi_translations;

#endif  /* __BIGEN_H_ */