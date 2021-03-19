#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "jit_compiler.h"
#include "../generator/gen.h"
#include "../binary_translator/bigen.h"

/* Static BBs, Fully Associative Caches, Pre-generation */
void jit_v0(char *buf, int size, reg *myreg) {

    struct reg l_myreg = *myreg;    // local myreg

    /* Build Leader Table - Static BBs */
    /* myreg.rIP is SPC */
    int leader_table[size];
    int leader_index = 0;
    int leader_count = 0;
    memset(leader_table, 0, sizeof(int)*size);
    leader_table[0] = 1;
    leader_count += 1;
    while(*(l_myreg.rIP)) {
        if (*(l_myreg.rIP) == 5) {
            leader_table[leader_index-6] = 1;
            leader_table[leader_index+1] = 1;
            leader_count += 2;
        }
        l_myreg.rIP += 1;
        leader_index += 1;
    }
    
    /* Build Translation Table */
    l_myreg = *myreg;    // reset myreg -> reset SPC
    int tt_i = 0;
    struct code_cache *myCCs = (struct code_cache *)malloc(leader_count * sizeof(code_cache));
    struct translation_table *tt = (struct translation_table *)malloc((leader_count+1) * sizeof(translation_table));
    for(int i=0; i<size; i++){
        if (leader_table[i] == 1){
            tt[tt_i].SPC = l_myreg.rIP;
            tt_i += 1;
        }
        l_myreg.rIP += 1;
    }
    tt[tt_i].SPC = l_myreg.rIP;
    // tt[tt_i].TPC = myreg.rIP + size - 1;
    tt_i += 1;
    // printf("Leader instruction Counts: %d\n", leader_count);

    /* Build Code Cache */
    l_myreg = *myreg;    // reset myreg -> reset SPC
    int cc_size; 
    for(int i=0; i<tt_i-1; i++){
        myCCs[i].tag = tt[i].SPC;
        myCCs[i].valid = 1;
        cc_size = tt[i+1].SPC - tt[i].SPC;
        myCCs[i].bi_code = binary_generator_v1(&l_myreg, cc_size);
        tt[i].TPC = myCCs[i].bi_code;
        l_myreg.rIP += cc_size;
    }
    // printf("Code Cache Counts: %d\n", cc_size);

    /* Execution */
    while(*myreg->rIP) {
        for(int i=0; i<tt_i; i++){
            if(myCCs[i].tag == myreg->rIP) {
                ((void(*)(char **rIP, int32_t *rA, int32_t *rL))myCCs[i].bi_code)(&myreg->rIP, &myreg->rA, &myreg->rL);
                continue;
            }
        }
    }

    /* Memory Release */
    free(tt);
    for(int i=0; i<tt_i-1; i++){
        free(myCCs[i].bi_code);
    }
    free(myCCs);
}

/* Pre-generation of Static BBs, Direct Mapped Code Cache */
void jit_v1(char *buf, int size, reg *myreg) {

    struct reg l_myreg = *myreg;    // local myreg

    /* Build Leader Table - Static BBs */
    /* myreg.rIP is SPC */
    int leader_table[size];
    int leader_index = 0;
    int leader_count = 0;
    memset(leader_table, 0, sizeof(int)*size);
    leader_table[0] = 1;
    leader_count += 1;
    while(*(l_myreg.rIP)) {
        if (*(l_myreg.rIP) == 5) {
            leader_table[leader_index-6] = 1;
            leader_table[leader_index+1] = 1;
            leader_count += 2;
        }
        l_myreg.rIP += 1;
        leader_index += 1;
    }
    
    /* Build Translation Table & Code Cache */
    l_myreg = *myreg;    // reset myreg -> reset SPC
    int SPC = 0;
    struct translation_table *tt = (struct translation_table *)malloc((size+1) * sizeof(translation_table));
    for(int i=1; i<size; i++){
        if (leader_table[i] == 1){
            // printf("i: %d, SPC: %d, i-SPC: %d\n", i, SPC, i-SPC);
            tt[SPC].TPC = binary_generator_v1(&l_myreg, i-SPC);
            l_myreg.rIP += i-SPC;
            SPC = i;
        }
    }
    tt[SPC].TPC = binary_generator_v1(&l_myreg, size-SPC);

    /* Execution */
    l_myreg = *myreg;
    while(*myreg->rIP){
        SPC = myreg->rIP-l_myreg.rIP;
        ((void(*)(char **rIP, int32_t *rA, int32_t *rL))tt[SPC].TPC)(&myreg->rIP, &myreg->rA, &myreg->rL);
    }

    /* Memory Release */
    for(int i=0; i<size; i++){
        free(tt[i].TPC);
    }
    free(tt);
}

/* Pre-generation of Dynamic BBs, Direct Mapped Code Cache */
void jit_v2(char *buf, int size, reg *myreg) {

    struct reg l_myreg = *myreg;    // local myreg
    
    /* Build Dynamic Translation Table & Code Cache */
    char *ori_SPC = myreg->rIP, *BACK7_SPC = myreg->rIP;
    int index = 0, offset = 0;
    struct translation_table *tt = (struct translation_table *)malloc((size+1) * sizeof(translation_table));
    memset(tt, 0, (size+1) * sizeof(translation_table));

    // printf("*BACK7_SPC: %d\n", *BACK7_SPC);

    while(*BACK7_SPC) {
        index = l_myreg.rIP - ori_SPC;
        if(*BACK7_SPC == 5) {
            if(tt[index].TPC==0) {
                offset = BACK7_SPC - l_myreg.rIP + 1;
                tt[index].TPC = binary_generator_v1(&l_myreg, offset);
                BACK7_SPC -= 7;
            }
            BACK7_SPC++;
            l_myreg.rIP = BACK7_SPC;
        }
        else {
            BACK7_SPC++;
        }
    }
    index = l_myreg.rIP - ori_SPC;
    offset = BACK7_SPC - l_myreg.rIP + 1;
    tt[index].TPC = binary_generator_v1(&l_myreg, offset);

    /* Execution */
    l_myreg = *myreg;
    while(*myreg->rIP){
        index = myreg->rIP-l_myreg.rIP;
        ((void(*)(char **rIP, int32_t *rA, int32_t *rL))tt[index].TPC)(&myreg->rIP, &myreg->rA, &myreg->rL);
    }

    /* Memory Release */
    for(int i=0; i<size; i++){
        free(tt[i].TPC);
    }
    free(tt);
}

/* Dynamic Generation of Dynamic BBs, Direct Mapped Code Cache */
void jit_v3(char *buf, int size, reg *myreg) {

    
    /* Dynamic Translation Table & Code Cache */
    struct translation_table *tt = (struct translation_table *)malloc((size+1) * sizeof(translation_table));
    memset(tt, 0, (size+1) * sizeof(translation_table));

    /* Execution */
    char *ori_SPC = myreg->rIP, *BACK7_SPC;
    int index = 0, offset = 0;
    while(*myreg->rIP) {
        index = myreg->rIP - ori_SPC;
        if(tt[index].TPC != 0) 
            ((void(*)(char **rIP, int32_t *rA, int32_t *rL))tt[index].TPC)(&myreg->rIP, &myreg->rA, &myreg->rL);
        else {
            BACK7_SPC = myreg->rIP;
            while(*BACK7_SPC) {
                if(*(BACK7_SPC+1) == 5 | *(BACK7_SPC+1) == 0) {
                    offset = BACK7_SPC - myreg->rIP + 2;
                    tt[index].TPC = binary_generator_v1(myreg, offset);
                    break;
                }
                BACK7_SPC++;
            }
        }
    }

    /* Memory Release */
    for(int i=0; i<size; i++){
        free(tt[i].TPC);
    }
    free(tt);
}