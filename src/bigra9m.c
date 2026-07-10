#include "../include/bigra9m.h"
#include <stdio.h>
#include <stdlib.h>

void bigra9m_assign(BigInt *a , BigInt b  ) {

    memcpy(a , &b , sizeof(BigInt)) ; 
    // a->length = b.length ; 
}


void bigra9m_init(BigInt *a) {
    a->length = 1 ;
    memset(a->nums , 0 , MAX_LEN*sizeof(uint64_t)) ;
}



void bigra9m_assign_str(BigInt *a , uchar_t *num_str) {
    
    size_t len = strlen(num_str) ;

    size_t j = 0 ;
    if (len % 2 ==0)
    {
        j = len/2 ;
        a->length = j ; 
        j-- ; 
        for (size_t i = 0; i < len; i+=2)
        {
            uchar_t buffer[2] ; 
            memcpy(buffer , num_str + i , sizeof(uchar_t)*2) ;
            a->nums[j] = atoi(buffer ) ;
            j-- ; 
        }
        
    } else {
        j = len/2 +1;;
        a->length = j ; 
        j-- ; 
        uchar_t buffer[2] ; 
        buffer[1] = 0  ; 
        memcpy(buffer   , num_str  , sizeof(uchar_t)) ;
        a->nums[j] = atoi(buffer) ;
        j-- ; 
        
        for (size_t i = 1; i < len; i+=2)
        {
            uchar_t buffer[2] ; 
            memcpy(buffer , num_str + i , sizeof(uchar_t)*2) ;
            a->nums[j] = atoi(buffer ) ;
            j-- ; 
        }        
    }
    
}


void bigra9m_print(BigInt number) {
    // printf("length : (%ld) ||\t" , number.length) ; 
    for (size_t i = 0 ; i < number.length ; i++)
    {
        uchar_t a = number.nums[number.length-i-1] ; 
        if (a==0 && i == 0)
        {
            printf("0") ; 
        }
        else if (a < 10 && number.length > 1 && i != 0)
        {
            printf("0%d" , a) ; 
        } else if (a ==0 ) {
            printf("00") ; 

        } else {
            printf("%d" , a) ; 

        }
        
        
    }
    printf("\n") ; 
    
}


void bigra9m_add(BigInt a , BigInt b , BigInt *c ) {

    // lets assume same length for a and b
    if (a.length == b.length)
    {
        uint64_t overflow = 0 ;
        for (size_t i = 0; i < a.length; i++)
        {
            uint64_t result = a.nums[i] + b.nums[i] + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                // printf("hi\n") ; 
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            
        }

        c->length = a.length  ; 
        if (overflow != 0)
        {
            c->nums[a.length] = overflow ; 
            c->length = a.length + 1 ; 
        }
        
    } else {

        size_t min_len = (a.length < b.length) ? a.length : b.length ;
        size_t max_len ;
        BigInt *umm ;
        if (a.length > b.length)
        {
            max_len = a.length ;
            umm = &a ; 
        } else {
            max_len = b.length ;
            umm = &b ; 

        }
        

        uint64_t overflow = 0 ;
        for (size_t i = 0; i < min_len; i++)
        {
            uint64_t result = a.nums[i] + b.nums[i] + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                // printf("hi\n") ; 
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0  ;
            }
            
        }
        // overflow = 0 ; 
        for (size_t i = min_len; i < max_len ; i++)
        {
            uint64_t result = umm->nums[i]  + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                // printf("hi\n") ; 
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            
        }

        c->length = umm->length  ; 
        if (overflow != 0)
        {
            c->nums[umm->length] = overflow ; 
            c->length = umm->length + 1 ; 
        }
        


        // printf("ERROR : NOT IMPLEMENTED\n") ; 
        // exit(EXIT_FAILURE ); 
    }
    

}
