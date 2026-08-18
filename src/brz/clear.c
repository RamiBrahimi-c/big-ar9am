#include "../../include/bigra9m.h"
// #include "bigra9m.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define DEBUG 0

void bigra9m_clear(BigInt *a) {
    a->capacity = 0 ; 
    a->length = 0 ;
    #if DEBUG
    printf("about to free : %p \n" , a->nums) ; 
    #endif
    free(a->nums) ;  
    #if DEBUG
    printf("free'd successfully :  \n" ) ; 
    #endif
}


// i didnt have internet so i browsed the source code of gmp and stole how va_list works :( ...
void bigra9m_clears(BigInt *a , ...) {
        
    va_list  ap;

    va_start (ap, a);

    do {
        bigra9m_clear(a) ; 
        a = va_arg (ap, BigInt *);
    }
    while (a != NULL);

    va_end (ap);    
 
}

