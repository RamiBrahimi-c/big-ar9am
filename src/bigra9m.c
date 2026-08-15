#include "../include/bigra9m.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include <string.h>
#if 1
    #define DEBUG
#endif

#define DEBUG_KNUTHS 0


// NOTE : not configured yet with dynammic approach


/* TODO : actually you need to fix bigra9m_mul cuz each time we need to initilize it before we call it !!!!!!!!!!!!!!!*/ 

static int bigra9m_is_clean_lastdigit(BigInt a) {
    if (a.length == 0)
        return 1 ; 
    return a.nums[abs(a.length)-1] != 0  ;
}
static void bigra9m_clean_lastdigit(BigInt *a) {
    if (a->length==0)
    {
        return ; 
    }
    
    if (a != NULL && a->nums[abs(a->length)-1] ==0)
    {
        if (a->length > 0)
        {
            a->length-- ; 
        } else {
            a->length++ ; 

        }
        
    }
    
} 















#include <time.h>
#include <math.h>








#if 0
int main(int argc , char **argv) {

    // BigInt ccc , rrrr ; 
    // bigra9m_init(&ccc ) ; 
    // bigra9m_init( &rrrr) ; 

    // bigra9m_assign_str(&ccc , "1020") ; 

    // bigra9m_mul_uint64(ccc , 5 , &rrrr) ; 

    // bigra9m_print(rrrr) ;

    // exit(0) ; 252493142
    printf("argc : %d\n" , argc) ;
    for (size_t i = 0; i < argc; i++)
    {
        printf("%s\n" , argv[i]) ; 
    }
     
    /* BigRa9m U , V  , Q , R;
    bigra9m_init(&U) ; 
    bigra9m_init(&V) ; 
    bigra9m_init(&Q) ; 
    bigra9m_init(&R) ; 

    bigra9m_assign_str(&U , "252493142") ; 
    bigra9m_assign_str(&V , "13220") ; 
    // bigra9m_print()
    // bigra9m_sub(U , V , &Q ) ; 
    // knuths_algorithm_d(U , V , &Q , &R) ; 

    printf("final result : ") ; 
    bigra9m_print(Q) ; 
    printf("final reminder : ") ; 
    bigra9m_print(R) ; 

    
    exit(EXIT_SUCCESS)  ; 
 */


    BigInt p_big ;
    bigra9m_init(&p_big) ;
    uint64_t p = 29 ; 
    bigra9m_assign_uint64_t(&p_big , p) ;  
    if (argc > 1)
    {
        p = atoi(argv[1]) ; 
        bigra9m_assign_str(&p_big , argv[1]) ; 
    }
    printf("testing on : ") ; 
    bigra9m_print(p_big) ; 

    int result2 = bigra9m_fermat_primality_test(p_big) ; 
    printf("ending bigra9m\n\n\n");

    int result = fermat_primality_test_uint64(p) ; 
    printf("result = %d\n" , result) ; 
    printf("result2 = %d\n" , result) ; 
    if (result == 0)
    {
        printf("%lu is likely prime\n" , p) ; 
    } else {
        printf("%lu is composite\n" , p) ; 
    }
    
    return 0 ; 
}
#endif