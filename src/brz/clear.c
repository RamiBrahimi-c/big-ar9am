#include "../../include/bigra9m.h"
// #include "bigra9m.h"
#include <stdlib.h>
#include <stdarg.h>

void bigra9m_clear(BigInt *a) {
    a->capacity = 0 ; 
    a->length = 0 ;
    free(a->nums) ;  
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

