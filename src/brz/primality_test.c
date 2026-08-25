#include "../../include/bigra9m.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define S 40

// TODO : CLEAN THIS MESS OR IM GONNA FIND YOU !!!

// NOTE : configured with dynammic approach ???
#define FERMAT_DEBUG 0

static int fermat_primality_test_uint64(uint64_t p) {
    srand(time(NULL)) ; 
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
        
        bigra9m_pow(&a , &p_min1 , &temp) ; 

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
        bigra9m_assign_uint64_t(&a , rand()  ) ; 

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
            
            bigra9m_modular_exponentiation(&a , &p_min1 , &p , &temp ) ; 
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
static int random_in_range(int min, int max) {
    return min + (rand() % (max - min + 1));
}

#define DEBUG_MILLER_RABIN 0


int bigra9m_miller_rabin(BigInt p ) {
    if (bigra9m_isEven(&p))
    {
        return 0 ; 
    }
    srand(time(NULL)) ; 
    BigInt i , j , inc , inc2 , a , p_min1 , u_min1 , s , temp , z ;
    bigra9m_inits(&i , &j, &inc , &inc2 , &a , &s, &p_min1 , &u_min1 , &z , &temp , NULL ) ;
    
    bigra9m_assign_uint64_t(&s , S) ; 
    bigra9m_assign_uint64_t(&i , 1) ; 
    bigra9m_assign_uint64_t(&j , 1) ; 
    bigra9m_assign_uint64_t(&inc , 0) ; 
    bigra9m_assign_uint64_t(&inc2 , 1) ; 
    bigra9m_assign_uint64_t(&temp , 2) ; 
    bigra9m_sub(&p , &i , &p_min1) ; 
    
    if (bigra9m_isEqualNum(p , i))
    {
        
        bigra9m_clears(&i , &j, &inc , &inc2 , &a , &s, &p_min1 , &u_min1 , &z , &temp , NULL ) ;

        return 0 ; 
    }
    
    
    if (bigra9m_isEqualNum(p , temp))
    {
        
        bigra9m_clears(&i , &j, &inc , &inc2 , &a , &s, &p_min1 , &u_min1 , &z , &temp , NULL ) ;

        return 1 ; 
    }
    


    BigInt u , r  ,res , useless ; 
    bigra9m_inits(&u , &r  , &res , &useless, NULL ) ;
    bigra9m_assign_uint64_t(&u ,0 ) ; 
    bigra9m_assign(&r , p_min1) ; 
    // printf("hi\n") ; 

    bigra9m_mod(r , temp , &res) ; 
    while (bigra9m_is_zero(res))
    {
        bigra9m_div(&r , &temp , &r , &useless) ; 
        
        bigra9m_add_1(u , 1 , &u) ; 
        bigra9m_mod(r , temp , &res) ; 
    }
    #if DEBUG_MILLER_RABIN 
    
    printf("p : ") ; 
    bigra9m_print(p) ; 
    printf("u : ") ; 
    bigra9m_print(u) ; 
    printf("r : ") ; 
    bigra9m_print(r) ; 
    #endif
    // return 0 ; 
    bigra9m_sub(&u , &i , &u_min1) ; 
    bigra9m_assign_uint64_t(&temp , 2) ; 
    #if DEBUG_MILLER_RABIN 
    printf("u - 1 : ") ; 
    bigra9m_print(u_min1) ; 
    #endif

    
    while (bigra9m_isLowerThanNum(i , s))
    {
        bigra9m_assign_uint64_t(&a , rand()  ) ; 

        bigra9m_mod(a , p_min1 , &a ) ;
        // check if a = 0 OR a= 1
        if (bigra9m_isEqualNum(a , inc) || bigra9m_isEqualNum(a , inc2) || bigra9m_is_negative(a ) )
        {
            bigra9m_assign_uint64_t(&a , 2) ; 
        }
        #if DEBUG_MILLER_RABIN 
        
        printf("i : ") ; 
        bigra9m_print(i) ; 
        printf("a : ") ; 
        bigra9m_print(a) ; 
        #endif 
        
        bigra9m_modular_exponentiation(&a , &r , &p , &z ) ; 
        #if DEBUG_MILLER_RABIN 
            printf("z : ") ; 
            bigra9m_print(z) ; 
        #endif 
        
        while (bigra9m_is_negative(z))
        {
            printf("oops\n") ; 
            bigra9m_add(z ,p , &z  ) ; 
            printf("z : ") ; 
            bigra9m_print(z) ; 
            break;
        }
        

        if (!bigra9m_isEqualNum(z , inc2 ) && !bigra9m_isEqualNum(z , p_min1 ) )
        {
            while (bigra9m_isLowerThanNum(j , u_min1))
            {
                bigra9m_modular_exponentiation(&z , &temp , &p , &z ) ; 
                #if DEBUG_MILLER_RABIN 

                printf("========== inside j loop ========== \n") ;
                printf("z : ") ;
                bigra9m_print(z) ;
                #endif
                if (bigra9m_isEqualNum(z , p_min1 ))
                {
                    break;
                }
                
                if (bigra9m_isEqualNum(z , inc2 ))
                {
                    bigra9m_clears(&i , &j, &inc , &inc2 , &a , &s, &p_min1 , &u_min1 , &z , &temp , NULL ) ;
                    bigra9m_clears(&u , &r  , &res , &useless, NULL ) ;

                    return 0 ;
                }
                
                bigra9m_add_1(j , 1 , &j) ; 
            }
            if (!bigra9m_isEqualNum(z , p_min1 ))
            {
                bigra9m_clears(&i , &j, &inc , &inc2 , &a , &s, &p_min1 , &u_min1 , &z , &temp , NULL ) ;
                bigra9m_clears(&u , &r  , &res , &useless, NULL ) ;

                return 0 ;
            }

            
        }
        

        bigra9m_add_1(i , 1 , &i) ; 
    }

    
    bigra9m_clears(&i , &j, &inc , &inc2 , &a , &s, &p_min1 , &u_min1 , &z , &temp , NULL ) ;
    bigra9m_clears(&u , &r  , &res , &useless, NULL ) ;

    return 1 ; 
}

