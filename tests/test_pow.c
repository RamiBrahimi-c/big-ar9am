/*
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bigra9m.h"
#include "../include/utils.h"
#include "../include/test.h"
#include <math.h>
#define N 100



static int getbit_bigra9m(BigInt a , int position) {
    int t = floor(log2(BASE)) + 1 ;
    t *= a.length ; 
    if (t==0)
    {
        return -1 ; 
    }
    
    int n  = position * a.length / t ;
    position %= 8 ; 

    uint64_t temp = a.nums[n] ;
    int k = 0 ; 
    while (k < position)
    {   
        temp >>= 1 ;
        k++ ;  
    }
    return temp & 0b1 ; 
      
}

int main()
{



    BigInt a   ,b, c , d;
    
    bigra9m_inits(&a , &b , &c , &d , NULL) ;
    bigra9m_assign_str(&a , "2") ; 
    bigra9m_assign_str(&b , "3") ; 
    bigra9m_assign_str(&c , "3") ; 
    // bigra9m_assign_str(&c , "12496655418685785816424231563469859388159210277183") ; 

    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 



    // bigra9m_pow(&a , &a  , &c ) ;
    modular_exponentiation(&a , &b , &c ,&d ) ;

    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 

 /* 
    int t =  (((log2(BASE))) + 1) ;
    printf("t = %d \n" , t) ; 
    
    bigra9m_assign_uint64_t(&a , 222) ; 
    bigra9m_print(a) ; 
    int position = 1 ;
    for (size_t i = 0; i < 10; i++)
    {
        printf("bit at pos %d is %d \n"  , i, getbit_bigra9m(a , i)) ; 
        
    }
      */

    bigra9m_clears(&a , &b , &c , &d, NULL) ; 

}