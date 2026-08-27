#include "../../include/bigra9m.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: these things are messy as hell and need to get checked AGAIN !!!!!!!!!!!

// NOTE : not configured yet with dynammic approach
// NOTE : these function should be treated as a `init` ???


static int is_num(const char a) {
    return a >= '0' && a <= '9' ; 
}




// accepts numbers that are like (-9.../913...) aka starts with number OR numeral digit , yet needs better handling  
// TODO : handle input properly like in bizarre cases such as "4545-+565"
// TODO : replace atoi() with strtol ... 
void bigra9m_assign_str(BigInt *a , const char *num_str) {
    
    uchar_t *num_str_clean = strdup(num_str) ;
    // cuz we might increment `num_str_clean` therefore it wont point exactly to the first allocated byte 
    uchar_t *temp = num_str_clean ;
    int sign = 1 ; 
    if (num_str[0]== '-' && is_num(num_str[1]))
    {
        sign = -1 ; 
        // a->length = -1 ;
        num_str_clean = num_str_clean + 1 ;  
    } else if (is_num(num_str[0]))  {
        // a->length = 1 ;
        // num_str_clean = num_str  ;  
        
    } else {
        a->length = 0 ;
        // bigra9m_init(a) ; 
        free(num_str_clean) ; 
        return ; 
    }
    

    size_t len = strlen((const char*) num_str_clean) ;
    // for now
    int base = 10 ; 

    // bigra9m_init(a) ; 
    bigra9m_assign_uint64_t(a , 0) ; 

    for (size_t i = 0; i < len; i++)
    {
        // printf("i=%ld\n" , i) ; 
        // read one character or one digit
        uchar_t c = num_str_clean[i] ; 
        uint64_t val = c - '0' ; 
        // printf("val : %lu\n" , val) ; 
        bigra9m_mul_uint64(a , base , a ) ;
        bigra9m_add_1(*a , val , a ) ;
    }
    a->length *= sign ; 

    free(temp);
}




int bigra9m_assign_uint64_t(BigInt *a , uint64_t x) {
    if (x == 0)
    {
        a->length = 0 ; 
        return 0 ; 
    }
    
    // bigra9m_init(a);
    int i=0;
    uint64_t c;
    while (x > 0)
    {
        c = x % BASE ;
        a->nums[i] = c;
        i++;
        x /= BASE ;
        a->length = i ;
        if (a->capacity < i*2)
        {
            a->capacity = nextPowerOfTwo(a->capacity) ; 
            // printf("reallocating with %d \n" , a->capacity) ; 
            BRZ_ALLOCATE_U64(a->nums , a->capacity )
            /* a->nums = realloc(a->nums , a->capacity * sizeof(uint64_t)) ;  
            if (a->nums == NULL) { 
                fprintf(stderr , "ERROR: realloc failed sadly");    
                return -1;    
            }  
            printf("array start at : %p \n" , a->nums) ; 
            printf("about to set %d bytes to 0 starting from %p \n" ,a->capacity -  a->length , a->nums + a->length ) ;

            printf("reallocating???\n") ;  */
        }
        
    }

    for (size_t j = 0; j < i; j++)
    {
        uint64_t temp = a->nums[j] ; 
        a->nums[j] = a->nums[i-j-1] ; 
        a->nums[i-j-1] = temp ; 
    }
    
    
}

// IMPORTANT : here we pretend like a went through init before
void bigra9m_assign(BigInt *a , BigInt b  ) {

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



