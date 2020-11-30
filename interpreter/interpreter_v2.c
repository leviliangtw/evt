// interpreter_v1.c
#include "interpreter_v2.h"

void interpreter_goto(char *buf, int size, reg *myreg){
    static void *ins[] = { &&HALT, &&CLRA, &&INC3A, &&DECA, &&SETL, &&BACK7 };
    myreg->rIP = buf;
    char inst = *(myreg->rIP);
    int opcode = inst;

CLRA:
    printf("opcode 1: set content of register A to 0\n");
    myreg->rIP += 1;
    myreg->rA = 0;
    goto *ins[*myreg->rIP];
 
INC3A:
    printf("opcode 2: increment register A by 3\n");
    // printf("    After interpreter, myreg: %d\n", myreg);
    printf("    After interpreter, myreg.rIP: %d\n", *myreg->rIP);
    printf("    After interpreter, myreg.rA: %d\n", myreg->rA);
    printf("    After interpreter, myreg.rL: %d\n", myreg->rL);
    myreg->rIP += 1;
    myreg->rA += 3;
    goto *ins[*myreg->rIP];

DECA:
    printf("opcode 3: decrement register A by 1\n");
    myreg->rIP += 1;
    myreg->rA -=1;
    goto *ins[*myreg->rIP];

SETL:
    printf("opcode 4: copy value of register A to L\n");
    myreg->rIP += 1;
    myreg->rL = myreg->rA;
    goto *ins[*myreg->rIP];
                
BACK7:
    printf("opcode 5: decrement L; if value of L is positive, jump back by 7 instructions (i.e. loop body is 6 one-byte instructions and the BACK7 itself). Otherwise fall through to next instruction\n");
    // printf("    After interpreter, myreg: %d\n", myreg);
    printf("    After interpreter, myreg.rIP: %d\n", *myreg->rIP);
    printf("    After interpreter, myreg.rA: %d\n", myreg->rA);
    printf("    After interpreter, myreg.rL: %d\n", myreg->rL);
    if(myreg->rL <= 0) {
        myreg->rIP += 8;
        myreg->rL += 1;
    }
    myreg->rIP -= 7;
    myreg->rL -= 1;
    goto *ins[*myreg->rIP];

HALT:
    printf("opcode 0: stop execution\n");
}