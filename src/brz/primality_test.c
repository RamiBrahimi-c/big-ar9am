#include "../../include/bigra9m.h"

#define S 10

// NOTE : not configured yet with dynammic approach


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
            return 1 ;
        }
         
    }
    return 0 ; 
    
}

int bigra9m_fermat_primality_test(BigInt p) {
    srand(time(0)) ; 
    
    BigInt i , inc , inc2 , a , p_min1 , s , temp ;
    bigra9m_init(&i) ;
    bigra9m_init(&inc) ;
    bigra9m_init(&inc2) ;
    bigra9m_init(&a) ;
    bigra9m_init(&p_min1) ;

    bigra9m_assign_str(&i , "1") ; 
    bigra9m_assign_str(&inc , "1") ; 
    bigra9m_assign_str(&inc2 , "0") ; 
    // inc2.length = 0 ;
    bigra9m_assign_uint64_t(&s , S) ; 
    bigra9m_sub(p , inc , &p_min1) ; 
    // printf("hi\n");
    // bigra9m_init(&i) ;
    int j = 0 ; 
    while (!bigra9m_isBiggerThanNum(i , s))
    {
        // init a
        // printf("hi\n");
        // bigra9m_assign_uint64_t(&a , 2 ) ; 
        bigra9m_assign_uint64_t(&a , rand() % 100 ) ; 

        bigra9m_mod(a , p_min1 , &a ) ;
        // printf("its not mod\n"); 
        // check if a = 0 OR a= 1
        if (bigra9m_isEqualNum(temp , inc) || bigra9m_isEqualNum(temp , inc2))
        {
            bigra9m_assign_uint64_t(&a , 2) ; 
        }
        
        printf("a : ") ; 
        bigra9m_print(a) ; 
        printf("p min 1: ") ; 
        bigra9m_print(p_min1) ; 
        
        bigra9m_pow(a , p_min1 , &temp) ; 
        printf("temp : \n");
        bigra9m_print(temp);  
        // bigra9m_print(p);  
        bigra9m_mod(temp , p , &temp) ; 
        // printf("its not mod\n"); 


        if (!bigra9m_isEqualNum(temp , inc))
        {
            printf("====================================\n");
            printf("p is composite\n") ; 
            printf("====================================\n");
            return 1 ; 
        }
        bigra9m_add(i , inc , &i) ; 
    }
    printf("====================================\n");
    printf("p could be prime\n") ;     
    printf("====================================\n");
    return 0 ; 

}


