#include "../../include/bigra9m.h"


// NOTE : not configured yet with dynammic approach


static int is_num(const char a) {
    return a >= '0' && a <= '9' ; 
}




// accepts numbers that are like (-9.../913...) aka starts with number OR numeral digit , yet needs better handling  
// NOTE : works only with base 100   
// TODO : handle input properly like in bizarre cases such as "4545-+565"
// TODO : replace atoi() with strtol ... 
void bigra9m_assign_str(BigInt *a , const char *num_str) {
    
    uchar_t *num_str_clean = strdup(num_str) ;
    // cuz we might increment `num_str_clean` therefore it wont point exactly to the first allocated byte 
    uchar_t *temp = num_str_clean ;
    if (num_str[0]== '-' && is_num(num_str[1]))
    {
        a->length = -1 ;
        num_str_clean = num_str_clean + 1 ;  
    } else if (is_num(num_str[0]))  {
        a->length = 1 ;
        // num_str_clean = num_str  ;  
        
    } else {
        // a->length = 0 ;
        bigra9m_init(a) ; 
        free(num_str_clean) ; 
        return ; 
    }
    

    size_t len = strlen((const char*) num_str_clean) ;

    size_t j = 0 ;
    if (len % 2 ==0)
    {
        j = len/2 ;
        a->length *= j ; 
        j-- ; 
        for (size_t i = 0; i < len; i+=2)
        {
            uchar_t buffer[2] ; 
            memcpy(buffer , num_str_clean + i , sizeof(uchar_t)*2) ;
            a->nums[j] = atoi(buffer ) ;
            j-- ; 
        }
        
    } else {
        j = len/2 +1;;
        a->length *= j ; 
        j-- ; 
        uchar_t buffer[2] ; 
        buffer[1] = 0  ; 
        memcpy(buffer   , num_str_clean  , sizeof(uchar_t)) ;
        a->nums[j] = atoi(buffer) ;
        j-- ; 
        
        for (size_t i = 1; i < len; i+=2)
        {
            uchar_t buffer[2] ; 
            memcpy(buffer , num_str_clean + i , sizeof(uchar_t)*2) ;
            a->nums[j] = atoi(buffer ) ;
            j-- ; 
        }        
    }
    free(temp);
}




void bigra9m_assign_uint64_t(BigInt *a , uint64_t x) {

    bigra9m_init(a);
    int i=0;
    int c;
    while (x > 0)
    {
        c = x % BASE ;
        a->nums[i] = c;
        i++;
        x /= BASE ;
    }
    a->length = i ;

    for (size_t j = 0; j < i; j++)
    {
        uint64_t temp = a->nums[j] ; 
        a->nums[j] = a->nums[i-j-1] ; 
        a->nums[i-j-1] = temp ; 
    }
    
    
}


void bigra9m_assign(BigInt *a , BigInt b  ) {

    memcpy(a , &b , sizeof(BigInt)) ; 
    // a->length = b.length ; 
}



