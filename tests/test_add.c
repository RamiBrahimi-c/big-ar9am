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

    uint64_t a2 = 0 ; 


    BigInt a  , c ;
    
    bigra9m_inits(&c , &a , NULL) ; 
    // bigra9m_assign_uint64_t(&a , 90000) ; 
    bigra9m_assign_str(&a , "-1") ; 
    bigra9m_assign_str(&c , "12496655418685785816424231563469859388159210277182") ; 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("c : ") ; 
    bigra9m_print(c) ;

    
    bigra9m_add(a , c , &a) ;
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 




}