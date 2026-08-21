#include "../../include/bigra9m.h"

#define S 10

// TODO : CLEAN THIS MESS OR IM GONNA FIND YOU !!!

// NOTE : configured with dynammic approach ???
#define FERMAT_DEBUG 0

static int fermat_primality_test_uint64(uint64_t p) {
    srand(time(0)) ; 
    size_t s = S , a;
    for (size_t i = 0; i < s; i++)
    {
        a = (rand() % (p-1))  ;
        a = (a == 0 || a==1) ? 2 : a ;
        // printf("testing with a=%ld  p-1=%ld \tpow(a , p-1) %% p =%lu \n" , a , p-1   ,( pow_ui64(a , p-1) % p )  ) ; 
        // printf("pow(a , p-1):%lu  \n" ,   pow_ui64(a , p-1)   ) ; 
        if ( pow_ui64(a , p-1) % p != 1)
        {
            return 0 ;
        }
         
    }
    return 1 ; 
    
}

int bigra9m_fermat_primality_test(BigInt p) {
    #if FERMAT_DEBUG
    #endif

    srand(time(0)) ; 
    BigInt i , inc , inc2 , a , p_min1 , s , temp ;
    bigra9m_inits(&i , &inc , &inc2 , &a , &s, &p_min1 , &temp , NULL ) ;
    
    bigra9m_assign_uint64_t(&i , 1) ; 
    bigra9m_assign_uint64_t(&inc , 1) ; 
    bigra9m_assign_uint64_t(&inc2 , 0) ; 
    // inc2.length = 0 ;
    bigra9m_assign_uint64_t(&s , S) ; 
    #if FERMAT_DEBUG
        printf("p : ") ; 
        bigra9m_print(p) ; 
        printf("inc  : ") ; 
        bigra9m_print(inc) ; 
        printf("p - 1  : ") ; 
        bigra9m_print(p_min1) ; 
    #endif
    bigra9m_sub(&p , &inc , &p_min1) ; 
    
    #if FERMAT_DEBUG
        printf("p : ") ; 
        bigra9m_print(p) ; 
        printf("inc  : ") ; 
        bigra9m_print(inc) ; 
        printf("p - 1  : ") ; 
        bigra9m_print(p_min1) ; 
    #endif


    // printf("hi\n");
    // bigra9m_init(&i) ;
    int j = 0 ; 
    while (!bigra9m_isBiggerThanNum(i , s))
    {
        #if FERMAT_DEBUG
            printf("iteration : ") ;
            bigra9m_print(i) ; 
        #endif
        // init a
        // printf("hi\n");
        // bigra9m_assign_uint64_t(&a , 2 ) ; 
        bigra9m_assign_uint64_t(&a , rand() % 1000 ) ; 

        bigra9m_mod(a , p_min1 , &a ) ;
        // check if a = 0 OR a= 1
        if (bigra9m_isEqualNum(a , inc) || bigra9m_isEqualNum(a , inc2))
        {
            bigra9m_assign_uint64_t(&a , 2) ; 
        }
        #if FERMAT_DEBUG
            printf("a : ") ; 
            bigra9m_print(a) ; 
            printf("p min 1: ") ; 
            bigra9m_print(p_min1) ; 
        #endif
        
        bigra9m_pow(a , p_min1 , &temp) ; 

        #if FERMAT_DEBUG
        printf("temp : \n");
        bigra9m_print(temp);  
        #endif
        // bigra9m_print(p);  
        bigra9m_mod(temp , p , &temp) ; 
        // printf("its not mod\n"); 
        #if FERMAT_DEBUG
        printf("temp : \n");
        bigra9m_print(temp);  
        #endif
        
        
        if (!bigra9m_isEqualNum(temp , inc))
        {
            #if FERMAT_DEBUG
            printf("====================================\n");
            printf("p is composite\n") ; 
            printf("====================================\n");
            #endif
            return 0 ; 
        }
        bigra9m_add_1(i , 1 , &i) ; 
    }
    #if FERMAT_DEBUG
        printf("====================================\n");
        printf("p could be prime\n") ;     
        printf("====================================\n");
    #endif
    bigra9m_clears(&i , &inc , &inc2  , &s , &temp, &a , &p_min1 , NULL ) ;

    return 1 ; 

}


int bigra9m_fermat_primality_test_fast(BigInt p) {
    #if FERMAT_DEBUG
    #endif

    srand(time(0)) ; 
    BigInt i , inc , inc2 , a , p_min1 , s , temp ;
    bigra9m_inits(&i , &inc , &inc2 , &a , &s, &p_min1 , &temp , NULL ) ;
    
    bigra9m_assign_uint64_t(&i , 1) ; 
    bigra9m_assign_uint64_t(&inc , 1) ; 
    bigra9m_assign_uint64_t(&inc2 , 0) ; 
    // inc2.length = 0 ;
    bigra9m_assign_uint64_t(&s , S) ; 
    #if FERMAT_DEBUG
        printf("p : ") ; 
        bigra9m_print(p) ; 
        printf("inc  : ") ; 
        bigra9m_print(inc) ; 
        printf("p - 1  : ") ; 
        bigra9m_print(p_min1) ; 
    #endif
    bigra9m_sub(&p , &inc , &p_min1) ; 
    
    #if FERMAT_DEBUG
        printf("p : ") ; 
        bigra9m_print(p) ; 
        printf("inc  : ") ; 
        bigra9m_print(inc) ; 
        printf("p - 1  : ") ; 
        bigra9m_print(p_min1) ; 
    #endif


    // printf("hi\n");
    // bigra9m_init(&i) ;
    int j = 0 ; 
    while (!bigra9m_isBiggerThanNum(i , s))
    {
        #if FERMAT_DEBUG
            printf("iteration : ") ;
            bigra9m_print(i) ; 
        #endif
        // init a
        // printf("hi\n");
        // bigra9m_assign_uint64_t(&a , 2 ) ; 
        bigra9m_assign_uint64_t(&a , rand() % 1000 ) ; 

        bigra9m_mod(a , p_min1 , &a ) ;
        // check if a = 0 OR a= 1
        if (bigra9m_isEqualNum(a , inc) || bigra9m_isEqualNum(a , inc2))
        {
            bigra9m_assign_uint64_t(&a , 2) ; 
        }
        #if FERMAT_DEBUG
            printf("a : ") ; 
            bigra9m_print(a) ; 
            printf("p min 1: ") ; 
            bigra9m_print(p_min1) ; 
        #endif
            
            modular_exponentiation(&a , &p_min1 , &p , &temp ) ; 
        // bigra9m_pow(a , p_min1 , &temp) ; 
        // bigra9m_mod(temp , p , &temp) ; 

        #if FERMAT_DEBUG
        printf("temp : \n");
        bigra9m_print(temp);  
        #endif
        // bigra9m_print(p);  
        // printf("its not mod\n"); 
        #if FERMAT_DEBUG
        printf("temp : \n");
        bigra9m_print(temp);  
        #endif
        
        
        if (!bigra9m_isEqualNum(temp , inc))
        {
            #if FERMAT_DEBUG
            printf("====================================\n");
            printf("p is composite\n") ; 
            printf("====================================\n");
            #endif
            return 0 ; 
        }
        bigra9m_add_1(i , 1 , &i) ; 
    }
    #if FERMAT_DEBUG
        printf("====================================\n");
        printf("p could be prime\n") ;     
        printf("====================================\n");
    #endif
    bigra9m_clears(&i , &inc , &inc2  , &s , &temp, &a , &p_min1 , NULL ) ;

    return 1 ; 

}


