#include "../include/bigra9m.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void bigra9m_assign(BigInt *a , BigInt b  ) {

    memcpy(a , &b , sizeof(BigInt)) ; 
    // a->length = b.length ; 
}


void bigra9m_init(BigInt *a) {
    a->length = 0 ;
    memset(a->nums , 0 , MAX_LEN*sizeof(uint64_t)) ;
}


static int is_num(const char a) {
    return a >= '0' && a <= '9' ; 
}

// accepts numbers that are like (-9.../913...) aka starts with number OR numeral digit , yet needs better handling  
// TODO : handle input properly like in bizarre cases such as "4545-+565"
// TODO : replace atoi() with strtol ... 
void bigra9m_assign_str(BigInt *a , const char *num_str) {
    
    uchar_t *num_str_clean ;
    if (num_str[0]== '-' && is_num(num_str[1]))
    {
        a->length = -1 ;
        num_str_clean = num_str + 1 ;  
    } else if (is_num(num_str[0]))  {
        a->length = 1 ;
        num_str_clean = num_str  ;  
        
    } else {
        // a->length = 0 ;
        bigra9m_init(a) ; 
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
    
}


void bigra9m_print(BigInt number) {
    // printf("length : (%ld) ||\t" , number.length) ; 
    if (number.length < 0)
    {
        printf("-");
        number.length *= -1 ; 
    } else if (!number.length) {
        printf("0") ; 
    }
    

    for (size_t i = 0 ; i < number.length ; i++)
    {
        uchar_t a = number.nums[number.length-i-1] ; 
        if (a==0 && i == 0)
        {
            printf("0") ; 
        }
        else if (a < 10 && number.length > 1 && i != 0)
        {
            printf("0%d" , a) ; 
        } else if (a ==0 ) {
            printf("00") ; 

        } else {
            printf("%d" , a) ; 

        }
        
        
    }
    printf("\n") ; 
    
}

// TODO: handle when some length is 0
void bigra9m_add(BigInt a , BigInt b , BigInt *c ) {
    if (a.length * b.length < 0)
    {
        bigra9m_sub(a , b , c) ; 
        return ;
    } 

    
    // lets assume same length for a and b
    if (abs(a.length) == abs(b.length))
    {
        uint64_t overflow = 0 ;
        for (size_t i = 0; i < abs(a.length); i++)
        {
            uint64_t result = a.nums[i] + b.nums[i] + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            
        }

        c->length = a.length  ; 
        if (overflow != 0)
        {
            c->nums[abs(a.length)] = overflow ; 
            c->length = a.length + (a.length/abs(a.length)) ; 
        }
        
    } else {

        size_t min_len = (abs(a.length) < abs(b.length)) ? abs(a.length) : abs(b.length) ;
        size_t max_len ;
        BigInt *umm ;
        if (abs(a.length) > abs(b.length))
        {
            max_len = abs(a.length) ;
            umm = &a ; 
        } else {
            max_len = abs(b.length) ;
            umm = &b ; 

        }
        

        uint64_t overflow = 0 ;
        for (size_t i = 0; i < min_len; i++)
        {
            uint64_t result = a.nums[i] + b.nums[i] + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0  ;
            }
            
        }
        for (size_t i = min_len; i < max_len ; i++)
        {
            uint64_t result = umm->nums[i]  + overflow ; 
            c->nums[i] = (result % BASE)  ; 
            if (result >= BASE)
            {
                overflow = result ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            
        }

        c->length = umm->length  ; 
        if (overflow != 0)
        {
            c->nums[abs(umm->length)] = overflow ; 
            c->length = umm->length + (umm->length/umm->length) ; 
        }
    }
}

// fucking hell .
// fuck this shit 
// TODO : this is NOT bug-free !!!!!!!!!!!!! 
void bigra9m_sub(BigInt a , BigInt b , BigInt *c) {
    if (a.length * b.length < 0)
    {
        b.length *= -1 ; 
        bigra9m_add(a , b , c) ;
        return ; 
    }
    if ((a.length == b.length && a.nums[abs(a.length)-1] < b.nums[abs(b.length)-1]) ||
    abs(a.length) < abs(b.length) )
    {
        
        c->length = -1 ; 
        
        BigInt temp ; 
        memcpy(&temp , &a , sizeof(BigInt)) ; 
        memcpy(&a , &b , sizeof(BigInt)) ; 
        memcpy(&b , &temp , sizeof(BigInt)) ; 
    } else  {

        c->length = (a.length/a.length) ; 
    }


    if (abs(a.length) == abs(b.length))
    {
        // printf("here\n") ; 
        uint64_t overflow = 0 ;
        uint64_t result ;
        for (size_t i = 0; i < abs(a.length); i++)
        {
            if (a.nums[i] >= (b.nums[i] + overflow))
            {
                result = a.nums[i] - (b.nums[i] + overflow) ; 
                overflow = 0 ; 
            } else {
                result = (a.nums[i] + BASE)  - (b.nums[i] + overflow) ; 
                overflow = 1 ; 
            }
            
            c->nums[i] = (result % BASE)  ; 
        }

        c->length *= a.length  ; 
        if (overflow != 0 && 0)
        {
            c->nums[abs(a.length)] = overflow ; 
            c->length = a.length + (a.length/a.length) ; 
        }
        
    } else {
        size_t min_len = (abs(a.length) < abs(b.length)) ? abs(a.length) : abs(b.length) ;
        size_t max_len ;
        BigInt *umm ;
        if (abs(a.length) > abs(b.length))
        {
            max_len = abs(a.length) ;
            umm = &a ; 
        } else {
            max_len = abs(b.length) ;
            umm = &b ; 

        }
        
        int j = 0 ; 
        uint64_t overflow = 0 ;
        uint64_t result ;
        for (size_t i = 0; i < abs(a.length); i++)
        {
            if (a.nums[i] >= (b.nums[i] + overflow))
            {
                result = a.nums[i] - (b.nums[i] + overflow) ; 
                overflow = 0 ; 
            } else {
                result = (a.nums[i] + BASE)  - (b.nums[i] + overflow) ; 
                overflow = 1 ; 
            }
            j++ ; 
            c->nums[i] = (result % BASE)  ; 
        }

        c->length *= j  ; 
        if (overflow != 0)
        {
            printf("overflow\n") ;
            j++ ; 
            c->nums[abs(umm->length)] = overflow ; 
            c->length = umm->length + (umm->length/umm->length) ; 
        }
        
        if (c->nums[c->length-1]==0 && c->length != 0)
        {
            c->length -= (c->length/c->length) ; 
        }
    }    
}




// our dummy so called naive algorithm 
// complexity O(n²)
// REQUIRES FOR C TO BE INITILIZED PROPERLY ...
void bigra9m_mul(BigInt a , BigInt b , BigInt *c) {

    if ((a.length == b.length && a.nums[abs(a.length)-1] > b.nums[abs(b.length)-1]) ||
    abs(a.length) > abs(b.length) )
    {        
        BigInt temp ; 
        memcpy(&temp , &a , sizeof(BigInt)) ; 
        memcpy(&a , &b , sizeof(BigInt)) ; 
        memcpy(&b , &temp , sizeof(BigInt)) ; 
    } 
    uint64_t overflow = 0 ;
    uint64_t result ;
            
    for (size_t i = 0; i < abs(a.length); i++)
    {
        overflow = 0 ; 
        for (size_t j = 0; j < abs(b.length); j++)
        {
            c->nums[i+j] += (a.nums[i] * b.nums[j]) + overflow ; 
                    
                    
            if (c->nums[i+j] >= BASE)
            {
                overflow = c->nums[i+j] ;
                overflow /= BASE ; 
            } else {
                overflow = 0 ; 
            }
            c->nums[i+j] %= BASE  ; 
                    
        }
        c->length =  i+abs(b.length)  ;
        if (overflow)
        {
            c->nums[i+abs(b.length)] = (overflow )  ;
            c->length =  i+abs(b.length)  +1;
        }
    }

    if (a.length * b.length > 0) {
        c->length *= (int) (a.length/a.length) ; 
    } else {
        c->length *= -1 ; 

    }

}


int bigra9m_is_zero(BigInt a) {
    return a.length == 0 ; 
}

int bigra9m_is_positive(BigInt a) {
    return a.length > 0 ; 
}

int bigra9m_is_negative(BigInt a) {
    return a.length < 0 ; 
}



static void repeated_subtraction_division(BigInt N , BigInt D ,BigInt *Qoeff , BigInt *Reminder ) {
    if (D.length ==0)
    {
        printf("Division by 0\n") ; 
        return ; 
    }
    BigInt R , Q ; 
    bigra9m_assign(&R , N) ; 
    bigra9m_assign_str(&Q , "0") ; 
    BigInt temp  , temp2; 
    bigra9m_assign_str(&temp , "1") ; 
    while (bigra9m_isBiggerThanNum(R , D))
    {
        bigra9m_sub(R , D  , &temp2) ; 
        bigra9m_add(Q , temp  , &Q) ; 
        bigra9m_assign(&R , temp2) ; 
        
        // bigra9m_print(R) ; 
        // bigra9m_print(D) ; 
        // bigra9m_print(temp2) ; 
    }
    
    bigra9m_assign(Qoeff , Q) ; 
    bigra9m_assign(Reminder , R) ; 
    
}

void bigra9m_div(BigInt a , BigInt b , BigInt *c ,  BigInt *d) {
    repeated_subtraction_division(a , b , c , d) ; 

}


// TODO : needs more testing
int bigra9m_isBiggerThanNum(BigInt a , BigInt b) {
    if (a.length * b.length < 0)
    {
        return a.length > b.length ;   
    } 
    
    if (a.length > b.length)
    {
        return 1; 
    }else if (a.length < b.length) {
        return 0; 

    } else if (a.length == b.length && a.length != 0) {
        return a.nums[a.length-1] >= b.nums[a.length-1] ; 
    } else {
        return 0; 
    }
    
}


int main() {

    
    TEST_SUBTRACTION("-55" , "89") ;


    return 0 ; 
}
