#include "../../include/bigra9m.h"

// NOTE : configured with dynammic approach
// #define DEBUG_MOD2 0

void bigra9m_mod2(BigInt dividend , BigInt divisor , BigInt quoeff , BigInt *c) {
    BigInt temp , temp2; 
    // printf("calling init from bigra9m_mod2 for temp %p , temp2 %p \n" , &temp , &temp2) ; 
    bigra9m_inits(&temp , &temp2 , NULL) ;
    #ifdef DEBUG_MOD2
        printf("multiplying : ");
        bigra9m_print(divisor) ; 
        printf("and : ");
        bigra9m_print(quoeff) ; 
    #endif
    bigra9m_mul(&divisor , &quoeff , &temp) ; 
    #ifdef DEBUG_MOD2

        printf("=  ");
        bigra9m_print(temp) ; 
    
        printf("subtracting : ") ; 
        bigra9m_print(dividend) ; 
        printf("and : ") ; 
        bigra9m_print(temp) ; 
    #endif    
    
    bigra9m_sub(&dividend , &temp , c);
    
    #ifdef DEBUG_MOD2
    printf("=  ");
    bigra9m_print(*c) ; 
    #endif
    // printf("calling clear from bigra9m_mod2 for temp %p , temp2 %p \n" , &temp , &temp2) ; 
    bigra9m_clears(&temp , &temp2 , NULL) ;


}
#define DEBUG_MOD 0

void bigra9m_mod(BigInt dividend , BigInt divisor , BigInt *c) {
    BigInt a ;
    bigra9m_init(&a) ; 
    bigra9m_div(&dividend , &divisor ,&a , c ) ; 
    #if DEBUG_MOD 
    printf("divisor is : ") ; 
        bigra9m_print(a) ; 
    #endif
    bigra9m_clear(&a) ; 
}
