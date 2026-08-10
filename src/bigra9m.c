#include "../include/bigra9m.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

#if 1
    #define DEBUG
#endif


/* TODO : actually you need to fix bigra9m_mul cuz each time we need to initilize it before we call it !!!!!!!!!!!!!!!*/ 



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
// NOTE : works only with base 100   
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
        if (c->nums[c->length-1]==0 && c->length != 0)
        {
            c->length -= (c->length/c->length) ; 
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


#define DEBUG_KNUTHS
// fuck this algorithm
static void knuths_algorithm_d(BigInt U , BigInt V ,BigInt *Qoeff , BigInt *Reminder) {
    printf("knuth's algorithm here !!!!!\n");
    printf("DIVIDEND : \n") ; 
    bigra9m_print(U); 
    printf("DIVISOR : \n") ; 
    bigra9m_print(V); 

    uint64_t D = (BASE-1) / V.nums[V.length-1] ;
    BigInt temp_U , temp_V ;
    bigra9m_assign(&temp_U , U) ; 
    bigra9m_assign(&temp_V , V) ; 
    
    int m = U.length - V.length ; 
    int j = m ;
    int n = V.length ;
    Qoeff->length = m +1; 

    // step 1 : [Normalize]
    do {
        // uint64_t d = (uint64_t) (BASE-1) / V.nums[V.length-1] ; 
        uint64_t d = 2 ; 
        
        bigra9m_mul_uint64(U , d , &U) ;
        bigra9m_mul_uint64(V , d , &V) ;
    } while(V.nums[V.length-1] < BASE/2) ;

    if (V.nums[V.length-1] >= BASE/2)
    {
        printf("yes normalized\n") ; 
    } else {
        printf("no not normalized\n") ; 

    }
    
    if (U.length == m + n)
    {
        // U.length++ ; 
    }
    m = U.length - V.length ; 
    n = V.length ; 
    Qoeff->length = m+1 ; 

    
    // step 2 : [Initilize]
    j = m ; 

    do {
        // step 3 : Calculate q^

        uint64_t q_hat = (U.nums[j+n]*BASE + U.nums[j+n-1]) / V.nums[n-1] ; 
        uint64_t r_hat = (U.nums[j+n]*BASE + U.nums[j+n-1]) % V.nums[n-1] ; 

        while (q_hat == BASE ||  q_hat * V.nums[n-2] > BASE*r_hat + U.nums[j+n-2])
        {
            q_hat-- ; 
            r_hat += V.nums[n-1] ; 

            if (r_hat >= BASE)
            {
                break;
            }
            
        }

        // step 4 : [Multiply and Subtract]

        BigInt temp , temp2;
        int k = 0 ;  
        for (size_t i = j; i < j + n + 1; i++)
        {
            temp.nums[k] = U.nums[i] ;
            k++  ; 
        }
        // temp.length = j + n + 1 ; 
        temp.length = k ; 
        // temp now has digits of (U) from (j) to (n+j)
        
        bigra9m_init(&temp2) ; 

        bigra9m_mul_uint64(V , q_hat , &temp2) ; 
        bigra9m_sub(temp , temp2 , &temp ) ; 

        k=0 ; 
        for (size_t i = j; i < j + n + 1; i++)
        {
            U.nums[i] = temp.nums[k]  ; 
            k++ ; 
        }

        // step 5 : [Test Reminder]


        Qoeff->nums[j] = q_hat ; 

        if (bigra9m_is_negative(temp))
        {
            // step 6 : [Add back]
            printf("panic\n"); 
            // exit(64) ;
            Qoeff->nums[j]-- ; 
            bigra9m_add(V , temp , &temp) ;

            k=0 ; 
            for (size_t i = j; i < j +  n + 1; i++)
            {
                U.nums[j] = temp.nums[k]  ; 
                k++ ; 
            }

        }
        // step 7 : [Loop on j]
        j-- ; 

    } while (j>=0) ; 
    
    


    // bigra9m_mul(U , D , U) ;
    // bigra9m_mul(V , D , V) ;
    
    // bigra9m_assign(&D , );
    //     Set Q̂ to (U[n+j] × B + U[n−1+j]) ÷ V[n−1]; 
    //     Set R̂ to (U[n+j] × B + U[n−1+j]) % V[n−1]; 
    printf("quoeff : ????\n");
    bigra9m_print(*Qoeff);
    

}
/*    uint64_t normalization_factor = 0 ; 
    BigInt big_2 ; 
    bigra9m_assign_str(&big_2 , "2") ; 


    // first step normalizing ????
    
    while (V.nums[V.length-1] < BASE / 2  )
    {
        bigra9m_mul(U , big_2 , &U) ; 
        bigra9m_mul(V , big_2 , &V) ; 
        normalization_factor++ ; 
    }
    

    
    for (size_t i = 0; i < V.length - 1; i++)
    {
        U.nums[i] = V.nums[i] = 0 ; 
    }
    
    uint64_t ratio = (U.nums[U.length-1] * (BASE-1) + U.nums[U.length-1]   ) ;
    ratio = ratio < BASE -1 ? ratio : BASE-1 ; 
    ratio /= V.nums[V.length-1] ; 

    #ifdef DEBUG_KNUTHS
        printf("printing after normalizing : \n") ; 
        bigra9m_print(U); 
        bigra9m_print(V); 

        printf("ratio : %lu \n" , ratio ) ; 
    #endif

    BigInt r_hat , q_hat; 
    bigra9m_init(&r_hat) ; 
    bigra9m_init(&q_hat) ; 
    bigra9m_assign_uint64_t(&q_hat ,ratio ) ;
    
    #ifdef DEBUG_KNUTHS
    printf("q hat :  "  ) ; 
    bigra9m_print(q_hat) ; 
    #endif    
    bigra9m_mod2(U , V , q_hat , &r_hat ) ; 
    
    #ifdef DEBUG_KNUTHS
        printf("r hat : "  ) ; 
        bigra9m_print(r_hat) ; 
    #endif

    BigInt temp1 , temp2 , temp3 , big1 , big6 , big7; 
    bigra9m_init(&temp1) ; 
    bigra9m_init(&temp2) ; 
    bigra9m_assign_str(&big1 , "1") ; 
    bigra9m_assign_uint64_t(&big6 , temp_U.nums[0]) ; 
    bigra9m_assign_uint64_t(&big7 , temp_V.nums[0] ) ; 


    bigra9m_mul(q_hat , big7 , &temp1) ; 
    bigra9m_add(r_hat , big6 , &temp2) ; 

    #ifdef DEBUG_KNUTHS
        printf("hi!!!\n");
        bigra9m_print(big6);
        bigra9m_print(big7);
        bigra9m_print(temp1);
        bigra9m_print(temp2);
    #endif
        // temp2.length-- ; 
        printf("hi!!! is bigger :%d \n" , bigra9m_isStrictlyBiggerThanNum(temp1 , temp2));
    
    while (bigra9m_isStrictlyBiggerThanNum(temp1 , temp2))
    {
        printf("hi???\n");
        bigra9m_sub(q_hat , big1 , &temp3);
        bigra9m_assign(&q_hat  , temp3);

        bigra9m_print(temp3) ; 

        bigra9m_init(&temp1) ; 
        bigra9m_mul(q_hat , big7 , &temp1) ; 

        bigra9m_mod2(U , V , temp3 , &r_hat ) ; 
        bigra9m_add(r_hat , big6 , &temp2) ; 

    }
    
    bigra9m_assign(Qoeff , temp3) ; 

    bigra9m_mod2(temp_U ,temp_V , temp3 , Reminder);
    // bigra9m_assign(Reminder , r_hat) ; 
    printf("normalization factor : %lu\n" , normalization_factor) ;

    return ; 
    


    #ifdef DEBUG_KNUTHS
        printf("m=%d\n" , m) ;
    #endif
    #endif
*/
static int bigra9m_is_normalized(BigInt a) {


    return 0;
}


static void naive_division(BigInt U , BigInt V ,BigInt *Qoeff , BigInt *Reminder) {
    

}


void bigra9m_div(BigInt a , BigInt b , BigInt *c ,  BigInt *d) {
    repeated_subtraction_division(a , b , c , d) ; 
    // knuths_algorithm_d(a , b , c , d) ; 

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



static int fermat_primality_test(uint64_t a) {
    size_t s ;
    for (size_t i = 0; i < s; i++)
    {
        
    }
    
}


void bigra9m_pow(BigInt base , BigInt pow , BigInt *res) {
    BigInt i , inc , copy ; 
    bigra9m_assign_str(&i , "1");
    bigra9m_assign_str(&inc , "1");
    // bigra9m_assign_str(res , "1");
    bigra9m_assign(&copy , base);
    bigra9m_init(res );
    int j = 0;
    
    while (!bigra9m_isBiggerThanNum(i , pow))
    {
        // bigra9m_print(base);
        // bigra9m_print(copy);
        
        bigra9m_init(res );
        bigra9m_mul(base , copy , res);
        bigra9m_assign(&copy , *res);
        bigra9m_add(i , inc , &i) ;
        j++ ; 
        // bigra9m_print(*res);
    }

}



void bigra9m_mod(BigInt dividend , BigInt divisor , BigInt *c) {
    BigInt a ;
    bigra9m_div(dividend , divisor ,&a , c ) ; 
}



// int main() {

//     // TEST_DIVISION("100" , "50") ;
//     TEST_POWER_EXPO("10" , "10") ;

//     BigInt a;
//     uint64_t x = 10254650; 
//     bigra9m_assign_uint64_t(&a , x );
//     printf("x=%lu\n" , x) ; 
//     bigra9m_print(a);        


//     return 0 ; 
// }
