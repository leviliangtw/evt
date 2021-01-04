// predecoder.h
#ifndef __PREDECODER_H_ 
#define __PREDECODER_H_ 
#include "reg.h"

struct preTable
{
    /* data */
    char *routine;
    char op1;   // useless
    char op2;   // useless
    char op3;   // useless
} typedef preTable;

void predecoding(char *, int, void *[], preTable *, char);

#endif  /* __PREDECODER_H_  */