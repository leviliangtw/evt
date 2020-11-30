// main.c
#include <stdio.h>
#include <stdlib.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v1.h"
#include "interpreter/interpreter_v2.h"

int main(int argc, char *argv[]){
    reg myreg = {0, 0, 0};
    char buf[10000];
    // char *buf = (char *) malloc(1000000 * sizeof(char));  
    int size = 10000;
    int prob[] = {0,1,0,0,0};
    // int prob[] = {1,2,3,4,5};
    // int prob[] = {1,9,1,5,5};
    int seed = 1;

    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);

    printf("After init, myreg.rA: %d\n", myreg.rA);
    printf("After init, myreg.rL: %d\n", myreg.rL);
    printf("\n");

    myreg.rIP = buf;
    char inst = *(myreg.rIP);
    int opcode = inst;
    // struct routines rts = {{&HandleHALT, &HandleCLRA, &HandleINC3A, &HandleDECA, &HandleSETL, &HandleBACK7}};

    // ###### My Test Data ######
    char test[10];
    int i;
    for(i=0; i<10; i++){
        test[i] = 2;
    }
    test[2]=3;
    test[3]=1;
    test[4]=4;
    test[7]=5;
    test[9]=0;
    // myreg.rIP = test;
    // rts.handles[*myreg.rIP](&myreg);
    // interpreter(test, size, &myreg);
    // ###### My Test Data ######

    // interpreter_v1(buf, size, &myreg);
    interpreter_goto(buf, size, &myreg);

    // printf("buf: %d\n", *buf);
    // printf("inst: %c\n", inst);
    // printf("opcode: %d\n", opcode);
    printf("\n");
    printf("After interpreter, myreg.rA: %d\n", myreg.rA);
    printf("After interpreter, myreg.rL: %d\n", myreg.rL);

    return 0;
}