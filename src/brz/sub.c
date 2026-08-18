#include "../../include/bigra9m.h"
#include "../../include/utils.h"
#include <stdlib.h>

// NOTE : configured with dynammic approach ???
// IMPORTANT NOTE : more tests needed !!!


void static basic_subtraction(BigInt a , BigInt b , BigInt *c) {
    if (abs(a.length) == abs(b.length))
    {
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
        // printf("here\n") ; 
        if (overflow != 0)
        {
            j++ ; 
            c->nums[abs(umm->length)] = overflow ; 
            c->length = umm->length + (umm->length/umm->length) ; 
        }
        
        if ( c->length != 0 && c->nums[c->length-1]==0 )
        {
            c->length -= (c->length/c->length) ; 
        }
    }    

}


// fucking hell .
// fuck this shit 
// TODO : this is NOT bug-free !!!!!!!!!!!!! 
void bigra9m_sub(BigInt *a , BigInt *b , BigInt *c) {
    BigInt temp_a , temp_b ; 
    // printf("calling inits from bigra9m_sub for temp_a %p and temp_b %p \n" , &temp_a , &temp_b) ;     
    // printf("temp_a.nums %p and temp_b.nums %p \n" , temp_a.nums , temp_b.nums) ;     
    bigra9m_inits(&temp_a , &temp_b , NULL) ; 
    
    // printf("just before assigning temp_a.nums %p  temp_b.nums %p\n" , temp_a.nums , temp_b.nums ) ;  
    bigra9m_assign(&temp_a , *a) ; 
    bigra9m_assign(&temp_b , *b) ; 
    
    // printf("just after assigning temp_a.nums %p  temp_b.nums %p\n" , temp_a.nums , temp_b.nums ) ;  
    if (temp_a.length * temp_b.length < 0)
    {
        temp_b.length *= -1 ; 
        bigra9m_add(temp_a , temp_b , c) ;
        // printf("calling clears from bigra9m_sub for temp_a %p and temp_b %p \n" , &temp_a , &temp_b) ;     
        bigra9m_clears(&temp_a , &temp_b , NULL) ; 
        
        return ; 
    } 
    
    // printf("before allocation temp_a.nums %p  temp_b.nums %p\n" , temp_a.nums , temp_b.nums ) ;  
    
    // lets allocate for our result ...
    if (nextPowerOfTwo(MAX(abs(temp_a.length) , abs(temp_b.length))) >  c->capacity  ) {
        c->capacity = nextPowerOfTwo(MAX(abs(temp_a.length) , abs(temp_b.length)))  ;
        BRZ_ALLOCATE_U64(c->nums , c->capacity ) 
        memset(c->nums + abs(c->length)  , 0 , sizeof(uint64_t)*(c->capacity -  abs(c->length) )) ;

    }
    
    c->length = 1 ; 
    // printf("this : ?\n") ;
    // printf("before basic subtraction temp_a.nums %p  temp_b.nums %p\n" , temp_a.nums , temp_b.nums ) ;  
    if ((!bigra9m_isBiggerThanNum(temp_a , temp_b))  )
    {
        
        c->length = -1 ; 
        // swap 
        
        basic_subtraction(temp_b , temp_a , c) ; 
        
    } else  {
        basic_subtraction(temp_a , temp_b , c) ; 
        
        // c->length = (a.length/a.length) ; 
    }
    // printf("after basic subtraction temp_a.nums %p  temp_b.nums %p\n" , temp_a.nums , temp_b.nums ) ;  
    // printf("after basic subtraction temp_a.nums %p \n" , temp_a.nums ) ;  
    
    // printf("calling clears from bigra9m_sub for temp_a %p and temp_b %p \n" , &temp_a , &temp_b) ;     
    // printf("temp_a.nums %p and temp_b.nums %p \n" , temp_a.nums , temp_b.nums) ;     
    bigra9m_clears(&temp_a , &temp_b , NULL) ; 
    
    
    
    // printf("hi\n") ; ;

    // to actually clean the result and not left it with some useless 0s
    while (!bigra9m_is_clean_lastdigit(*c))
    {
        bigra9m_clean_lastdigit(c) ; 
    }
    
}

