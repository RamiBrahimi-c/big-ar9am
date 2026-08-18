#include "../../include/bigra9m.h"
#include "../../include/utils.h"

#include <stdio.h>
#include <stdlib.h>

// NOTE : configured with dynammic approach ?? 
// idk man , dont ask me !

void bigra9m_mul_uint64(BigInt *a , uint64_t b, BigInt *c) {
    BigInt b_big ; // = malloc(sizeof(b_big)) ;
    // printf("calling init from bigra9m_mul_uint64 for b_big %p  \n" , &b_big) ;     
    
    bigra9m_init(&b_big) ; 
    
    bigra9m_assign_uint64_t(&b_big , b) ; 
    bigra9m_mul(a , &b_big , c) ; 
    
    // printf("calling clear from bigra9m_mul_uint64 for b_big %p  \n" , &b_big) ;     
    bigra9m_clear(&b_big) ; 
    // free(b_big) ; 
}


// our dummy so called naive algorithm 
// complexity O(n²)
static void basecase_multiplication(BigInt a , BigInt b , BigInt *result) {
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

    // if (a.length * b.length > 0) {
    //     result->length *= (int) (a.length/a.length) ; 
    // } else {
    //     result->length *= -1 ; 

    // }

}

// REQUIRES FOR C TO BE INITILIZED PROPERLY ...
void bigra9m_mul(BigInt *a , BigInt *b , BigInt *c) {
    if (bigra9m_is_zero(*a) ||  bigra9m_is_zero(*b))
    {
        bigra9m_assign_uint64_t(c , 0) ; 
        return ; 
    }
    


    int sign = 1 ; 

    if (a->length * b->length < 0)
    {
        sign = -1 ; 
    }

    if (a==c || b==c)
    {
        BigInt temp_a , temp_b ; 
    // printf("calling inits from bigra9m_mul for tempa %p and temp_b %p \n" , &temp_a , &temp_b) ;     

        bigra9m_inits(&temp_a , &temp_b , NULL) ; 

        bigra9m_assign(&temp_a , *a) ; 
        bigra9m_assign(&temp_b , *b) ; 

        // c gotta be initilized 
        memset(c->nums , 0x0 , sizeof(uint64_t)*c->capacity) ; 
        
        // lets allocate for our result ...

        if (nextPowerOfTwo(abs(temp_a.length)+abs(temp_b.length)) >  c->capacity  ) {
            c->capacity = nextPowerOfTwo(abs(temp_a.length)+abs(temp_b.length)) ;
            BRZ_ALLOCATE_U64(c->nums , c->capacity ) 
            memset(c->nums + abs(c->length)  , 0 , sizeof(uint64_t)*(c->capacity -  abs(c->length) )) ;

        }

        basecase_multiplication(temp_a , temp_b , c) ; 
        // c->length *= sign ; 
    // printf("calling clears from bigra9m_mul for tempa %p and temp_b %p \n" , &temp_a , &temp_b) ;     

        // printf("temp_a.nums : %p \n" , temp_a.nums ) ; 
        bigra9m_clears(&temp_a , &temp_b , NULL) ; 

    } else {

        // c gotta be initilized 
        memset(c->nums , 0x0 , sizeof(uint64_t)*c->capacity) ; 
        
        // printf("wtf\n");
        // lets allocate for our result ...
        if (nextPowerOfTwo(abs(a->length)+abs(b->length)) >  c->capacity  ) {
            c->capacity = nextPowerOfTwo(abs(a->length)+abs(b->length)) ;
            BRZ_ALLOCATE_U64(c->nums , c->capacity ) 
            memset(c->nums + abs(c->length)  , 0 , sizeof(uint64_t)*(c->capacity -  abs(c->length) )) ;

        }


        basecase_multiplication(*a , *b , c) ; 
        
    }
    
    c->length *= sign ; 

}
