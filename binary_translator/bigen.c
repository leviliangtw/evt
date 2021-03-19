#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "bigen.h"
#include "../generator/gen.h"

/* Code Cache Prototype: 
void cc(char **rIP, int32_t *rA, int32_t *rL) {
    // [prolog]
    char *IP=*rIP; int A=*rA; int L=*rL;
    // [CLRA]
    A = 0; IP += 1;
    // [INC3A]
    A += 3; IP += 1;
    // [DECA]
    A -= 1; IP += 1;
    // [SETL]
    L = A; IP += 1;
    // [BACK7]
    if(L == 0) { IP += 7; L += 1; }
    IP -= 6; L -= 1;
    // [epilog]
    *rIP = IP; *rA = A; *rL = L;
}
*/

unsigned char HALT[] = {
    0x90,						                // nop
};

unsigned char CLRA[] = {
    /* A = 0; */
    0xc7, 0x45, 0xf0, 0x00, 0x00, 0x00, 0x00,	// movl   $0x0,-0x10(%rbp)
    /* IP += 1; */
    0x48, 0x83, 0x45, 0xf8, 0x01,               // addq   $0x1,-0x8(%rbp)
};

unsigned char INC3A[] = {
    /* A += 3; */
    0x83, 0x45, 0xf0, 0x03,		                // addl   $0x3,-0x10(%rbp)
    /* IP += 1; */
    0x48, 0x83, 0x45, 0xf8, 0x01,               // addq   $0x1,-0x8(%rbp)
};

unsigned char DECA[] = {
    /* A -= 1; */
    0x83, 0x6d, 0xf0, 0x01,		                // subl   $0x1,-0x10(%rbp)
    /* IP += 1; */
    0x48, 0x83, 0x45, 0xf8, 0x01,               // addq   $0x1,-0x8(%rbp)
};

unsigned char SETL[] = {
    /* L = A; */
    0x8b, 0x45, 0xf0,		                    // mov    -0x10(%rbp),%eax
    0x89, 0x45, 0xf4,		                    // mov    %eax,-0xc(%rbp)
    /* IP += 1; */
    0x48, 0x83, 0x45, 0xf8, 0x01,               // addq   $0x1,-0x8(%rbp)
};

unsigned char BACK7[] = {
    /* if(L < 1) { IP += 7; L += 1; }
    IP -= 6; L -= 1; */
    // 0x83, 0x7d, 0xf4, 0x00,                     // cmpl   $0x0,-0xc(%rbp)
    // 0x7f, 0x09,                                 // jg   <next+9>
    // 0x48, 0x83, 0x45, 0xf8, 0x07,               // addq   $0x7,-0x8(%rbp)
    // 0x83, 0x45, 0xf4, 0x01,                     // addl   $0x1,-0xc(%rbp)
    // 0x48, 0x83, 0x6d, 0xf8, 0x06,               // subq   $0x6,-0x8(%rbp)
    // 0x83, 0x6d, 0xf4, 0x01,                     // subl   $0x1,-0xc(%rbp)

    /* if(L > 0) { IP -=6; L -= 1; }
    else IP ++; */
    0x83, 0x7d, 0xf4, 0x00,                     // cmpl   $0x0,-0xc(%rbp)
    0x7e, 0x10,                                 // jle   <next+16>
    0x48, 0x83, 0x6d, 0xf8, 0x06,               // subq   $0x6,-0x8(%rbp)
    0x83, 0x6d, 0xf4, 0x01,                     // subl   $0x1,-0xc(%rbp)
    0xe9, 0x00, 0x00, 0x00, 0x00,               // jmp   <next+0>: preservation for chaining
    0xeb, 0x0a,                                 // jmp   <next+10>
    0x48, 0x83, 0x45, 0xf8, 0x01,               // addq   $0x1,-0x8(%rbp)
    0xe9, 0x00, 0x00, 0x00, 0x00,               // jmp   <next+0>: preservation for chaining
    // 0x90,						                // nop: segmentation fault happens without nop

};

unsigned char prolog[] = {
    /* Regular Calling Convention */
	0x55,						// push   %rbp
    0x48, 0x89, 0xe5,			// mov    %rsp,%rbp
	0x48, 0x89, 0x7d, 0xe8,		// mov    %rdi,-0x18(%rbp), 1st Parameter: char **rIP
    0x48, 0x89, 0x75, 0xe0,		// mov    %rsi,-0x20(%rbp), 2nd Parameter: int *rA
    0x48, 0x89, 0x55, 0xd8,     // mov    %rdx,-0x28(%rbp), 3rd Parameter: int *rL

    /* Assign *rIP to a local variable IP: char *IP=*rIP; */
    0x48, 0x8b, 0x45, 0xe8,     // mov    -0x18(%rbp),%rax
    0x48, 0x8b, 0x00,           // mov    (%rax),%rax
    0x48, 0x89, 0x45, 0xf8,     // mov    %rax,-0x8(%rbp)

    /* Assign *rA to a local variable A: int A=*rA; */
    0x48, 0x8b, 0x45, 0xe0,		// mov    -0x20(%rbp),%rax
    0x8b, 0x00,					// mov    (%rax),%eax
    0x89, 0x45, 0xf0,		    // mov    %eax,-0x10(%rbp)

    /* Assign *rL to a local variable L: int L=*rL; */
    0x48, 0x8b, 0x45, 0xd8,		// mov    -0x28(%rbp),%rax
    0x8b, 0x00,					// mov    (%rax),%eax
    0x89, 0x45, 0xf4,		    // mov    %eax,-0xc(%rbp)


};

unsigned char epilog[] = {
    /* Assign the local variable IP back to a 1st parameter *rIP: *rIP = IP; */
    0x48, 0x8b, 0x45, 0xe8,         // mov    -0x18(%rbp),%rax
    0x48, 0x8b, 0x55, 0xf8,         // mov    -0x8(%rbp),%rdx
    0x48, 0x89, 0x10,               // mov    %rdx,(%rax)

    /* Assign the local variable A back to a 2nd parameter *rA: *rA = A; */
    0x48, 0x8b, 0x45, 0xe0,		    // mov    -0x20(%rbp),%rax
    0x8b, 0x55, 0xf0,			    // mov    -0x10(%rbp),%edx
    0x89, 0x10,					    // mov    %edx,(%rax)

    /* Assign the local variable L back to a 3rd parameter *rL: *rL = L; */
    0x48, 0x8b, 0x45, 0xd8,		    // mov    -0x28(%rbp),%rax
    0x8b, 0x55, 0xf4,			    // mov    -0xc(%rbp),%edx
    0x89, 0x10,					    // mov    %edx,(%rax)

    /* Regular Calling Convention */
    0x90,						    // nop
	0x5d,						    // pop    %rbp
    0xc3,						    // retq
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
    /* binary code initialization */
    int bi_code_byte_pointer = 0;
    unsigned char *bi_code = (char *) malloc(
        bi_translations_v1[6].len +             // prolog
        size * bi_translations_v1[5].len +      // BACK7 (max)
        bi_translations_v1[7].len);             // epilog
    
    /* prolog initialization */
    memcpy(bi_code, bi_translations_v1[6].codes, bi_translations_v1[6].len);
    bi_code_byte_pointer += bi_translations_v1[6].len;
    
    int i = size;
    char * l_rIP = myreg->rIP;  // local rIP
    int inst = *(l_rIP);        // Fetch the opcode of first instrucion: we do not have operands here, so it looks needless. 
    while (i--){
        inst = *(l_rIP);
        memcpy(&bi_code[bi_code_byte_pointer], bi_translations_v1[inst].codes, bi_translations_v1[inst].len);
        bi_code_byte_pointer += bi_translations_v1[inst].len;
        l_rIP += 1;
    }

    /* epilog initialization */
    memcpy(&bi_code[bi_code_byte_pointer], bi_translations_v1[7].codes, bi_translations_v1[7].len);

    /* get page size*/
    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("sysconf");
        return -1;
    }

    /* get memory page */
	void *addr = (void *)((unsigned long)bi_code & ((0UL - 1UL) ^ (pagesize-1)));

    /* set page attributes - here we allocate "size * 16" */	
	int ans = mprotect(addr, size * 16, PROT_READ|PROT_WRITE|PROT_EXEC);
	if (ans) {
		perror("mprotect");
		exit(EXIT_FAILURE);
	}
	
     return bi_code;
}

unsigned char *binary_generator_v2(unsigned char *rIP, int size, unsigned char **p_end) {

    /* binary code initialization */
    int bi_code_byte_pointer = 0;
    // unsigned char *bi_code = (char *) malloc(
    //     bi_translations_v1[6].len +             // prolog
    //     size * bi_translations_v1[5].len +      // BACK7 (max)
    //     bi_translations_v1[7].len);             // epilog
    
    unsigned char *bi_code = (char *) malloc(
        50 * (size-1) +                         // CLRA (12)
        bi_translations_v1[5].len +             // BACK7
        bi_translations_v1[6].len +             // prolog
        bi_translations_v1[7].len);             // epilog


    /* prolog initialization */
    memcpy(bi_code, bi_translations_v1[6].codes, bi_translations_v1[6].len);
    bi_code_byte_pointer += bi_translations_v1[6].len;
    
    int i = size;
    unsigned char * l_rIP = rIP;  // local rIP
    int inst = *(l_rIP);        // Fetch the opcode of first instrucion: we do not have operands here, so it looks needless. 
    while (i--){
        inst = *(l_rIP);
        memcpy(&bi_code[bi_code_byte_pointer], bi_translations_v1[inst].codes, bi_translations_v1[inst].len);
        bi_code_byte_pointer += bi_translations_v1[inst].len;
        l_rIP += 1;
    }






    // printf("    SPC: %d, *(l_rIP+1): %d\n", l_rIP+1-rIP, *(l_rIP+1));
    // printf("    SPC: %d, *(l_rIP):   %d\n", l_rIP-rIP, *(l_rIP));
    // for(int i=1; i<8; i++) {
    //     printf("    SPC: %d, *(l_rIP-%d): %d -> %d\n", l_rIP-i-rIP, i, *(l_rIP-i), bi_translations_v1[*(l_rIP-i)].len);
    // }

    // unsigned char *preCC_end;
    // unsigned char *sucCC_beg;
    // BACK7_chain(preCC_end, sucCC_beg, 0);

    // for(int i=1; i<200; i++) {
    //     printf("    bi_code_byte_pointer:%p -> %02x\n", 
    //     bi_code + bi_code_byte_pointer - i, 
    //     *(bi_code + bi_code_byte_pointer - i));
    // }
    // for(int i=1; i<20; i++) {
    //     printf("    sucCC_beg:%p -> %02x\n", (sucCC_beg+i), *(sucCC_beg+i));
    // }
    
    







    /* epilog initialization */
    memcpy(&bi_code[bi_code_byte_pointer], bi_translations_v1[7].codes, bi_translations_v1[7].len);

    /* get page size*/
    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("sysconf");
        return -1;
    }

    /* get memory page */
	void *addr = (void *)((unsigned long)bi_code & ((0UL - 1UL) ^ (pagesize-1)));

    /* set page attributes - here we allocate "size * 16" */	
	int ans = mprotect(addr, size * 16, PROT_READ|PROT_WRITE|PROT_EXEC);
	if (ans) {
		perror("mprotect");
		exit(EXIT_FAILURE);
	}

    /* Output end pointer */
    // printf("bi_code:%p->%d\n", bi_code, *bi_code, *bi_code); 
    *p_end = bi_code + bi_code_byte_pointer + bi_translations_v1[7].len -1;
    // printf("p_end:%p->%p->%d\n", p_end, *p_end, **p_end); 
	
     return bi_code;
}

void BACK7_chain(unsigned char *preCC_end, unsigned char *sucCC_beg, int forward) {

    preCC_end -= bi_translations_v1[7].len; 
    sucCC_beg += bi_translations_v1[6].len; 
    int rel32;

    // printf("    preCC_end-epilog: %p->%02x\n", preCC_end, *preCC_end); 
    // printf("    sucCC_beg-prolog: %p->%02x\n", sucCC_beg, *sucCC_beg); 
    // printf("\n"); 
    // printf("    sucCC_beg - preCC_end = %p - %p = %p\n", sucCC_beg, preCC_end-6, sucCC_beg - (preCC_end-6));
    // printf("\n"); 

    if(forward) {
        rel32 = sucCC_beg - (preCC_end + 1);
        *(preCC_end-3) = (rel32) & 255;
        *(preCC_end-2) = (rel32 >> 8) & 255;
        *(preCC_end-1) = (rel32 >> 16) & 255;
        *(preCC_end) = (rel32 >> 24) & 255;
    }
    else {
        rel32 = sucCC_beg - (preCC_end - 11);
        *(preCC_end-15) = (rel32) & 255;
        *(preCC_end-14) = (rel32 >> 8) & 255;
        *(preCC_end-13) = (rel32 >> 16) & 255;
        *(preCC_end-12) = (rel32 >> 24) & 255;

    }

    // for(int i=26; i>0; i--) {
    //     printf("    preCC_end-%02d: %p->%02x\n", i, preCC_end-i, *(preCC_end-i)); 
    // }
    //     printf("\n"); 
    // for(int i=0; i<10; i++) {
    //     printf("    sucCC_beg+%02d: %p->%02x\n", i, sucCC_beg+i, *(sucCC_beg+i)); 
    // }
    
}