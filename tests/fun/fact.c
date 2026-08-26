/*
    Program to calculate factorial of 1 up to N (could be 100 , 10000 , 100000000 , ...)
    chose this approach to validate bigra9m_mul(BigInt *,BigInt *,BigInt *)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bigra9m.h"

#define N 100

int main()
{

    BigInt temp2 , temp , num , num2 , num3 ;


    bigra9m_assign_str(&temp2 , "1") ; 
    bigra9m_assign_str(&temp , "1") ; 
    bigra9m_assign_str(&num , "1") ; 
    bigra9m_assign_str(&num2 , "1") ; 
    bigra9m_assign_str(&num3 , "1") ; 
    


    uint64_t f = 1 ; 


    printf("===========================\n") ;
    for (size_t i = 1; i < N; i++)
    {

        f = f *i ;
        bigra9m_init(&num3) ; 
        bigra9m_mul(&num , &num2 , &num3) ; 
        
        
        bigra9m_print(num3);
        bigra9m_assign(&num , num3) ; 
        
        
        bigra9m_add(temp , num2 , &temp2) ;
        bigra9m_assign(&num2 , temp2) ; 
        
        
        if (num.length > MAX_LEN || num2.length > MAX_LEN || num3.length > MAX_LEN )
        {
            printf("FATAL ERROR !!!!!!!!!!!!!\n") ; 
            exit(EXIT_FAILURE) ; 
        }
        
    }

    exit(EXIT_SUCCESS) ; 
}