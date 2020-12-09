// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v4.h"

int main(int argc, char *argv[]){
    reg myreg = {0, 0, 0};
    int size = 10000;
    int seed = 1;
    int prob[5] = {1,9,1,5,5};
    int prob_1[5] = {0,1,0,0,0};
    int prob_2[5] = {1,1,1,0,0};
    int senario = 1;

    if (argc-1){
        senario = atoi(argv[1]);
        switch (senario){
            case 1:
                memcpy(prob, prob_1, sizeof(prob_1)); 
                break;
            case 2:
                memcpy(prob, prob_2, sizeof(prob_2)); 
                break;
            case 3:
                break;
            case 4:
                seed = 2;
                break;
            case 5:
                seed = 3;
                break;
            case 6:
                size = 50000;
                break;
            case 7:
                size = 50000;
                seed = 2; 
                break;
            case 8:
                size = 50000;
                seed = 3; 
                break;
            default:
                ;
            }
    }
        
    char *buf = (char *) malloc(size * sizeof(char));
    myreg.rIP = buf;

    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);
    interpreter_v4(buf, size, &myreg);
    
    free(buf);
    return 0;
}