#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "bigen_v1.h"
#include "../generator/gen.h"

unsigned char HALT[] = {
    0x90,						// nop
};

unsigned char CLRA[] = {
    0xc7, 0x45, 0xf8, 0x00, 0x00, 0x00, 0x00,	// movl   $0x0,-0x8(%rbp)
};

unsigned char INC3A[] = {
    0x83, 0x45, 0xf8, 0x03,		// addl   $0x1,-0x8(%rbp)
};

unsigned char DECA[] = {
    0x83, 0x6d, 0xf8, 0x01,		// subl   $0x1,-0x8(%rbp)
};

unsigned char SETL[] = {
    0x8b, 0x45, 0xf8,		// mov    -0x4(%rbp),%eax
    0x89, 0x45, 0xfc		// mov    %eax,-0x4(%rbp)
};

unsigned char BACK7[] = {
    0x90,						// nop
};

unsigned char prolog[] = {
	0x55,						// push   %rbp
    0x48, 0x89, 0xe5,			// mov    %rsp,%rbp
	0x48, 0x89, 0x7d, 0xe8,		// mov    %rdi,-0x18(%rbp)
    0x48, 0x89, 0x75, 0xe0,		// mov    %rsi,-0x20(%rbp)
    0x48, 0x8b, 0x45, 0xe8,		// mov    -0x18(%rbp),%rax
    0x8b, 0x00,					// mov    (%rax),%eax
    0x89, 0x45, 0xf8,			// mov    %eax,-0x8(%rbp)
    0x48, 0x8b, 0x45, 0xe0,		// mov    -0x20(%rbp),%rax
    0x8b, 0x00,					// mov    (%rax),%eax
    0x89, 0x45, 0xfc,			// mov    %eax,-0x4(%rbp)
};

unsigned char epilog[] = {
    0x48, 0x8b, 0x45, 0xe8,		// mov    -0x18(%rbp),%rax
    0x8b, 0x55, 0xf8,			// mov    -0x8(%rbp),%edx
    0x89, 0x10,					// mov    %edx,(%rax)
    0x48, 0x8b, 0x45, 0xe0,		// mov    -0x20(%rbp),%rax
    0x8b, 0x55, 0xfc,			// mov    -0x4(%rbp),%edx
    0x89, 0x10,					// mov    %edx,(%rax)
    0x90,						// nop
	0x5d,						// pop    %rbp
    0xc3						// retq
};

struct bi_translations bi_translations_v1[] = {
    {HALT, sizeof(HALT)},
    {CLRA, sizeof(CLRA)},
    {INC3A, sizeof(INC3A)},
    {DECA, sizeof(DECA)},
    {SETL, sizeof(SETL)},
    {BACK7, sizeof(BACK7)},
    {prolog, sizeof(prolog)},
    {epilog, sizeof(epilog)}
};

unsigned char *binary_generator_v1(reg *myreg, int size){
    // int TPC = 0;             // initialization for myPT, useless
    // int SPC = 0;             // initialization for buf, useless
    int inst = *(myreg->rIP);   // initialization

    /* binary code initialization */
    int bi_code_byte_pointer = 0;
    unsigned char *bi_code = (char *) malloc((size+2) * 30);
    // unsigned char *bi_code = (char *) malloc(size * 8);
    
    memcpy(bi_code, bi_translations_v1[6].codes, bi_translations_v1[6].len);
    bi_code_byte_pointer += bi_translations_v1[6].len;
    
    int i = size;
    while (i--){
        inst = *(myreg->rIP);
        // printf("%d, ", inst);
        /* ignore BACK7 */
        // if(inst == 5) {
        //     // memcpy(&bi_code[bi_code_byte_pointer], bi_translations_v1[inst].codes, bi_translations_v1[inst].len);
        //     // bi_code_byte_pointer += bi_translations_v1[inst].len;
        //     myreg->rIP += 1;
        //     continue;
        // }
        memcpy(&bi_code[bi_code_byte_pointer], bi_translations_v1[inst].codes, bi_translations_v1[inst].len);
        bi_code_byte_pointer += bi_translations_v1[inst].len;
        myreg->rIP += 1;
    }
    // printf("\n", inst);

    memcpy(&bi_code[bi_code_byte_pointer], bi_translations_v1[7].codes, bi_translations_v1[7].len);

    /* get page size*/
    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("sysconf");
        return -1;
    }

    /* get memory page */
	void *addr = (void *)((unsigned long)bi_code & ((0UL - 1UL) ^ (pagesize-1)));

    /* set page attributes */	
	int ans = mprotect(addr, size * 8, PROT_READ|PROT_WRITE|PROT_EXEC);
	if (ans) {
		perror("mprotect");
		exit(EXIT_FAILURE);
	}
	
     return bi_code;
}