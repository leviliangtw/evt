// main.c
#include <stdio.h>
#include <stdlib.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v1.h"

int main(int argc, char *argv[]){
    reg myreg = {0, 0, 0};
    char buf[10000];
    // char *buf = (char *) malloc(1000000 * sizeof(char));  
    int size = 10000;
    int prob[] = {0,1,0,0,0};
    // int prob[] = {1,1,1,0,0};
    // int prob[] = {1,2,3,4,5};
    // int prob[] = {1,9,1,5,5};
    int seed = 1;

    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);

    myreg.rIP = buf;
    char inst = *(myreg.rIP);
    int opcode = inst;
    interpreter_v1(buf, size, &myreg);
    return 0;
}