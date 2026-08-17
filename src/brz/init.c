#ifndef INIT_C
#define INIT_C

#include "../../include/bigra9m.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// TODO: these things are messy as hell and need to get checked AGAIN !!!!!!!!!!!


// NOTE : is configured with dynammic approach

int bigra9m_init(BigInt *a) {
    a->length = 0 ;
    a->capacity = 4 ; 
    a->nums = malloc(sizeof(uint64_t)*a->capacity) ; 
    if (a->nums == NULL)
    {
        fprintf( stderr, "ERROR : could not initilize bigra9m ; malloc failed !\n") ; 
        return -1 ; 
    }
    
    memset(a->nums , 0 , a->capacity *sizeof(uint64_t)) ;
    return 0 ;
}


int bigra9m_inits(BigInt *a , ...) {

    va_list  ap;

    va_start (ap, a);

    do {
        bigra9m_init(a) ; 
        a = va_arg (ap, BigInt *);
    }
    while (a != NULL);

    va_end (ap);    

    return 0 ;
}

int bigra9m_init_assign(BigInt *a , BigInt b  ) {
    bigra9m_init(a) ; 
    a->length = b.length ; 
    // a->capacity = b.capacity ; 
    if (a->capacity < b.capacity)
    {
        a->capacity = b.capacity ; 
        BRZ_ALLOCATE_U64(a->nums , a->capacity) 
        memset(a->nums + abs(a->length), 0x0 , sizeof(uint64_t)*(a->capacity - abs(a->length))) ; 
        
    }
    memcpy(a->nums , b.nums , sizeof(uint64_t)*abs(b.length)) ; 
    
    // memcpy(a , &b , sizeof(BigInt)) ; 

    // a->length = b.length ; 
}
static int is_num(const char a) {
    return a >= '0' && a <= '9' ; 
}


// accepts numbers that are like (-9.../913...) aka starts with number OR numeral digit , yet needs better handling  
// TODO : handle input properly like in bizarre cases such as "4545-+565"
// TODO : replace atoi() with strtol ... 
void bigra9m_init_str(BigInt *a , const char *num_str) {
    
    uchar_t *num_str_clean = strdup(num_str) ;
    // cuz we might increment `num_str_clean` therefore it wont point exactly to the first allocated byte 
    uchar_t *temp = num_str_clean ;

    int sign = 1 ; 
    if (num_str[0]== '-' && is_num(num_str[1]))
    {
        // a->length = -1 ;
        num_str_clean = num_str_clean + 1 ;
        sign = -1 ;  
    } else if (is_num(num_str[0]))  {
        // a->length = 1 ;
        // num_str_clean = num_str  ;  
        
    } else {
        // a->length = 0 ;
        bigra9m_init(a) ; 
        free(num_str_clean) ; 
        return ; 
    }
    

    size_t len = strlen((const char*) num_str_clean) ;
    // for now
    int base = 10 ; 

    bigra9m_init(a) ; 
    bigra9m_assign_uint64_t(a , 0) ; 

    for (size_t i = 0; i < len; i++)
    {
        // printf("i=%ld\n" , i) ; 
        // read one character or one digit
        if (!is_num(num_str_clean[i]))
            continue;
        uchar_t c = num_str_clean[i] ; 
        uint64_t val = c - '0' ; 
        // printf("val : %lu\n" , val) ; 
        bigra9m_mul_uint64(a , base , a ) ;
        // printf("not here\n") ; 
        bigra9m_add_1(*a , val , a ) ;
    }
    a->length *= sign ; 

    free(temp) ; 




}


#endif