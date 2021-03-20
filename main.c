// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/predecoder.h"
#include "interpreter/interpreter.h"
#include "binary_translator/jit_compiler.h"

struct timespec diff(struct timespec, struct timespec);

int main(int argc, char *argv[]) {

    // Initialize the register and senario
    reg myreg = {0, 0, 0};
    int size = 10000;
    int seed = 1;
    int prob[5] = {1,9,1,5,5};
    int prob_1[5] = {0,1,0,0,0};
    int prob_2[5] = {1,1,1,0,0};
    int senario = 3;
    int rounds = 1;

    // Select senario based on the 1st parameter
    if (argc > 1){
        rounds = atoi(argv[1]);
    }
    // Dertermine round numbers based on the 2nd parameter
    if (argc > 2) {
        senario = atoi(argv[2]);
        switch (senario){
            case 1: memcpy(prob, prob_1, sizeof(prob_1)); break;
            case 2: memcpy(prob, prob_2, sizeof(prob_2)); break;
            case 3: break;
            case 4: seed = 2; break;
            case 5: seed = 3; break;
            case 6: size = 50000; break;
            case 7: size = 50000; seed = 2; break;
            case 8: size = 50000; seed = 3; break;
            default: ;;
            }
    }

    printf("\n");
    printf("####################\n");
    printf("senario: %d\n", senario);
    printf("size: %d\n", size);
    printf("seed: %d\n", seed);
    printf("prob: %d %d %d %d %d\n", prob[0], prob[1], prob[2], prob[3], prob[4]);
    printf("rounds: %d\n", rounds);
    printf("####################\n");
    printf("\n");

    // Initialize the instruction series (code buffer)
    char *buf = (char *) malloc(size * sizeof(char));
    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);
    myreg.rIP = buf;

    struct reg machine_reg = myreg; 
    struct timespec start, end, temp;
    double wtime;

    printf("INT_v1: No optimization\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++)
        interpreter_v1(buf, size, &machine_reg);
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    printf("INT_v2: Computed goto\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++)
        interpreter_v2(buf, size, &machine_reg);
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    printf("INT_v3: Predecoded computed goto\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++)
        interpreter_v3(buf, size, &machine_reg);
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    printf("INT_v4: Superevents\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++)
        interpreter_v4(buf, size, &machine_reg);
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    /* The performance sucks */
    // clock_gettime(CLOCK_MONOTONIC, &start);
    // machine_reg = myreg; 
    // for(i = 0; i < rounds; i++){
    //     jit_v0(buf, size, &machine_reg);
    // }
    // clock_gettime(CLOCK_MONOTONIC, &end);
    // temp = diff(start, end);
    // time_used_v5 = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    // printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    // printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", time_used_v5/rounds*1000);
    // printf("\n");

    printf("JIT_v1: Pre-generation of static BBs\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++){
        jit_v1(buf, size, &machine_reg);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    printf("JIT_v2: Pre-generation of dynamic BBs\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++){
        jit_v2(buf, size, &machine_reg);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    printf("JIT_v3: Dynamic generation of dynamic BBs\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++){
        jit_v3(buf, size, &machine_reg);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    printf("JIT_v4: Chained Dynamic generation of dynamic BBs\n");
    machine_reg = myreg; 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < rounds; i++){
        jit_v4(buf, size, &machine_reg);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = diff(start, end);
    wtime = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
    printf("myreg.rA: %d, myreg.rL: %d\n", machine_reg.rA, machine_reg.rL);
    printf("Total wall-clock Time (CLOCK_MONOTONIC) = %f msec\n", wtime/rounds*1000);
    printf("\n");

    free(buf);
    return 0;
}

struct timespec diff(struct timespec start, struct timespec end) {
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}