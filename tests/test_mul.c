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


    BigInt a  , c  ,d , e , f;
    
    // bigra9m_init(&c) ; 
    bigra9m_init_str(&a , "213304013") ; 
    bigra9m_init_str(&c , "-1529457609") ; 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 
    printf("after : \n") ; 

    bigra9m_mul(&a , &c , &a) ; 
    // bigra9m_mul_uint64(a , 10 , &a) ; 
    // bigra9m_add_1(a , 10000 , &a) ;
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 


    // bigra9m_inits(&d , &e ,  &f, NULL) ;
    
    bigra9m_clears(&a , &c , NULL) ; 

}