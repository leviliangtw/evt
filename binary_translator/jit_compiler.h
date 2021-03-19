// jit_compiler.h
#ifndef __JIT_COMPILER_H_ 
#define __JIT_COMPILER_H_
#include "reg.h"

struct code_cache {
    unsigned char *tag;
    int valid; 
    unsigned char *bi_code;
}   typedef code_cache;

struct translation_table {
    unsigned char *SPC;
    unsigned char *TPC;
}   typedef translation_table;

void jit_v0(char *, int, reg *);
void jit_v1(char *, int, reg *);
void jit_v2(char *, int, reg *);
void jit_v3(char *, int, reg *);
void jit_v4(char *, int, reg *);

#endif  /* __JIT_COMPILER_H_ */