#include "../../include/bigra9m.h"

#include <stdio.h>
#include <stdlib.h>

// NOTE : not configured yet with dynammic approach

void bigra9m_mul_uint64(BigInt a , uint64_t b, BigInt *c) {
    BigInt *b_big = malloc(sizeof(BigInt)) ;
    if (b_big == NULL)
    {
        fprintf( stderr, "aw\n") ;
        return ;  
    }

    bigra9m_assign_uint64_t(b_big , b) ; 
    bigra9m_mul(a , *b_big , c) ; 
}

// our dummy so called naive algorithm 
// complexity O(n²)
// REQUIRES FOR C TO BE INITILIZED PROPERLY ...
void bigra9m_mul(BigInt a , BigInt b , BigInt *c) {
    BigInt *result = malloc(sizeof(BigInt)) ;
    if (result == NULL)
    {
        fprintf( stderr, "aw\n") ;
        return ;  
    }
    

    if ((a.length == b.length && a.nums[abs(a.length)-1] > b.nums[abs(b.length)-1]) ||
    abs(a.length) > abs(b.length) )
    {        
        BigInt temp ; 
        memcpy(&temp , &a , sizeof(BigInt)) ; 
        memcpy(&a , &b , sizeof(BigInt)) ; 
        memcpy(&b , &temp , sizeof(BigInt)) ; 
    } 
    uint64_t overflow = 0 ;
            
    for (size_t i = 0; i < abs(a.length); i++)
    {
        overflow = 0 ; 
        for (size_t j = 0; j < abs(b.length); j++)
        {
            result->nums[i+j] += (a.nums[i] * b.nums[j]) + overflow ; 
                    
                    
            if (result->nums[i+j] >= BASE)
            {
                overflow = result->nums[i+j] ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            result->nums[i+j] %= BASE  ; 
                    
        }
        result->length =  i+abs(b.length)  ;
        if (overflow)
        {
            result->nums[i+abs(b.length)] = (overflow )  ;
            result->length =  i+abs(b.length)  +1;
        }
    }

    if (a.length * b.length > 0) {
        result->length *= (int) (a.length/a.length) ; 
    } else {
        result->length *= -1 ; 

    }
    memcpy(c , result , sizeof(BigInt)) ; 
}
