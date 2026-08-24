/*
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bigra9m.h"
#include "../include/utils.h"
#include "../include/test.h"

#define N 100

int main()
{

    uint64_t a2 = 0 ; 


    BigInt a , b , c , d ;
    
    bigra9m_inits( &a, &b, &c , &d , NULL) ; 
    bigra9m_assign_str( &a , "2") ; 
    bigra9m_assign_str(&b , "2") ; 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    
    // bigra9m_add_1(a , 10000 , &a) ;
    bigra9m_div(&a , &b , &c , &d) ; 
    // bigra9m_sub(&a , &a , &a) ; 
    // knuths_algorithm_d(a , b , &c , &d) ; 
    
    printf("after : \n") ; 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 
    printf("d : ") ; 
    bigra9m_print(d) ; 

    // bigra9m_clear(&b) ; 
    bigra9m_clears(&a, &b, &c , &d , NULL) ; 


}