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

#define DEBUG_MID_INV 0


void bigra9m_modinverse(BigInt *a , BigInt *m , BigInt *c) {
    if (bigra9m_is_zero(*a))
    {
        bigra9m_assign_uint64_t(c , 0) ; 
        return ;
    }
    
    BigInt big_1 ; 
    bigra9m_init(&big_1) ; 
    bigra9m_assign_uint64_t(&big_1 , 1) ; 

    if (bigra9m_isEqualNum(*m , big_1))
    {
        bigra9m_assign_uint64_t(c , 0) ; 
        return ;
    }
    BigRa9m temp_a ; 
    bigra9m_init(&temp_a) ; 

    if (bigra9m_isBiggerThanNum(*a , *m))
    {
        // do mod 
        bigra9m_mod(*a , *m , &temp_a) ;         
        #if DEBUG_MID_INV
        printf("done\n") ; 
        bigra9m_print(temp_a) ;
        #endif
    } else {
        bigra9m_assign(&temp_a , *a) ; 
    }
    
    BigInt x0 , x1 , q , t , m0 , a_s , m_s , temp ; 
    bigra9m_inits(&x0 , &x1 , &q , &t , &m0 , &a_s , &m_s , &temp , NULL) ; 
    
    bigra9m_assign_uint64_t(&x0 , 0) ; 
    bigra9m_assign_uint64_t(&x1 , 1) ; 
    bigra9m_assign(&m0 , *m) ; 
    bigra9m_assign(&a_s , temp_a) ; 
    bigra9m_assign(&m_s , *m) ; 

    int i = 0 ; 
    while (bigra9m_isStrictlyBiggerThanNum(a_s , big_1))
    {
        #if DEBUG_MID_INV
        printf("================ iteration : %d ================\n" , i) ; 
        #endif
        if (bigra9m_is_zero(m_s))
        {
            bigra9m_assign_uint64_t(c , 0) ; 

            // bigra9m_clears(, NULL) ; 
            bigra9m_clears(&x0 , &x1 , &q , &t , &m0 , &a_s , &m_s , &temp , &temp_a , &big_1  , NULL) ; 
            return ;
        }
        
        bigra9m_div2(&a_s , &m_s , &q) ; 
        bigra9m_assign(&t , m_s) ; 
        bigra9m_mod(a_s , m_s , &m_s) ; 
        bigra9m_assign(&a_s , t) ;
        bigra9m_assign(&t , x0) ;
        
        #if DEBUG_MID_INV
            printf("before op : \n") ; 
            printf("q : ") ; 
            bigra9m_print(q) ; 
            printf("x0 : ") ; 
            bigra9m_print(x0) ;
        #endif
        
        bigra9m_mul(&q , &x0 , &temp) ;
        
        #if DEBUG_MID_INV
            printf("result : ") ; 
            bigra9m_print(temp) ; 

            printf("x1 : ") ; 
            bigra9m_print(x1) ; 
        #endif
        
        bigra9m_sub(&x1 , &temp , &x0) ; 

        #if DEBUG_MID_INV
            printf("x0 : ") ; 
            bigra9m_print(x0) ; 

            printf("end op : \n") ;
        #endif

        if (bigra9m_is_negative(x0))
        {
            // bigra9m_add(x0 , *m , &x0) ; 
        }
        
        bigra9m_assign(&x1 , t) ;

        #if DEBUG_MID_INV
        printf("q : \n" ) ;
        bigra9m_print(q) ;  
        printf("t :\n" ) ; 
        bigra9m_print(t) ;  
        printf("m_s :\n" ) ; 
        bigra9m_print(m_s) ;  
        printf("a_s : \n" ) ; 
        bigra9m_print(a_s) ;  
        printf("x0 : \n" ) ; 
        bigra9m_print(x0) ;  
        printf("x1 : \n" ) ; 
        bigra9m_print(x1) ;  
        printf("temp : " ) ; 
        bigra9m_print(temp) ;  
        #endif

        i++ ; 
    }
    
    if (bigra9m_is_negative(x1))
    {
        #if DEBUG_MID_INV
        printf("result was negative \n") ; 
        #endif
        bigra9m_add(x1 , m0 , &x1) ; 
    }
    

    bigra9m_assign(c , x1) ; 
    
    bigra9m_clears(&x0 , &x1 , &q , &t , &m0 , &a_s , &m_s , &temp , &temp_a  , &big_1, NULL) ; 
}




