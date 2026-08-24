#include "../../include/bigra9m.h"
#include <stdio.h>
// NOTE : configured with dynammic approach
// NOTE : MORE TESTING

#define POW_DEBUG 0

uint64_t pow_ui64(uint64_t a , uint64_t b) {
    uint64_t r = 1 ;
    for (size_t i = 0; i < b; i++)
    {
        r *= a ; 
    }
    return r ; 
}


// bro this NEEDS MORE investegations
void bigra9m_pow(BigInt *base , BigInt *pow , BigInt *res) {
    BigInt i  , copy ; 
    bigra9m_inits(&i ,&copy , NULL  );
    #if POW_DEBUG 
        printf("base : ") ;
        bigra9m_print(*base) ;  
        printf("pow : ") ; 
        bigra9m_print(*pow) ;  
    #endif
    
    bigra9m_assign_uint64_t(&i , 1);
    bigra9m_assign(&copy , *base);


    if (base == res || pow == res)
    {
        BigInt temp_a , temp_b ;

        bigra9m_init_assign(&temp_a , *base);
        bigra9m_init_assign(&temp_b , *pow);

        while (bigra9m_isStrictlyLowerThanNum(i , temp_b))
        {
            #if POW_DEBUG 
                // printf("==== iteration : %d======\n" , j) ; 
            #endif
            
            bigra9m_mul(&copy , &temp_a , res);
            bigra9m_assign(&copy , *res);
            bigra9m_add_1(i , 1 , &i) ;
        }
        
        bigra9m_clears(&temp_a ,&temp_b , NULL  );

    }
    else
    {
        while (bigra9m_isStrictlyLowerThanNum(i , *pow))
        {
            #if POW_DEBUG 
                // printf("==== iteration : %d======\n" , j) ; 
            #endif
            
            bigra9m_mul(&copy , base , res);
            bigra9m_assign(&copy , *res);
            bigra9m_add_1(i , 1 , &i) ;
        }
    }
    
    
    bigra9m_clears(&i ,&copy , NULL  );
    
}

#include <math.h>
// this shit is not ot when base is 100
static int getbit_bigra9m(BigInt a , int position) {
    int t = floor(log2(BASE)) + 1 ;
    t = 8 ;
    t *= a.length ;
    // printf("===============\n" ) ;  
    printf("t=%d\n" , t) ;  
    // printf("===============\n" ) ;  
    // if (t==0)
    // {
    //     return -1 ; 
    // }
    
    int n  = position / 8 ;
    
    if (position % 8 == 0)
    {
        n-- ; 
    }
    while (n < 0)
    {
        n++ ; 
    }
    

    position =  8 - (position % 8) ; 
    position = (position == 8) ? 0 : position ;

    uint64_t temp = a.nums[n] ;
    int k = 0 ; 
    while (k < position-1)
    {   
        temp >>= 1 ;
        k++ ;  
    }
    return temp & 0b1 ; 
      
}

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MOD_EXPO 0

void modular_exponentiation(BigInt *base , BigInt *exponent , BigInt *modulus, BigInt *res) {
    if (bigra9m_is_negative(*exponent))
    {
        fprintf(stderr , "ERROR : exponent can NOT be negative \n") ;
        return ; 
    }

    BigInt r ,reminder , coefficient ,  temp , temp_2;
    bigra9m_init_assign(&temp , *exponent) ; 
    bigra9m_inits(&temp_2 , &reminder , &coefficient , NULL ) ; 

    bigra9m_assign_uint64_t(&temp_2 , 2) ; 
    bigra9m_init_assign(&r , *base) ; 

    #if DEBUG_MOD_EXPO
    printf("base : ") ; 
    bigra9m_print(*base) ; 
    printf("expo : ") ; 
    bigra9m_print(*exponent) ; 
    #endif
    // i lowkey knew log2 was good idea to calculate num of bits in a number and google just confirmed it
    int t = floor(log2(BASE)) + 1 ;
    // int t = 8 ;
    t *= exponent->length ; 
    // t = 8 ; 
    
    uchar_t *buffer = malloc(sizeof(uchar_t) * t) ; 
    if (buffer == NULL)
    {
        fprintf(stderr ,"ERROR : malloc failed wth\n" ) ;
        abort() ; // gmp style uhuh
    }
    
    int actual_len = 0 ; 
    // lets calculate the bits first
    for (size_t i = 0; i < t; i++)
    {
        buffer[i] = 0 ; 
        bigra9m_div(&temp , &temp_2 , &coefficient , &reminder ) ; 
        bigra9m_assign(&temp , coefficient ) ;
        if (reminder.length > 0)
        {
            buffer[i] = reminder.nums[0] ; 
        }
        if (bigra9m_is_zero(coefficient))
        {
            break;
        }
        actual_len++ ; 
        
    }
    


    for (int i = actual_len - 1; i >= 0; i--)
    {
        int bit = buffer[i];
        // bigra9m_div(&temp , &temp_2 , &coefficient , &reminder ) ; 
        
        #if DEBUG_MOD_EXPO
            printf("============= i = %d ================\n" , i) ; 
            printf("divedend : ") ; 
            bigra9m_print(temp) ; 
            printf("divisor : ") ; 
            bigra9m_print(temp_2) ; 
            printf("coeff : ") ; 
            bigra9m_print(coefficient) ; 
            printf("reminder : ") ; 
            bigra9m_print(reminder) ;
        #endif
        

        bigra9m_mul(&r , &r , &r) ; 
        bigra9m_mod(r , *modulus , &r) ;
        #if DEBUG_MOD_EXPO
            printf("r = \n"  ) ;
            bigra9m_print(r) ;  
            printf("bit = %d\n" , bit ) ; 

        #endif
        // printf("for i=%d we have getbit_bigra9m(*exponent , i)= %d\n" , i , getbit_bigra9m(*exponent , i)) ; 
        if (bit==1)
        {
            // printf("enter\n") ; 
            bigra9m_mul(&r , base , &r) ; 
            #if DEBUG_MOD_EXPO
            printf("bit is 1  \n"  ) ;
            printf("r = \n"  ) ;
            bigra9m_print(r) ;  
            #endif            
            bigra9m_mod(r , *modulus , &r) ;
        #if DEBUG_MOD_EXPO
            printf("r = \n"  ) ;
            bigra9m_print(r) ;  

        #endif            
        }
        
    }
    
    #if DEBUG_MOD_EXPO
        printf("modulus : ") ; 
        bigra9m_print(*modulus) ; 
        printf("r : ") ; 
        bigra9m_print(r) ; 
    #endif    
    bigra9m_assign(res , r) ;     

    bigra9m_clears(&r , &temp , NULL) ; 
} 

