#include <stdio.h>
#include "../../../include/bigra9m.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/*
#define N 10000
#define LOOP_TIMES 715


#define LOOP_TIMES_SQRT10005 35000
#define PRECISION_SQRT10005 10000

*/

#define N 10000
#define LOOP_TIMES 715


#define LOOP_TIMES_SQRT10005 35000
#define PRECISION_SQRT10005 10000


#define DEBUG_FLAG 0
#define FACT_DEBUG_FLAG 0



void bigra9m_factorial(BigInt *result , uint64_t max ) {
    
    if (max < 2 ) {
        bigra9m_assign_uint64_t(result, 1) ;
        return;
    }
    
    
    
    
    BigInt temp2 , temp , num , num2  ;
    bigra9m_inits(&temp2 , &temp , &num , &num2 , NULL)  ;
    
    bigra9m_assign_uint64_t(&temp2 , 1) ; 
    bigra9m_assign_uint64_t(&temp , 1) ; 
    bigra9m_assign_uint64_t(&num , 1) ; 
    bigra9m_assign_uint64_t(&num2 , 1) ; 
    bigra9m_assign_uint64_t(result , 1) ; 
    


    uint64_t f = 1 ;
    
    #if FACT_DEBUG_FLAG
        printf("===== fact =======\n") ; 
        printf("%lu\n" , max) ; 
    #endif
    
    
    for (size_t i = 1; i <= max; i++)
    {
        
        f = f *i ;
        bigra9m_mul(&num , &num2 , result) ; 
        
        
        bigra9m_assign(&num , *result) ; 
        
        
        bigra9m_add(temp , num2 , &temp2) ;
        bigra9m_assign(&num2 , temp2) ; 
        
        
        
    }

    #if FACT_DEBUG_FLAG
        
        printf("result : ") ; 
        bigra9m_print(*result) ; 
        printf("===== fact end =======\n") ; 
    #endif

    bigra9m_clears(&temp2 , &temp , &num , &num2 , NULL)  ;

}


void bigra9m_get10005sqrt(BigRa9m *result) {
    BigInt scale , i_big , big_one , big_two , big_ten , input , a , b , c , numerator  , precision , precision_lite ;
    bigra9m_inits(&scale , &i_big , &big_one , &big_two , &big_ten, &a , &b , &c , &numerator  ,&precision , &precision_lite , NULL) ; 
    bigra9m_inits( &input, NULL) ; 
    
    
    bigra9m_assign_uint64_t(&big_one , 1 ) ; 
    bigra9m_assign_uint64_t(&big_two , 2 ) ; 
    bigra9m_assign_uint64_t(&big_ten , 10 ) ;
    bigra9m_assign_uint64_t(&input , 10005 ) ;

    bigra9m_assign_uint64_t(&precision , PRECISION_SQRT10005 + 10 ) ;

    // our first guess here : 
    bigra9m_assign_uint64_t(&c , 15 ) ; 
    
    bigra9m_assign_uint64_t(&b , 0 ) ; 
    bigra9m_assign_uint64_t(&a , 0 ) ; 

    bigra9m_pow(&big_ten , &precision , &scale ) ; 
    
    bigra9m_mul(&scale , &scale , &precision_lite ) ; 
    
    bigra9m_mul(&precision_lite , &c , &c ) ; 

    
    
    for (size_t i = 0; i < LOOP_TIMES_SQRT10005; i++)
    {
        bigra9m_assign(&a, c) ; 
        
        
        bigra9m_mul(&input, &precision_lite, &numerator) ; 
        
        bigra9m_div2(&numerator, &c , &b ) ;
        
        bigra9m_add(a, b, &c) ; 
        
        
        bigra9m_div2(&c, &big_two , &c ) ;
        
        
        
    }
    
    bigra9m_assign(result, c) ; 
    // printf(" \n\n\nsqrt(10005) : ") ; 
    // bigra9m_print(c) ; 
    // bigra9m_print(*result) ; 
    // printf(" \n\n\nsqrt(10005) : ") ; 
    // bigra9m_print(c) ; 
    
    bigra9m_clears(&scale , &i_big , &big_one , &big_two , &big_ten, &a , &b , &c , &numerator ,&precision , &precision_lite , NULL) ; 
    bigra9m_clears( &input, NULL) ; 


    
}


int main() {



    BigInt scale , i_big , big_minus_one , big_one , big_two , big_ten , a , b , c , numerator , denomerator , precision  ;
    bigra9m_inits(&scale , &i_big , &big_minus_one , &big_one , &big_two , &big_ten, &a , &b , &c , &numerator , &denomerator ,&precision  , NULL) ; 

    BigInt temp_1 , temp_2 , temp_3 ; 
    bigra9m_inits(&temp_1 , &temp_2 , &temp_3 , NULL) ; 

    BigInt first_const , second_const , third_const , fourth_const , fifth_const ; 
    bigra9m_inits(&first_const , &second_const , &third_const  , &fourth_const , &fifth_const , NULL) ; 

    BigInt big_six  , big_three; 
    bigra9m_inits(&big_six , &big_three,  NULL) ; 

    BigInt term  , sum; 
    bigra9m_inits(&term , &sum,  NULL) ; 



    bigra9m_assign_uint64_t(&first_const    , 545140134 ) ; 
    bigra9m_assign_uint64_t(&second_const   , 13591409  ) ; 
    bigra9m_assign_uint64_t(&third_const    , 640320    ) ; 


    bigra9m_assign_str(&fourth_const    , "4270934400" ) ; 
    
    bigra9m_get10005sqrt(&fifth_const) ; 
    printf("INFO : done setting %d digit of fifth constant (square root of 10005)\n" , PRECISION_SQRT10005 ) ; 

    bigra9m_assign_uint64_t(&big_one    , 1 ) ; 
    bigra9m_assign_uint64_t(&big_two    , 2 ) ; 
    bigra9m_assign_uint64_t(&big_three  , 3 ) ; 
    bigra9m_assign_uint64_t(&big_six    , 6 ) ; 
    bigra9m_assign_uint64_t(&big_ten    , 10 ) ;

    
    bigra9m_assign_uint64_t(&a , 0 ) ; 
    bigra9m_assign_uint64_t(&b , 0 ) ; 
    bigra9m_assign_uint64_t(&c , 0 ) ; 
    
    bigra9m_assign_str(&big_minus_one, "-1") ; 
    
    
    bigra9m_assign_uint64_t(&term , 0 ) ; 
    bigra9m_assign_uint64_t(&sum , 0 ) ; 


    bigra9m_assign_uint64_t(&precision , N + 10 ) ;


    bigra9m_pow(&big_ten , &precision , &scale ) ; 
    
    
    // now that constant that is out of the sum and in the denomerator needs to get scaled just as much as the fifth constant 
    bigra9m_mul(&fourth_const, &scale, &fourth_const) ;
    printf("INFO : done setting fourth constant = 4270934400 * 10^%d \n" , N + 10) ; 

    uint64_t j = 1 ; 
    
    for (size_t k = 0; k < LOOP_TIMES; k++)
    {
        
        // setting the numerator : 
        #if DEBUG_FLAG 
        printf("k=%ld\n" , k) ; 
            printf("temp1 : ") ; 
            bigra9m_print(temp_1)  ; 
        #endif

        bigra9m_mul_uint64(&first_const,(uint64_t) k ,&temp_1 ) ;

        #if DEBUG_FLAG 
            printf("temp1 after : ") ; 
            bigra9m_print(temp_1)  ; 
        #endif
       

        
        bigra9m_add(temp_1, second_const, &temp_2) ;  

        #if DEBUG_FLAG 
            printf("temp2 : ") ; 
            bigra9m_print(temp_2)  ; 
        #endif
        
        
        bigra9m_factorial(&temp_1, 6*k) ; 

        #if DEBUG_FLAG 
            printf("factorial(6*k) : ") ; 
            bigra9m_print(temp_1)  ; 
        #endif
        
        
        bigra9m_mul(&temp_1, &temp_2, &temp_1) ; 
        
        if (k % 2 == 1) {
            #if DEBUG_FLAG 
            printf("odd value  k= %ld \n" , k) ; 
            #endif
            
            bigra9m_mul(&temp_1, &big_minus_one, &numerator) ; 
        }
        else {
            #if DEBUG_FLAG 
            
            printf("even value k= %ld \n" , k) ; 
            #endif
            
            bigra9m_assign(&numerator, temp_1) ; 
        }
        // bigra9m_mul(&temp_1, &big_one, &numerator) ; 
        
        bigra9m_mul(&numerator, &scale, &numerator) ; 
    
        #if DEBUG_FLAG 
            printf("final numerator : ") ; 
            bigra9m_print(numerator) ; 
        #endif
        // we got the numerator now , 
        
        // now the denomerator now , 
        bigra9m_factorial(&temp_1,(uint64_t) (3*k)) ; 

        #if DEBUG_FLAG 
            printf("(3*k)! : ") ; 
            bigra9m_print(temp_1) ; 
        #endif

        bigra9m_factorial(&temp_2, k) ; 

        #if DEBUG_FLAG 
            printf("k : ") ; 
            bigra9m_print(temp_2) ; 
        #endif

        bigra9m_pow(&temp_2, &big_three, &temp_3) ; 
        
        #if DEBUG_FLAG 
            printf("(k!)^3 : ") ; 
            bigra9m_print(temp_2) ; 
        #endif


        bigra9m_assign_uint64_t(&temp_2, 3*k) ; 
        // bigra9m_mul_uint64(BigInt *a, uint64_t b, BigInt *c)

        bigra9m_pow(&third_const, &temp_2, &b) ;
        #if DEBUG_FLAG 
            printf("640320^(k*3) : ") ; 
            bigra9m_print(b) ; 
        #endif
        
        // final denomerator
        bigra9m_mul(&temp_1, &b, &denomerator) ; 
        bigra9m_mul(&denomerator, &temp_3, &denomerator) ; 
        
        #if DEBUG_FLAG 
            printf("final denomerator : ") ; 
            bigra9m_print(denomerator) ; 
        #endif
        // we got both numerator AND denomerator


        bigra9m_div2(&numerator, &denomerator, &term) ; 

        
        #if DEBUG_FLAG 
        printf("term : ") ; 
        bigra9m_print(term) ; 
        printf("sum before : ") ; 
        bigra9m_print(sum) ; 
        #endif
        
        bigra9m_add(term, sum, &sum) ; 
        
        #if DEBUG_FLAG 
        printf("sum : ") ; 
        bigra9m_print(sum) ; 
        #endif

    }

    // printf("result before final operation : ") ; 
    // bigra9m_print(sum) ;

    bigra9m_mul(&sum, &fifth_const, &sum) ; 
    bigra9m_div2(&sum, &fourth_const, &sum ) ; 
    
    // printf("final result : ") ; 
    // bigra9m_print(sum) ; 
    
    
    // we got 1/pi now here is pi : 
    bigra9m_mul(&scale, &scale, &scale) ; 
    bigra9m_div2(&scale, &sum, &c)  ;
    
    printf("final pi : ") ; 
    bigra9m_print(c) ;



    printf("%d digit btw in (2^32) base \n" , sum.length) ; 


 
 
    
    
    // so that the rust devs dont start tweaking at this memory for not getting freed !!!! (it will get freed by the OS anyway)
    bigra9m_clears(&scale , &i_big , &big_minus_one , &big_one , &big_two , &big_ten, &a , &b , &c , &numerator , &denomerator ,&precision  , NULL) ; 
    bigra9m_clears(&temp_1 , &temp_2 , &temp_3 , NULL) ; 
    bigra9m_clears(&first_const , &second_const , &third_const  , &fourth_const , &fifth_const , NULL) ; 
    bigra9m_clears(&big_six , &big_three,  NULL) ; 
    bigra9m_clears(&term , &sum,  NULL) ; 

 
 
 
 
    return 0 ; 
}