#include "../../include/bigra9m.h"

// NOTE : not configured yet with dynammic approach


void bigra9m_mod2(BigInt dividend , BigInt divisor , BigInt quoeff , BigInt *c) {
    BigInt temp , temp2; 

    bigra9m_init(&temp) ;
    bigra9m_init(&temp2) ;
    #ifdef DEBUG_MOD2
        printf("multiplying : ");
        bigra9m_print(divisor) ; 
        printf("and : ");
        bigra9m_print(quoeff) ; 
    #endif
    bigra9m_mul(divisor , quoeff , &temp) ; 
    #ifdef DEBUG_MOD2

        printf("=  ");
        bigra9m_print(temp) ; 
    
        printf("subtracting : ") ; 
        bigra9m_print(dividend) ; 
        printf("and : ") ; 
        bigra9m_print(temp) ; 
    #endif    
    
    bigra9m_sub(dividend , temp , c);
    
    #ifdef DEBUG_MOD2
        printf("=  ");
        bigra9m_print(*c) ; 
    #endif
}


void bigra9m_mod(BigInt dividend , BigInt divisor , BigInt *c) {
    BigInt a ;
    bigra9m_div(dividend , divisor ,&a , c ) ; 
}
