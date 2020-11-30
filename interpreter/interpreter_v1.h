// interpreter_v1.h
#ifndef __INTERPRETER_V1_H_ 
#define __INTERPRETER_V1_H_ 
#include "reg.h"

typedef void (*handle)(reg *);

struct routines{
  handle handles[6];
};

void interpreter_v1(char *, int, reg *);
void HandleHALT(reg *);
void HandleCLRA(reg *);
void HandleINC3A(reg *);
void HandleDECA(reg *);
void HandleSETL(reg *);
void HandleBACK7(reg *);

#endif  /* __INTERPRETER_V1_H_  */