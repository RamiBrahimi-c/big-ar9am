#include <stdio.h>
#include <big-ar9am/bigra9m.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


long double factd(long double a) {

    long double k = 1 ; 
    for (size_t i = 2; i <= a; i++)
    {
        k *= i ; 
    }
    
    return k ; 
}

long double func() {
    
    long double a = 2 , b ;

    for (size_t i = 2; i <= 100; i++)
    {
        a +=  (1 / factd(i)) ; 
    }

    return a ; 
}   


#define N 1000

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
        
        
        // bigra9m_print(result);
        bigra9m_assign(&num , *result) ; 
        
        
        bigra9m_add(temp , num2 , &temp2) ;
        bigra9m_assign(&num2 , temp2) ; 
        
        
        
    }

    bigra9m_clears(&temp2 , &temp , &num , &num2 , NULL)  ;

}




int main() {

    // printf("%.9Lf \n" , func()) ;


    BigInt scale , i_big , big_one , big_ten , a , b , c , numerator , denomerator , precision ;
    bigra9m_inits(&scale , &i_big , &big_one , &big_ten, &a , &b , &c , &numerator , &denomerator ,&precision, NULL) ; 


    bigra9m_assign_uint64_t(&big_one , 1 ) ; 
    bigra9m_assign_uint64_t(&big_ten , 10 ) ;

    bigra9m_assign_uint64_t(&precision , N + 10 ) ;

    bigra9m_assign_uint64_t(&a , 0 ) ; 

    bigra9m_pow(&big_ten , &precision , &scale ) ; 


    for (size_t i = 2; i < N; i++)
    {
        bigra9m_mul(&scale , &big_one , &numerator) ;
        
        bigra9m_factorial(&denomerator , i) ; 

        bigra9m_div2(&numerator , &denomerator , &b) ; 

        bigra9m_add(a , b , &a) ; 

        
    }
    
    printf("final result : ") ; 
    bigra9m_print(a) ; 
    
    printf("%d digit btw \n" , a.length) ; 


/*

*/

    bigra9m_clears(&scale , &a , &b , &c , NULL) ; 
    return 0 ; 
}