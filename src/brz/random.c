#include "bigra9m.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
 
#define DEBUG_RANDOM_bits 0


int setrandom_bigra9m(BigInt *a  , int bits)  {
    if (bits < 2)
    {
        fprintf(stderr , "ERROR : bits provided :%d are too low\n" , bits) ; 
        return -1 ; 
    }
    
    
    uchar_t buffer[1024] ; 
    getRandomBytes(buffer , 1024) ;
    #if DEBUG_RANDOM_bits
    printf("log2(BASE) : %d \n" , (int) log2(BASE)) ; 
    #endif
    int max_len = (int) ceil( bits / ( log2(BASE) )  ) ; 
    
    #if DEBUG_RANDOM_bits
    printf("max len calculated : %d \n" , max_len) ; 
    #endif
    if (abs(a->length) < max_len)
    {
        a->capacity = nextPowerOfTwo(max_len) ;
        
        BRZ_ALLOCATE_U64(a->nums , a->capacity)
        memset(a->nums + abs(a->length), 0x0 , sizeof(uint64_t)*(a->capacity - abs(a->length))) ; 

    }
    if (max_len > 100)
    a->length = max_len -10;
    else 
    a->length = max_len ;
    #if DEBUG_RANDOM_bits    
    printf("a->len : %d\n" , a->length) ; 
    #endif
    
    BigInt num , divisor , max , Bits , temp, temp2; 
    bigra9m_inits(&num , &divisor , &max ,&Bits , &temp , &temp2 , NULL) ; 
    
    bigra9m_assign_uint64_t(&Bits , bits) ; 
    bigra9m_assign_uint64_t(&temp , 2) ; 
    bigra9m_assign_uint64_t(&temp2 , 1) ; 
    #if DEBUG_RANDOM_bits    
    printf("here\n") ; 
    
    printf("temp : ") ; 
    bigra9m_print(temp) ; 
    printf("Bits : ") ; 
    bigra9m_print(Bits) ; 
    #endif
    bigra9m_pow( &temp , &Bits , &Bits ) ; 
    
    #if DEBUG_RANDOM_bits
    printf("here after pow\n") ;
    
    printf("Bits : ") ; 
    bigra9m_print(Bits) ; 
    #endif
    
    bigra9m_assign( &max , Bits ) ; 
    // bigra9m_sub(&Bits , &temp2 , &max) ; 
    #if DEBUG_RANDOM_bits
    printf("max.len : %d\n" , max.length) ; 
    printf("max : ") ; 
    bigra9m_print(max) ; 
    #endif
    do
    {
        for (int i = 0; i < abs(a->length); i++)
        {
            a->nums[i] = getRandomU64_t(BASE) ; 
        }
    
        while (!bigra9m_is_clean_lastdigit(*a))
        {
            bigra9m_clean_lastdigit(a) ; 
        }
        #if DEBUG_RANDOM_bits            
        printf("candidate : ") ; 
        bigra9m_print(*a) ;
        #endif
        // exit(EXIT_FAILURE ) ;  
    } while (bigra9m_isBiggerThanNum(*a , max));
    
    #if DEBUG_RANDOM_bits            
    printf("generated a : ") ; 
    bigra9m_print(*a) ; 
    #endif
    bigra9m_clears(&num , &divisor , NULL) ; 
    // bigra9m_clear(&num) ; 
}

#define DEBUG_RANDOM 0

int setrandom_bigra9m2(BigInt *a , BigInt *high )  {
    if (bigra9m_is_negative(*high))
    {
        fprintf(stderr , "ERROR : high cant be negative\n") ; 
        return -1 ; 
    }
    
    
    uchar_t buffer[1024] ; 
    // getRandomBytes(buffer , 1024) ;
    
    if (abs(a->length) < abs(high->length))
    {
        a->capacity = (high->capacity) ;
        
        BRZ_ALLOCATE_U64(a->nums , a->capacity)
        memset(a->nums + abs(a->length), 0x0 , sizeof(uint64_t)*(a->capacity - abs(a->length))) ; 

    }
    a->length = high->length ; 
    #if DEBUG_RANDOM
    printf("a.len : %d\n" , a->length) ; 
    #endif
    
    do
    {
        for (int i = 0; i < abs(a->length); i++)
        {
            a->nums[i] = getRandomU64_t(BASE) ; 
        }
    } while (bigra9m_isBiggerThanNum(*a , *high));
    
    while (!bigra9m_is_clean_lastdigit(*a))
    {
        bigra9m_clean_lastdigit(a) ; 
    }
    
    
    // BigInt num , divisor , max , Bits , temp, temp2; 
    // bigra9m_inits(&num , &divisor , &max ,&Bits , &temp , NULL) ; 
    // bigra9m_clears(&num , &divisor , NULL) ; 
    // bigra9m_clear(&num) ; 
}

#define DEBUG_RANDOM_PRIME 0


int generate_prime_bigra9m2(BigInt *a , BigInt *high) {


    do
    {
        setrandom_bigra9m2(a , high) ; 
        #if DEBUG_RANDOM_PRIME
        printf("candidate : ") ; 
        bigra9m_print(*a) ; 
        #endif
    } while (bigra9m_isEven(a) || bigra9m_miller_rabin(*a) == 0);
    
    #if DEBUG_RANDOM_PRIME
    printf("is prime ? : %d \n" , bigra9m_miller_rabin(*a)) ; 
    #endif

}

#define DEBUG_RANDOM_PRIME_bits 1

int generate_prime_bigra9m(BigInt *a , int bits) {


    do
    {
        do
        {
            setrandom_bigra9m(a , bits) ; 
            /* code */
        } while (bigra9m_isEven(a));
        
        #if DEBUG_RANDOM_PRIME_bits
        printf("candidate is even ?: %d \n" , bigra9m_isEven(a)) ; 
        bigra9m_print(*a) ; 
        #endif
        
    } while ( bigra9m_miller_rabin(*a) == 0);
    
    #if DEBUG_RANDOM_PRIME_bits
        printf("is prime ? : %d \n" , bigra9m_miller_rabin(*a)) ; 
    #endif
}