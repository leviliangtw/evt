// interpreter_v1.h
#ifndef __INTERPRETER_H_ 
#define __INTERPRETER_H_ 
#include "reg.h"

typedef void (*handle)(reg *);

struct routines{
  handle handles[6];
};

void HandleHALT(reg *);
void HandleCLRA(reg *);
void HandleINC3A(reg *);
void HandleDECA(reg *);
void HandleSETL(reg *);
void HandleBACK7(reg *);
void interpreter_v1(char *, int, reg *);
void interpreter_v2(char *, int, reg *);
void interpreter_v3(char *, int, reg *);
void interpreter_v4(char *, int, reg *);

#endif  /* __INTERPRETER_H_  */