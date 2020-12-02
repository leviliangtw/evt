// interpreter_v1.c
#include "interpreter_v1.h"

void interpreter_v1(char *buf, int size, reg *myreg){
    myreg->rIP = buf;
    char inst = *(myreg->rIP);
    int opcode = inst;

    if (inst){
        switch(opcode) {
            case 1:
                HandleCLRA(myreg);
                break;
            case 2:
                HandleINC3A(myreg);
                break;
            case 3:
                HandleDECA(myreg);
                break;
            case 4:
                HandleSETL(myreg);
                break;
            case 5:
                HandleBACK7(myreg);
                break;
            default:
                break;
        }
    }
}

void HandleHALT(reg *myreg){
    // printf("opcode 0: stop execution\n");
    // exit(0);
}

void HandleCLRA(reg *myreg){
    // printf("opcode 1: set content of register A to 0\n");
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rA = 0;
    rts.handles[*myreg->rIP](myreg);
}

void HandleINC3A(reg *myreg){
    // printf("opcode 2: increment register A by 3\n");
    // printf("    After interpreter, myreg: %d\n", myreg);
    // printf("    After interpreter, myreg.rIP: %d\n", *myreg->rIP);
    // printf("    After interpreter, myreg.rA: %d\n", myreg->rA);
    // printf("    After interpreter, myreg.rL: %d\n", myreg->rL);
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rA += 3;
        // printf("    After interpreter, myreg->rIP: %d\n", *myreg->rIP);
    rts.handles[*myreg->rIP](myreg);
}

void HandleDECA(reg *myreg){
    // printf("opcode 3: decrement register A by 1\n");
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rA -=1;
    rts.handles[*myreg->rIP](myreg);
}

void HandleSETL(reg *myreg){
    // printf("opcode 4: copy value of register A to L\n");
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rL = myreg->rA;
    rts.handles[*myreg->rIP](myreg);
}

void HandleBACK7(reg *myreg){
    // printf("opcode 5: decrement L; if value of L is positive, jump back by 7instructions (i.e. loop body is6one-byte instructions and the BACK7itself). Otherwise fall through to next instruction\n");
    // printf("    After interpreter, myreg: %d\n", myreg);
    // printf("    After interpreter, myreg.rIP: %d\n", *myreg->rIP);
    // printf("    After interpreter, myreg.rA: %d\n", myreg->rA);
    // printf("    After interpreter, myreg.rL: %d\n", myreg->rL);
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    if(myreg->rL <= 0) {
        myreg->rIP += 8;
        myreg->rL += 1;
    }
    myreg->rIP -= 7;
    myreg->rL -= 1;
    rts.handles[*myreg->rIP](myreg);
}