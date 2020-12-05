// main.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v1.h"
#include "interpreter/interpreter_v2.h"

struct timespec diff(struct timespec, struct timespec);

int main(int argc, char *argv[]){
    reg myreg = {0, 0, 0};
    int size = 10000;
    int seed = 1;
    int prob[5] = {1,0,0,0,0};

    printf("\n");
    printf("Before case, prob: %d %d %d %d %d\n", prob[0], prob[1], prob[2], prob[3], prob[4]);

    if (argc-1)
        switch (*argv[1]){
            case '1':
                break;
            case '2':
                prob[1] = 1; prob[2] = 1; 
                break;
            case '3':
                prob[1] = 9; prob[2] = 1; prob[3] = 5; prob[4] = 5; 
                break;
            case '4':
                seed = 2; 
                prob[1] = 9; prob[2] = 1; prob[3] = 5; prob[4] = 5; 
                break;
            case '5':
                seed = 3; 
                prob[1] = 9; prob[2] = 1; prob[3] = 5; prob[4] = 5; 
                break;
            case '6':
                size = 50000; 
                prob[1] = 9; prob[2] = 1; prob[3] = 5; prob[4] = 5; 
                break;
            case '7':
                size = 50000; 
                seed = 2; 
                prob[1] = 9; prob[2] = 1; prob[3] = 5; prob[4] = 5; 
                break;
            case '8':
                size = 50000; 
                seed = 3; 
                prob[1] = 9; prob[2] = 1; prob[3] = 5; prob[4] = 5;
                break;
            default:
                ;
        }

    printf("After switch-case, size: %d\n", size);
    printf("After switch-case, seed: %d\n", seed);
    printf("After switch-case, prob: %d %d %d %d %d\n", prob[0], prob[1], prob[2], prob[3], prob[4]);

    char *buf = (char *) malloc(size * sizeof(char));
    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);

    printf("\n");
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
    test[7]=5;
    test[9]=0;
    // myreg.rIP = test;
    // rts.handles[*myreg.rIP](&myreg);
    // interpreter(test, size, &myreg);
    // ###### My Test Data ######

    clock_t c_start, c_end;
    double cpu_time_used;
    c_start = clock();

    // interpreter_v1(buf, size, &myreg);
    interpreter_goto(buf, size, &myreg);
    // interpreter_goto(test, size, &myreg);

    c_end = clock();
    cpu_time_used = ((double) (c_end - c_start)) / CLOCKS_PER_SEC;

    struct timespec start, end;
    double time_used;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // interpreter_v1(buf, size, &myreg);
    interpreter_goto(buf, size, &myreg);
    // interpreter_goto(test, size, &myreg);

    clock_gettime(CLOCK_MONOTONIC, &end);
    struct timespec temp = diff(start, end);
    time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;

    // printf("buf: %d\n", *buf);
    // printf("inst: %c\n", inst);
    // printf("opcode: %d\n", opcode);

    printf("After interpreter, myreg.rA: %d\n", myreg.rA);
    printf("After interpreter, myreg.rL: %d\n", myreg.rL);
    printf("\n");
    printf("Total Clocks = %ld\n", c_end-c_start);
    printf("Total Clocks/CLOCKS_PER_SEC = %f\n", cpu_time_used);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f\n", time_used);
    printf("\n");

    free(buf);
    return 0;
}

struct timespec diff(struct timespec start, struct timespec end) {
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}