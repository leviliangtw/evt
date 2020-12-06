// main.c
#include <stdio.h>
#include <stdlib.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "interpreter/interpreter_v3.h"

int main(int argc, char *argv[]){
    int size = 10000;
    int seed = 3;
    int prob[] = {1,9,1,5,5};
    // int prob[] = {0,1,0,0,0};
    // int prob[] = {1,1,1,0,0};
    reg myreg = {0, 0, 0};

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
        
    char *buf = (char *) malloc(size * sizeof(char));
    myreg.rIP = buf;

    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);
    interpreter_v3(buf, size, &myreg);
    
    free(buf);
    return 0;
}