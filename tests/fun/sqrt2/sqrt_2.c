#include <stdio.h>
#include <big-ar9am/bigra9m.h>
#include <stdint.h>
#include <stdlib.h>


/* 
    for 10000 digit

    #define N 50
    #define LOOP_TIMES 50000
    #define PRECISION 10000
 
*/

#define N 50
#define LOOP_TIMES 35000
#define PRECISION 10000


int main() {

    BigInt scale , i_big , big_one , big_two , big_ten , a , b , c , numerator , denomerator , precision , precision_lite ;
    bigra9m_inits(&scale , &i_big , &big_one , &big_two , &big_ten, &a , &b , &c , &numerator , &denomerator ,&precision , &precision_lite , NULL) ; 
    BigInt temp_1 , temp_2 , temp_3 ; 
    bigra9m_inits(&temp_1 , &temp_2 , &temp_3 , NULL) ; 


    bigra9m_assign_uint64_t(&big_one , 1 ) ; 
    bigra9m_assign_uint64_t(&big_two , 2 ) ; 
    bigra9m_assign_uint64_t(&big_ten , 10 ) ;

    bigra9m_assign_uint64_t(&precision , PRECISION + 10 ) ;

    // our first guess here : 
    bigra9m_assign_uint64_t(&c , 15 ) ; 

    bigra9m_assign_uint64_t(&b , 0 ) ; 
    bigra9m_assign_uint64_t(&a , 0 ) ; 

    bigra9m_pow(&big_ten , &precision , &scale ) ; 
    
    bigra9m_mul(&scale , &scale , &precision_lite ) ; 
    
    bigra9m_mul(&precision_lite , &c , &c ) ; 



    for (size_t i = 0; i < LOOP_TIMES; i++)
    {
        bigra9m_assign(&a, c) ; 

        
        bigra9m_mul(&big_two, &precision_lite, &numerator) ; 
        
        bigra9m_div2(&numerator, &c , &b ) ;

        bigra9m_add(a, b, &c) ; 
        
        
        bigra9m_div2(&c, &big_two , &c ) ;



    }
    
    printf(" \n\n\nfinal result : ") ; 
    // bigra9m_print(c) ; 
    bigra9m_print(c) ; 
    
    printf("%d digit btw in (2^32) base \n" , c.length) ; 


    bigra9m_clears(&scale , &a , &b , &c , NULL) ; 
    return 0 ; 
}