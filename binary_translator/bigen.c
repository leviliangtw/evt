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
    0x83, 0x7d, 0xf4, 0x00,                     // cmpl   $0x0,-0xc(%rbp)
    0x7f, 0x09,                                 // jg   <next+9>
    0x48, 0x83, 0x45, 0xf8, 0x07,               // addq   $0x7,-0x8(%rbp)
    0x83, 0x45, 0xf4, 0x01,                     // addl   $0x1,-0xc(%rbp)
    0x48, 0x83, 0x6d, 0xf8, 0x06,               // subq   $0x6,-0x8(%rbp)
    0x83, 0x6d, 0xf4, 0x01,                     // subl   $0x1,-0xc(%rbp)
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