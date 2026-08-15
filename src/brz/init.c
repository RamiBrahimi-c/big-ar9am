#include "../../include/bigra9m.h"
#include <stdlib.h>
#include <stdio.h>

// NOTE : is configured with dynammic approach

int bigra9m_init(BigInt *a) {
    a->length = 0 ;
    a->capacity = 16 ; 
    a->nums = malloc(sizeof(uint64_t)*a->capacity) ; 
    if (a->nums == NULL)
    {
        fprintf( stderr, "ERROR : could not initilize bigra9m ; malloc failed !\n") ; 
        return -1 ; 
    }
    
    memset(a->nums , 0 , a->capacity *sizeof(uint64_t)) ;
    return 0 ;
}
