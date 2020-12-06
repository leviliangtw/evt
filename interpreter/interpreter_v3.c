// interpreter_v3.c
#include "interpreter_v3.h"
#include "predecoder.h"

void interpreter_v3(char *buf, int size, reg *myreg){
    char *routine; 
    int TPC = 0;    // for myPT
    int SPC = 0;    // for buf
    static void *ins[] = { &&HALT, &&CLRA, &&INC3A, &&DECA, &&SETL, &&BACK7 };
    // printf("&&HALT: %p\n", &&HALT);
    // printf("&&CLRA: %p\n", &&CLRA);
    // printf("&&INC3A: %p\n", &&INC3A);
    // printf("&&DECA: %p\n", &&DECA);
    // printf("&&SETL: %p\n", &&SETL);
    // printf("&&BACK7: %p\n", &&BACK7);
    struct preTable *myPT = (struct preTable *) malloc(size * sizeof(struct preTable));
    predecoding(buf, size, ins, myPT, 0);
    char inst = *(buf);
    myreg->rIP = buf;
    // int opcode1 = myPT->op1;
    // int opcode2 = myPT->op2;
    // int opcode3 = myPT->op3;
    routine = myPT[TPC].routine;
    goto *routine;

CLRA:
    // printf("opcode 1: set content of register A to 0\n");
    TPC += 1;
    SPC += 1;
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
    routine = myPT[TPC].routine;
    goto *routine;
 
INC3A:
    // printf("opcode 2: increment register A by 3\n");
    TPC += 1;
    SPC += 1;
    myreg->rIP += 1;
    // operation
    myreg->rA += 3;
    // operation
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    routine = myPT[TPC].routine;
    goto *routine;

DECA:
    // printf("opcode 3: decrement register A by 1\n");
    TPC += 1;
    SPC += 1;
    myreg->rIP += 1;
    // operation
    myreg->rA -=1;
    // operation
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    routine = myPT[TPC].routine;
    goto *routine;

SETL:
    // printf("opcode 4: copy value of register A to L\n");
    TPC += 1;
    SPC += 1;
    myreg->rIP += 1;
    // operation
    myreg->rL = myreg->rA;
    // printf("    myreg address: %p\n", myreg);
    // printf("    myreg.rIP address: %p\n", myreg->rIP);
    // printf("    myreg.rIP's target value: %d\n", *myreg->rIP);
    // printf("    myreg.rA: %d\n", myreg->rA);
    // printf("    myreg.rL: %d\n", myreg->rL);
    // printf("    TPC: %d\n", TPC);
    // printf("    SPC: %d\n", SPC);
    routine = myPT[TPC].routine;
    goto *routine;
                
BACK7:
    // printf("opcode 5: decrement L; if value of L is positive, jump back by 7 instructions (i.e. loop body is 6 one-byte instructions and the BACK7 itself). Otherwise fall through to next instruction\n");
    if(myreg->rL <= 0) {
        TPC += 7;
        SPC += 7;
        myreg->rIP += 7;
        // operation
        myreg->rL += 1;
        // operation
    }
    TPC -= 6;
    SPC -= 6;
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
    routine = myPT[TPC].routine;
    goto *routine;

HALT:
    // printf("opcode 0: stop execution\n");
    ;
    free(myPT);
}