// main.c
#include <stdio.h>
#include <stdlib.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v1.h"

int main(int argc, char *argv[]){
    int size = 10000;
    int seed = 3;
    int prob[] = {1,9,1,5,5};
    // int prob[] = {0,1,0,0,0};
    // int prob[] = {1,1,1,0,0};
    reg myreg = {0, 0, 0};
    char *buf = (char *) malloc(1000000 * sizeof(char));  
    myreg.rIP = buf;

    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);
    interpreter_v1(buf, size, &myreg);
    
    free(buf);
    return 0;
}