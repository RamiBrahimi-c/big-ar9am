#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>



#define BASE 100
#define MAX_LEN 10000



typedef unsigned char uchar_t ; 
typedef struct BigInt BigInt ; 


struct BigInt
{   
    uint64_t nums[MAX_LEN] ; 
    size_t length ; 
};


void bigra9m_init() {
    
}

void bigra9m_print(BigInt number) {
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


void bigra9m_assign(BigInt *a , BigInt b  ) {

    memcpy(a , &b , sizeof(BigInt)) ; 
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

void bigra9m_mul(BigInt a , BigInt b , BigInt *c) {

}



int main() {


    printf("hiii big ar9am >-<\n") ; 


    uint32_t a = 0 ; 
    uint32_t b = 1 ; 
    uint32_t r ; 

    uint64_t a2 = 0 ; 
    uint64_t b2 = 1 ; 
    uint64_t r2 ; 


    BigInt num ;
    num.nums[0] = 0 ; 
    num.length = 1 ; 

    BigInt num2 ;
    num2.nums[0] = 1 ; 
    num2.length = 1 ; 

    BigInt num3 ;
    num3.nums[0] = 0 ; 
    num3.length = 0 ; 

    // printf("num : \n") ; 
    // bigra9m_print(num) ; 

    // printf("num2 : \n") ; 
    // bigra9m_print(num2) ; 


    // bigra9m_add(num , num2 , &num3) ; 

    // printf("num3 : \n") ; 
    // bigra9m_print(num3) ; 

    // exit(EXIT_SUCCESS) ; 

    // printf("=======================================================\n");
    // printf("uint32_t\tuint64_t\tbig ra9m\n") ; 
    // printf("=======================================================\n");
    
    for (size_t i = 2; i < 100; i++)
    {
        r = a + b ;
        r2 = a2 + b2 ;
        bigra9m_add(num , num2 , &num3) ; 
        
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
    




    return 0 ; 
}