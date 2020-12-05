// main.c
#include <stdio.h>
#include <stdlib.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v2.h"

int main(int argc, char *argv[]){
    char *buf = (char *) malloc(1000000 * sizeof(char)); 
    reg myreg = {0, 0, 0};
    myreg.rIP = buf;
    int size = 10000;
    int seed = 1;
    // int prob[] = {1,9,1,5,5};
    // int prob[] = {0,1,0,0,0};
    int prob[] = {1,1,1,0,0}; 

    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);
    interpreter_goto(buf, size, &myreg);
    
    free(buf);
    return 0;
}