#include <stdio.h>
#include "bigra9m.h"
#include <stdint.h>
#include <stdlib.h>


#define N               10000
#define ITERATIONS_MAX  10000
#define PRECISION       10020

void bigra9m_factorial(BigInt *result , uint64_t max ) {
    BigInt temp2 , temp , num , num2  ;
    bigra9m_inits(&temp2 , &temp , &num , &num2 , NULL)  ;
    
    bigra9m_assign_uint64_t(&temp2 , 1) ; 
    bigra9m_assign_uint64_t(&temp , 1) ; 
    bigra9m_assign_uint64_t(&num , 1) ; 
    bigra9m_assign_uint64_t(&num2 , 1) ; 
    bigra9m_assign_uint64_t(result , 1) ; 
    


    uint64_t f = 1 ; 


    for (size_t i = 1; i < max; i++)
    {

        f = f *i ;
        bigra9m_mul(&num , &num2 , result) ; 
        
        
        bigra9m_assign(&num , *result) ; 
        
        
        bigra9m_add(temp , num2 , &temp2) ;
        bigra9m_assign(&num2 , temp2) ; 
        
        
        
    }

    bigra9m_clears(&temp2 , &temp , &num , &num2 , NULL)  ;

}




int main() {

    BigInt scale , i_big , big_one , big_ten , a , b , c , numerator , denomerator , precision ;
    bigra9m_inits(&scale , &i_big , &big_one , &big_ten, &a , &b , &c , &numerator , &denomerator ,&precision, NULL) ; 


    bigra9m_assign_uint64_t(&big_one , 1 ) ; 
    bigra9m_assign_uint64_t(&big_ten , 10 ) ;

    bigra9m_assign_uint64_t(&precision , PRECISION ) ;

    bigra9m_assign_uint64_t(&a , 0 ) ; 

    bigra9m_pow(&big_ten , &precision , &scale ) ; 


    for (size_t i = 1; i < ITERATIONS_MAX; i++)
    {
        bigra9m_mul(&scale , &big_one , &numerator) ;
        
        bigra9m_factorial(&denomerator , i) ; 

        bigra9m_div2(&numerator , &denomerator , &b) ; 

        bigra9m_add(a , b , &a) ; 

        
    }
    
    printf("final result : ") ; 
    bigra9m_print(a) ; 
    


    bigra9m_clears(&scale , &i_big , &big_one , &big_ten, &a , &b , &c , &numerator , &denomerator ,&precision, NULL) ; 
    return 0 ; 
}