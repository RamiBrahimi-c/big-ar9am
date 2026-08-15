#include "../../include/bigra9m.h"

// NOTE : not configured yet with dynammic approach


// fucking hell .
// fuck this shit 
// TODO : this is NOT bug-free !!!!!!!!!!!!! 
void bigra9m_sub(BigInt a , BigInt b , BigInt *c) {
    if (a.length * b.length < 0)
    {
        b.length *= -1 ; 
        bigra9m_add(a , b , c) ;
        return ; 
    }
    if ((a.length == b.length && !bigra9m_isBiggerThanNum(a , b)) ||
    abs(a.length) < abs(b.length) )
    {
        
        c->length = -1 ; 
        
        BigInt temp ; 
        memcpy(&temp , &a , sizeof(BigInt)) ; 
        memcpy(&a , &b , sizeof(BigInt)) ; 
        memcpy(&b , &temp , sizeof(BigInt)) ; 
    } else  {

        c->length = (a.length/a.length) ; 
    }


    if (abs(a.length) == abs(b.length))
    {
        // printf("here\n") ; 
        uint64_t overflow = 0 ;
        uint64_t result ;
        for (size_t i = 0; i < abs(a.length); i++)
        {
            if (a.nums[i] >= (b.nums[i] + overflow))
            {
                result = a.nums[i] - (b.nums[i] + overflow) ; 
                overflow = 0 ; 
            } else {
                result = (a.nums[i] + BASE)  - (b.nums[i] + overflow) ; 
                overflow = 1 ; 
            }
            
            c->nums[i] = (result % BASE)  ; 
        }

        c->length *= a.length  ; 
        if (overflow != 0 && 0)
        {
            c->nums[abs(a.length)] = overflow ; 
            c->length = a.length + (a.length/a.length) ; 
        }
        if (c->nums[abs(c->length)-1]==0 && c->length != 0)
        {
            c->length -= (c->length/c->length) ; 
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
        
        int j = 0 ; 
        uint64_t overflow = 0 ;
        uint64_t result ;
        for (size_t i = 0; i < abs(a.length); i++)
        {
            if (a.nums[i] >= (b.nums[i] + overflow))
            {
                result = a.nums[i] - (b.nums[i] + overflow) ; 
                overflow = 0 ; 
            } else {
                result = (a.nums[i] + BASE)  - (b.nums[i] + overflow) ; 
                overflow = 1 ; 
            }
            j++ ; 
            c->nums[i] = (result % BASE)  ; 
        }

        c->length *= j  ; 
        if (overflow != 0)
        {
            printf("overflow\n") ;
            j++ ; 
            c->nums[abs(umm->length)] = overflow ; 
            c->length = umm->length + (umm->length/umm->length) ; 
        }
        
        if (c->nums[c->length-1]==0 && c->length != 0)
        {
            c->length -= (c->length/c->length) ; 
        }
    }    
    // to actually clean the result and not left it with some useless 0s
    while (!bigra9m_is_clean_lastdigit(*c))
    {
        bigra9m_clean_lastdigit(c) ; 
    }
    
}

