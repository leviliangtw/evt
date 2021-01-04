#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "generator/gen.h"
#include "interpreter/reg.h"
#include "binary_translator/bigen_v1.h"

struct code_cache {
    int tag;
    int invalidated; 
    unsigned char *bi_code;
}   typedef code_cache;

struct translation_table {
    char *SPC;
    int TPC;
}   typedef translation_table;

int main(int argc, char *argv[]){
    // initialize the register and senario
    reg myreg = {0, 0, 0};
    int size = 10000;
    int seed = 1;
    int prob[5] = {1,9,1,5,5};
    int senario = 3;

    printf("\n");
    printf("####################\n");
    printf("senario: %d\n", senario);
    printf("size: %d\n", size);
    printf("seed: %d\n", seed);
    printf("prob: %d %d %d %d %d\n", prob[0], prob[1], prob[2], prob[3], prob[4]);
    printf("####################\n");

    char *buf = (char *) malloc(size * sizeof(char));
    init(buf, size, prob, seed, &myreg.rA, &myreg.rL);
    myreg.rIP = buf;
    struct reg myreg1 = myreg; 
    struct reg myreg2 = myreg; 
    printf("\n");

    /* test data */
    // char mybuf[] = {2,2,2,0};
    // myreg.rIP = mybuf;

    /* Assume myreg.rIP is SPC */
    int TPC = 0;
    int leader_count = 0;
    int leader_table[size];

    /* Build Leader Table */
    memset(leader_table, 0, sizeof(int)*size);
    leader_table[0] = 1;
    leader_count += 1;
    while(*(myreg.rIP)) {
        if (*(myreg.rIP) == 5) {
            leader_table[TPC-6] = 1;
            leader_table[TPC] = 1;
            leader_table[TPC+1] = 1;
            leader_count += 3;
        }
        myreg.rIP += 1;
        TPC += 1;
    }
    
    /* Build Translation Table */
    myreg.rIP = buf;    // reset SPC
    int tt_i = 0;
    struct code_cache *myCCs = (struct code_cache *)malloc(leader_count * sizeof(code_cache));
    struct translation_table *tt = (struct translation_table *)malloc(leader_count * sizeof(translation_table));
    for(int i=0; i<size; i++){
        if (leader_table[i] == 1){
            tt[tt_i].SPC = myreg.rIP+i;
            tt[tt_i].TPC = i;
            // printf("tt_i: %d, SPC: %p, TPC: %d, inst:%d \n", tt_i, tt[tt_i].SPC, tt[tt_i].TPC, *tt[tt_i].SPC);
            tt_i += 1;
        }
        // printf("%d ", leader_table[i]);
    }
    // printf("leader_count: %d\n", leader_count);

    /* Build Code Cache */
    printf("myreg1.rIP:%p, myreg1.rA: %d, myreg1.rL: %d\n", myreg.rIP, myreg.rA, myreg.rL);
    int cc_size; 
    for(int i=0; i<tt_i-1; i++){
        myCCs[i].tag = tt[i].TPC;
        myCCs[i].invalidated = 1;
        cc_size = tt[i+1].SPC - tt[i].SPC;
        myCCs[i].bi_code = binary_generator_v1(&myreg, cc_size);
        // printf("i: %d, SPC: %p, myreg.rIP: %p, TPC: %d, inst:%d, cc_size:%d \n", i-1, tt[i-1].SPC, myreg.rIP, tt[i-1].TPC, *tt[i-1].SPC, cc_size);
        // printf("myreg1.rIP:%p, TPC: %d, myreg1.rA: %d, myreg1.rL: %d\n", myreg.rIP, tt[i-1].TPC, myreg.rA, myreg.rL);
        // ((void(*)(int32_t *rA, int32_t *rL))myCCs[i].bi_code)(&myreg.rA, &myreg.rL);
    }
    cc_size = size - tt[tt_i-1].TPC;
    myCCs[tt_i-1].tag = tt[tt_i-1].TPC;
    myCCs[tt_i-1].invalidated = 1;
    myCCs[tt_i-1].bi_code = binary_generator_v1(&myreg, cc_size);
    ((void(*)(int32_t *rA, int32_t *rL))myCCs[tt_i-1].bi_code)(&myreg.rA, &myreg.rL);

    /* Execute Code Cache */
    for(int i=0; i<tt_i; i++){
        // printf("i: %d; \n", i);
        ((void(*)(int32_t *rA, int32_t *rL))myCCs[i].bi_code)(&myreg1.rA, &myreg1.rL);
    }
    // printf("tt_i: %d\n", tt_i);
    printf("myreg1.rIP:%p, myreg1.rA: %d, myreg1.rL: %d\n", myreg1.rIP, myreg1.rA, myreg1.rL);
    printf("\n");

    /* Execute Static Binary Translation */
    printf("myreg2.rIP:%p, myreg2.rA: %d, myreg2.rL: %d\n", myreg2.rIP, myreg2.rA, myreg2.rL);
    unsigned char *mybi_code; 
    // myreg2.rIP += 140;
    mybi_code = binary_generator_v1(&myreg2, size);
    /* execute array */
	((void(*)(int32_t *rA, int32_t *rL))mybi_code)(&myreg2.rA, &myreg2.rL);
    free(mybi_code);
    printf("myreg2.rIP:%p, myreg2.rA: %d, myreg2.rL: %d\n", myreg2.rIP, myreg2.rA, myreg2.rL);
    printf("\n");
    
    return 0;
}