/*
    Program to calculate negative factorial of -1 down to N (could be -100 , -10000 , -100000000 , ...)
    chose this approach to validate bigra9m_sub(BigInt *,BigInt *,BigInt *)
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bigra9m.h"

#define N 100

int main()
{

    uint32_t a = 0 ; 
    uint32_t b = 1 ; 
    uint32_t r ; 

    uint64_t a2 = 0 ; 
    uint64_t b2 = 1 ; 
    uint64_t r2 ; 


    BigInt temp2 , temp , num , num2 , num3 ;
    
    bigra9m_assign_str(&temp2 , "1") ; 
    bigra9m_assign_str(&temp , "1") ; 
    bigra9m_assign_str(&num , "0") ; 
    bigra9m_assign_str(&num2 , "1") ; 
    bigra9m_assign_str(&num3 , "1") ; 
    


    for (size_t i = 1; i < N; i++)
    {
        r = a + b ;
        r2 = a2 + b2 ;
        bigra9m_sub(num , num2 , &num3) ; 
        // bigra9m_add(num , num2 , &num3) ; 
        
        // printf("%u\t%lu\t" , r , r2) ;
        bigra9m_print(num3) ; 
        
        a = b ;
        b = r ; 
        
        
        a2 = b2 ;
        b2 = r2 ; 
        
        bigra9m_assign(&num , num2 ) ; 
        bigra9m_assign(&num2 , num3) ; 

        if (num.length > MAX_LEN || num2.length > MAX_LEN || num3.length > MAX_LEN )
        {
            printf("FATAL ERROR !!!!!!!!!!!!!\n") ; 
            exit(EXIT_FAILURE) ; 
        }
        

    }
}