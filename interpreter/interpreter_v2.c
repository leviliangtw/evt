// interpreter_v2.c
#include "interpreter_v2.h"
#include "predecoder.h"

void interpreter_v2(char *buf, int size, reg *myreg){
    static void *ins[] = { &&HALT, &&CLRA, &&INC3A, &&DECA, &&SETL, &&BACK7 };

    myreg->rIP = buf;
    char inst = *(myreg->rIP);
    int opcode = inst;
    goto *ins[*myreg->rIP];

CLRA:
    // printf("opcode 1: set content of register A to 0\n");
    myreg->rIP += 1;
    // operation
    myreg->rA = 0;
    // operation
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    goto *ins[*myreg->rIP];
 
INC3A:
    // printf("opcode 2: increment register A by 3\n");
    myreg->rIP += 1;
    myreg->rA += 3;
    // operation
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    goto *ins[*myreg->rIP];

DECA:
    // printf("opcode 3: decrement register A by 1\n");
    myreg->rIP += 1;
    myreg->rA -=1;
    // operation
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    goto *ins[*myreg->rIP];

SETL:
    // printf("opcode 4: copy value of register A to L\n");
    myreg->rIP += 1;
    myreg->rL = myreg->rA;
    // operation
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    goto *ins[*myreg->rIP];
                
BACK7:
    // printf("opcode 5: decrement L; if value of L is positive, jump back by 7 instructions (i.e. loop body is 6 one-byte instructions and the BACK7 itself). Otherwise fall through to next instruction\n");
    if(myreg->rL <= 0) {
        myreg->rIP += 7;
        // operation
        myreg->rL += 1;
        // operation
    }
    myreg->rIP -= 6;
    // operation
    myreg->rL -= 1;
    // operation
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    goto *ins[*myreg->rIP];

HALT:
    // printf("opcode 0: stop execution\n");
    ;
}