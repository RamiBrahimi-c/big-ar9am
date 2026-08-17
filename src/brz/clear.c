#include "bigra9m.h"
#include <stdlib.h>

void bigra9m_clear(BigInt *a) {
    a->capacity = 0 ; 
    a->length = 0 ;
    free(a->nums) ;  
}
