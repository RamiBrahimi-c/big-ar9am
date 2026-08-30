#include "bigra9m.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
 
#define DEBUG_RANDOM_bits 0
#define DEBUG_RANDOM 0
#define DEBUG_RANDOM_PRIME 0
#define DEBUG_RANDOM_PRIME_bits 0
#define DEBUG_RANDOM_PRIME_bits2 0


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


    int high_limb_index = abs(max.length) - 1;

    do
    {
        
        a->nums[high_limb_index] = getRandomU64_t(max.nums[high_limb_index] + 1) ;  

        for (int i = high_limb_index - 1; i >= 0 ; i--)
        {
            if (bigra9m_isBiggerThanNum(*a , max))
            {
                break; 
                
            } else {
                a->nums[i] = getRandomU64_t(BASE) ; 
                
            }
            
            
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
    
    bigra9m_clears(&num , &divisor , &max ,&Bits , &temp , &temp2 , NULL) ; 
}


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


    int high_limb_index = abs(high->length) - 1;
    
    do
    {

        a->nums[high_limb_index] = getRandomU64_t(high->nums[high_limb_index] + 1) ;  

        for (int i = high_limb_index - 1; i >= 0 ; i--)
        {
            if (bigra9m_isBiggerThanNum(*a , *high))
            {
                break; 
                
            } else {
                a->nums[i] = getRandomU64_t(BASE) ; 
                
            }
            
            
        }

        printf("candidate : ") ; 
        bigra9m_print(*a) ; 
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


int generate_prime_bigra9m(BigInt *a , BigInt *high) {


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


int generate_prime_bigra9m2(BigInt *a , int bits) {


    do
    {
        setrandom_bigra9m(a , bits) ; 
            
        
        #if DEBUG_RANDOM_PRIME_bits
        printf("candidate is even ?: %d \n" , bigra9m_isEven(a)) ; 
        bigra9m_print(*a) ; 
        #endif
        
    } while (bigra9m_isEven(a) ||  bigra9m_miller_rabin(*a) == 0);
    
    #if DEBUG_RANDOM_PRIME_bits
        printf("is prime ? : %d \n" , bigra9m_miller_rabin(*a)) ; 
    #endif
}


#define LIMB_BITS 64
int generate_prime_bigra9m3(BigInt *a , int bits) {

    int candidates_num = 0 ; 
    do
    {
        setrandom_bigra9m(a , bits) ; 
        
        int limb_index = (bits - 1) / LIMB_BITS;
        int bit_position = (bits - 1) % LIMB_BITS;
        
        a->nums[0] |= 0x1 ; 
        a->nums[limb_index] |= (1u << bit_position);
        
        // printf("index : %d \n" , limb_index) ; 
        // printf("bit position : %d \n" , bit_position) ; 
        
        #if DEBUG_RANDOM_PRIME_bits2
        printf("candidate is even ?: %d \n" , bigra9m_isEven(a)) ; 
        bigra9m_print(*a) ; 
        #endif

        candidates_num++ ; 
    
    } while (  bigra9m_miller_rabin(*a) == 0);

    printf("we tested : %d \n" , candidates_num) ; 
    #if DEBUG_RANDOM_PRIME_bits2
        printf("is prime ? : %d \n" , bigra9m_miller_rabin(*a)) ; 
    #endif
}