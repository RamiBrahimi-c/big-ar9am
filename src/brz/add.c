#include "../../include/bigra9m.h"
#include "../../include/utils.h"
#include <stdlib.h>
// NOTE : apparently configured with dynammic approach


static void simple_addition(BigInt a , BigInt b , BigInt *c) {
// lets assume same length for a and b
    if (abs(a.length) == abs(b.length))
    {
        uint64_t overflow = 0 ;
        for (size_t i = 0; i < abs(a.length); i++)
        {
            uint64_t result = a.nums[i] + b.nums[i] + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            
        }

        c->length = a.length  ; 
        if (overflow != 0)
        {
            c->nums[abs(a.length)] = overflow ; 
            c->length = a.length + (a.length/abs(a.length)) ; 
        }
        
    } else {

        size_t min_len = (abs(a.length) < abs(b.length)) ? abs(a.length) : abs(b.length) ;
        size_t max_len ;
        BigInt *umm ;
        if (abs(a.length) > abs(b.length))
        {
            max_len = abs(a.length) ;
            umm = &a ; 
        } else {
            max_len = abs(b.length) ;
            umm = &b ; 

        }
        

        uint64_t overflow = 0 ;
        for (size_t i = 0; i < min_len; i++)
        {
            uint64_t result = a.nums[i] + b.nums[i] + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0  ;
            }
            
        }
        for (size_t i = min_len; i < max_len ; i++)
        {
            uint64_t result = umm->nums[i]  + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            
        }

        c->length = umm->length  ; 
        if (overflow != 0)
        {
            c->nums[abs(umm->length)] = overflow ; 
            c->length = umm->length + (umm->length/umm->length) ; 
        }
    }

} 


// TODO: handle when some length is 0
void bigra9m_add(BigInt a , BigInt b , BigInt *c ) {
    if (a.length * b.length < 0)
    {
        if (bigra9m_is_negative(a))
        {
            a.length *= -1 ; 
            bigra9m_sub(&b , &a , c) ; 

            return ;            
        }
        if (bigra9m_is_negative(b))
        {
            b.length *= -1 ; 
        }

        
        bigra9m_sub(&a , &b , c) ; 
        return ;
    }
    // proper reallocation by our concept (which is idk what tbh); 
    if (c->capacity < MAX(abs(a.length) , abs(b.length)) *2)
    {
        c->capacity = MAX(abs(a.length) , abs(b.length)) *2 ; 
        c->nums =  realloc(c->nums , c->capacity * sizeof(uint64_t)) ; 
        memset(c->nums , 0x0 , sizeof(uint64_t)*(c->capacity)) ; 
    }
    

    simple_addition(a, b , c) ; 
    
}


void bigra9m_add_1(BigInt a , uint64_t b , BigInt *c ) {
    if (bigra9m_is_negative(a))
    {
        fprintf(stderr , "ERROR : works only when 'a' is POSITIVE\n") ; 
        return ; 
    }
    

        uint64_t overflow = b ;
        uint64_t result  ;
        for (size_t i = 0; i < abs(a.length); i++)
        {
            // if (i==0)
            // {
                // result = a.nums[i] + b + overflow ; 
                /* code */
            // } else {
                result = a.nums[i]  + overflow ; 

            // }
            
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            
        }

        c->length = a.length  ; 
        if (overflow != 0)
        {
            c->nums[abs(a.length)] = overflow ; 
            if (a.length == 0)
            {
                c->length = 1; 
                /* code */
            }else {
                c->length = a.length + (a.length/abs(a.length)) ; 

            }
            
        }



}


