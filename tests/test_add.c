/*
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bigra9m.h"
#include "utils.h"
#include "test.h"

#define N 100

int main()
{

    BigRa9m a , b , c ; // or BigInt BigRa9m a , b , c ;  
    

    // make sure to initilize it first !!!
    // (use one of the 'inits' functions )
    bigra9m_inits(&a , &b , NULL) ;
    bigra9m_init_str(&c , "123456789987654321") ;
    
    
    // lats assign some HUGE numbers !!!
    bigra9m_assign_str(&a , "-123456876432654321351000650100000") ; 
    bigra9m_assign_uint64_t(&b , 0x123456789 ) ; 
    
    // now we print numbers to check 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ;

    // do some operation on it 
    bigra9m_add(a , b , &c) ;
    

    // print results : 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 

    // please clean your memory when you finish working !!!!!!
    bigra9m_clears(&a , &b , &c , NULL) ; 


}