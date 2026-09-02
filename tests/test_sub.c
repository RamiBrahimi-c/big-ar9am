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


    BigInt a   ,b, c ;
    
    bigra9m_inits(&a , &b , &c , NULL) ;

    // bigra9m_assign_uint64_t(&a , 120021) ; 
    // bigra9m_assign_uint64_t(&c , 12) ;
    bigra9m_assign_str(&a , "-1688433243809358094") ; 
    bigra9m_assign_str(&c , "-6629447832680730951") ; 
    
    // bigra9m_assign_uint64_t(&a , 90000) ; 
    printf("a : ") ; 
    bigra9m_print(a) ;
    printf("c : ") ; 
    bigra9m_print(c) ; 
    
    bigra9m_sub(&a , &c  , &a) ; 
    // bigra9m_add_1(a , 10000 , &a) ;
    printf("after : \n") ; 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 


    bigra9m_clears(&a , &b , &c , NULL) ; 

}