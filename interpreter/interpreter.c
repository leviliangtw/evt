// interpreter_v1.c
#include "interpreter.h"
#include "predecoder.h"

void HandleHALT(reg *myreg){
    // opcode 0: stop execution
    // exit(0);
}

void HandleCLRA(reg *myreg){
    // opcode 1: set content of register A to 0
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rA = 0;
}

void HandleINC3A(reg *myreg){
    // opcode 2: increment register A by 3
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rA += 3;
}

void HandleDECA(reg *myreg){
    // opcode 3: decrement register A by 1
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rA -=1;
}

void HandleSETL(reg *myreg){
    // opcode 4: copy value of register A to L
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    myreg->rIP += 1;
    myreg->rL = myreg->rA;
}

void HandleBACK7(reg *myreg){
    // opcode 5: decrement L; if value of L is positive, jump back by 7 instructions 
    // i.e. loop body is 6 one-byte instructions and the BACK7 itself
    struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};
    if(myreg->rL <= 0) {
        myreg->rIP += 7;
        myreg->rL += 1;
    }
    myreg->rIP -= 6;
    myreg->rL -= 1;
}

void interpreter_v1(char *buf, int size, reg *myreg){
    myreg->rIP = buf;
    char inst = *(myreg->rIP);
    int opcode = inst;

    while (inst){
        switch(opcode) {
            case 1: HandleCLRA(myreg); break;
            case 2: HandleINC3A(myreg); break;
            case 3: HandleDECA(myreg); break;
            case 4: HandleSETL(myreg); break;
            case 5: HandleBACK7(myreg); break;
            default: break;
        }
        inst = *(myreg->rIP);
        opcode = inst;
    }
}

void interpreter_v2(char *buf, int size, reg *myreg){
    // address array of each label (computed goto)
    static void *ins[] = { &&HALT, &&CLRA, &&INC3A, &&DECA, &&SETL, &&BACK7 };

    myreg->rIP = buf;
    char inst = *(myreg->rIP);  // useless, just wanna remind myself waht the real structure should be
    int opcode = inst;          // useless, just wanna remind myself waht the real structure should be
    goto *ins[*myreg->rIP];

CLRA:
    // opcode 1: set content of register A to 0
    myreg->rIP += 1; myreg->rA = 0;
    goto *ins[*myreg->rIP];
INC3A:
    // opcode 2: increment register A by 3
    myreg->rIP += 1; myreg->rA += 3;
    goto *ins[*myreg->rIP];
DECA:
    // opcode 3: decrement register A by 1
    myreg->rIP += 1; myreg->rA -=1;
    goto *ins[*myreg->rIP];
SETL:
    // opcode 4: copy value of register A to L
    myreg->rIP += 1; myreg->rL = myreg->rA;
    goto *ins[*myreg->rIP];     
BACK7:
    // opcode 5: decrement L; if value of L is positive, jump back by 7 instructions 
    // i.e. loop body is 6 one-byte instructions and the BACK7 itself
    if(myreg->rL <= 0) {
        myreg->rIP += 7; myreg->rL += 1;
    }
    myreg->rIP -= 6; myreg->rL -= 1;
    goto *ins[*myreg->rIP];
HALT:
    // opcode 0: stop execution
    ;
}

void interpreter_v3(char *buf, int size, reg *myreg){
    char *routine; 
    static void *ins[] = { &&HALT, &&CLRA, &&INC3A, &&DECA, &&SETL, &&BACK7 };

    struct preTable *myPT = (struct preTable *) malloc(size * sizeof(struct preTable));
    predecoding(buf, size, ins, myPT, 0);

    myreg->rIP = buf;   // Source PC (virtual machine) for buf
    int TPC = 0;        // Target PC (host machine) for myPT
    char inst = *(myreg->rIP);
    // int opcode1 = myPT->op1;
    // int opcode2 = myPT->op2;
    // int opcode3 = myPT->op3;
    routine = myPT[TPC].routine;
    goto *routine;

CLRA:
    // opcode 1: set content of register A to 0
    myreg->rIP += 1; myreg->rA = 0;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;
INC3A:
    // opcode 2: increment register A by 3
    myreg->rIP += 1; myreg->rA += 3;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;
DECA:
    // opcode 3: decrement register A by 1
    myreg->rIP += 1; myreg->rA -=1;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;
SETL:
    // opcode 4: copy value of register A to L
    myreg->rIP += 1; myreg->rL = myreg->rA;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;       
BACK7:
    // opcode 5: decrement L; if value of L is positive, jump back by 7 instructions 
    // i.e. loop body is 6 one-byte instructions and the BACK7 itself
    if(myreg->rL <= 0) {
        myreg->rIP += 7; myreg->rL += 1;
        TPC += 7;
    }
    myreg->rIP -= 6; myreg->rL -= 1;
    TPC -= 6; routine = myPT[TPC].routine;
    goto *routine;
HALT:
    // opcode 0: stop execution
    free(myPT);
}

void interpreter_v4(char *buf, int size, reg *myreg){
    char *routine; 
    static void *ins[] = { &&HALT, &&CLRA, &&INC3A, &&DECA, &&SETL, &&BACK7, 
                            &&INC3A_CLRA, &&INC3A_DECA, &&INC3A_SETL, &&INC3A_BACK7 };

    struct preTable *myPT = (struct preTable *) malloc(size * sizeof(struct preTable));
    predecoding(buf, size, ins, myPT, 1);

    myreg->rIP = buf;   // Source PC (virtual machine) for buf
    int TPC = 0;        // Target PC (host machine) for myPT
    char inst = *(myreg->rIP);
    // int opcode1 = myPT->op1;
    // int opcode2 = myPT->op2;
    // int opcode3 = myPT->op3;
    routine = myPT[TPC].routine;
    goto *routine;
    
CLRA:
    // opcode 1: set content of register A to 0
    myreg->rIP += 1; myreg->rA = 0;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;
INC3A:
    // opcode 2: increment register A by 3
    myreg->rIP += 1; myreg->rA += 3;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;
DECA:
    // opcode 3: decrement register A by 1
    myreg->rIP += 1; myreg->rA -=1;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;
SETL:
    // opcode 4: copy value of register A to L
    myreg->rIP += 1; myreg->rL = myreg->rA;
    TPC += 1; routine = myPT[TPC].routine;
    goto *routine;     
BACK7:
    // opcode 5: decrement L; if value of L is positive, jump back by 7 instructions 
    // i.e. loop body is 6 one-byte instructions and the BACK7 itself
    if(myreg->rL <= 0) {
        myreg->rIP += 7; myreg->rL += 1;
        TPC += 7;
    }
    myreg->rIP -= 6; myreg->rL -= 1;
    TPC -= 6; routine = myPT[TPC].routine;
    goto *routine;
INC3A_CLRA:
    myreg->rIP += 2; myreg->rA = 0;
    TPC += 2; routine = myPT[TPC].routine;
    goto *routine;
INC3A_DECA:
    myreg->rIP += 2; myreg->rA += 2;
    TPC += 2; routine = myPT[TPC].routine;
    goto *routine;
INC3A_SETL:
    myreg->rIP += 2; myreg->rA += 3; myreg->rL = myreg->rA;
    TPC += 2; routine = myPT[TPC].routine;
    goto *routine;
INC3A_BACK7:
    if(myreg->rL <= 0) {
        myreg->rIP += 7; myreg->rL += 1;
        TPC += 7;
    }
    myreg->rIP -= 4; myreg->rA += 3; myreg->rL -= 1;
    TPC -= 5; routine = myPT[TPC].routine;
    goto *routine;
HALT:
    // opcode 0: stop execution
    free(myPT);
}