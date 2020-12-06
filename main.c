// main.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v1.h"
#include "interpreter/interpreter_v2.h"
#include "interpreter/interpreter_v3.h"
#include "interpreter/interpreter_v4.h"
#include "interpreter/predecoder.h"

struct timespec diff(struct timespec, struct timespec);

int main(int argc, char *argv[]){
    reg myreg = {0, 0, 0};
    int size = 10000;
    int seed = 1;
    int prob[5] = {1,0,0,0,0};

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


    printf("size: %d\n", size);
    printf("seed: %d\n", seed);
    printf("prob: %d %d %d %d %d\n", prob[0], prob[1], prob[2], prob[3], prob[4]);

    char *buf = (char *) malloc(size * sizeof(char));
    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);
    myreg.rIP = buf;

    struct reg myreg1 = myreg; 
    struct reg myreg2 = myreg; 
    struct reg myreg3 = myreg; 
    struct reg myreg4 = myreg; 

    printf("After init, myreg.rA: %d\n", myreg.rA);
    printf("After init, myreg.rL: %d\n", myreg.rL);
    printf("\n");

    // ############ My Test Data ############
    // char test[10];
    // int i;
    // for(i=0; i<10; i++){
    //     test[i] = 2;
    // }
    // test[7]=5;
    // test[9]=0;
    // myreg.rIP = test;
    // rts.handles[*myreg.rIP](&myreg);
    // interpreter(test, size, &myreg);
    // ############ My Test Data ############

    // ############ My Clock Time Test ############
    // clock_t c_start, c_end;
    // double cpu_time_used;
    // c_start = clock();
    // interpreter_v1(buf, size, &myreg1);
    // interpreter_v2(buf, size, &myreg2);
    // interpreter_v3(buf, size, &myreg3);
    // interpreter_v4(buf, size, &myreg4);
    // c_end = clock();
    // cpu_time_used = ((double) (c_end - c_start)) / CLOCKS_PER_SEC;

    // struct timespec start, end;
    // double time_used;
    // clock_gettime(CLOCK_MONOTONIC, &start);
    // interpreter_v1(buf, size, &myreg1);
    // interpreter_v2(buf, size, &myreg2);
    // interpreter_v3(buf, size, &myreg3);
    // interpreter_v4(buf, size, &myreg4);
    // clock_gettime(CLOCK_MONOTONIC, &end);
    // struct timespec temp = diff(start, end);
    // time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    // printf("Total Clocks = %ld\n", c_end-c_start);
    // printf("Total Clocks/CLOCKS_PER_SEC = %f\n", cpu_time_used);
    // printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f\n", time_used);
    // printf("\n");
    // ############ My Clock Time Test ############

    interpreter_v1(buf, size, &myreg1);
    interpreter_v2(buf, size, &myreg2);
    interpreter_v3(buf, size, &myreg3);
    interpreter_v4(buf, size, &myreg4);

    printf("interpreter_v1, myreg.rA: %d\n", myreg1.rA);
    printf("interpreter_v1, myreg.rL: %d\n", myreg1.rL);
    printf("\n");
    printf("interpreter_v2, myreg.rA: %d\n", myreg2.rA);
    printf("interpreter_v2, myreg.rL: %d\n", myreg2.rL);
    printf("\n");
    printf("interpreter_v3, myreg.rA: %d\n", myreg3.rA);
    printf("interpreter_v3, myreg.rL: %d\n", myreg3.rL);
    printf("\n");
    printf("interpreter_v4, myreg.rA: %d\n", myreg4.rA);
    printf("interpreter_v4, myreg.rL: %d\n", myreg4.rL);
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