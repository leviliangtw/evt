// predecoder.c
#include "predecoder.h"

void predecoding(char *buf, int size, void *ins[], preTable *myPT, char superevents){
    // printf("    ins: %p\n", ins);
    // printf("    *ins: %p\n", *ins);
    // printf("*ins[1]: %p\n", routine[1]);

    if (superevents)
        for(int i = 0; i< size; i++){
            myPT[i].routine = ins[*(buf+i)];
            if (*(buf+i) == 2){
                switch (*(buf+i+1))
                {
                case 1:
                    myPT[i].routine = ins[6];
                    break;
                case 3:
                    myPT[i].routine = ins[7];
                    break;
                // case 4:
                //     myPT[i].routine = ins[8];
                //     break;
                // case 5:
                //     myPT[i].routine = ins[9];
                //     break;
                // default:
                //     break;
                }
                // if (*(buf+i+1) == 1) myPT[i].routine = ins[6];
                // else if (*(buf+i+1) == 3) myPT[i].routine = ins[7];
                // else if (*(buf+i+1) == 4) myPT[i].routine = ins[8];
                // else if (*(buf+i+1) == 5) myPT[i].routine = ins[9];
            }
            // op1
            // op2
            // op3
        }
    else
        for(int i = 0; i< size; i++){
            myPT[i].routine = ins[*(buf+i)];
            // op1
            // op2
            // op3
        }
    
    // printf("    buf+size: %d\n", *(buf+size));
    // printf("    myPT[0].routine: %p\n", myPT[0].routine);
    // printf("    myPT[size-2].routine: %p\n", myPT[size-2].routine);
    // printf("    myPT[size-1].routine: %p\n", myPT[size-1].routine);

}