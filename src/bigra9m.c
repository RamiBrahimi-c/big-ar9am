#include "../include/bigra9m.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include <string.h>
#if 1
    #define DEBUG
#endif


/* TODO : actually you need to fix bigra9m_mul cuz each time we need to initilize it before we call it !!!!!!!!!!!!!!!*/ 

static int bigra9m_is_clean_lastdigit(BigInt a) {
    return a.nums[abs(a.length)-1] != 0  ;
}
static void bigra9m_clean_lastdigit(BigInt *a) {
    if (a != NULL && a->nums[a->length-1] ==0)
    {
        if (a->length > 0)
        {
            a->length-- ; 
        } else {
            a->length++ ; 

        }
        
    }
    
} 


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
    
    uchar_t *num_str_clean = strdup(num_str) ;
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
    free(num_str_clean);
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
    if ((a.length == b.length && !bigra9m_isBiggerThanNum(a , b)) ||
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
    // to actually clean the result and not left it with some useless 0s
    while (!bigra9m_is_clean_lastdigit(*c))
    {
        bigra9m_clean_lastdigit(c) ; 
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


#define DEBUG_KNUTHS 0
// fuck this algorithm
// TODO : this algo stills need to do the length correctly plus calculating the reminder ..
static void knuths_algorithm_d(BigInt U , BigInt V ,BigInt *Qoeff , BigInt *Reminder) {
    #if DEBUG_KNUTHS
        printf("knuth's algorithm here !!!!!\n");
        printf("DIVIDEND : \n") ; 
        bigra9m_print(U); 
        printf("DIVISOR : \n") ; 
        bigra9m_print(V); 
    #endif
    uint64_t D = (BASE-1) / V.nums[V.length-1] ;
    BigInt temp_U , temp_V ;
    bigra9m_assign(&temp_U , U) ; 
    bigra9m_assign(&temp_V , V) ; 
    
    int m = U.length - V.length ; 
    int j = m ;
    int n = V.length ;
    Qoeff->length = m +1; 

    // step 1 : [Normalize]
    while(V.nums[V.length-1] < BASE/2) {
        // uint64_t d = (uint64_t) (BASE-1) / V.nums[V.length-1] ; 
        uint64_t d = 2 ; 
        
        bigra9m_mul_uint64(U , d , &U) ;
        bigra9m_mul_uint64(V , d , &V) ;
    }  
    
    #if DEBUG_KNUTHS
    if (V.nums[V.length-1] >= BASE/2)
    {
        printf("yes normalized\n") ; 
    } else {
        printf("no not normalized\n") ; 

    }
    #endif
    
    /*
        NOTE in this phase , U is supposed to get added a 0 on its left
        make sure to have enough allocated space ...
    */
    m = U.length - V.length ; 
    n = V.length ; 
    Qoeff->length = m +1; 

    
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
            #if DEBUG_KNUTHS

                printf("panic\n"); 
                // for debugging ...
                printf("this happened when U : \n"); 
                bigra9m_print(temp_U) ; 
                printf("and V : \n"); 
                bigra9m_print(temp_U) ; 
            #endif
            // exit(64) ;
            Qoeff->nums[j]-- ; 
            bigra9m_add(V , temp , &temp) ;

            k=0 ; 
            for (size_t i = j; i < j +  n + 1; i++)
            {
                U.nums[i] = temp.nums[k]  ; 
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

    while (!bigra9m_is_clean_lastdigit(*Qoeff))
    {
        bigra9m_clean_lastdigit(Qoeff) ; 
    }
    
    while (!bigra9m_is_clean_lastdigit(*Reminder))
    {
        bigra9m_clean_lastdigit(Reminder) ; 
    }
    

    #if DEBUG_KNUTHS
    printf("quoeff : ????\n");
    bigra9m_print(*Qoeff);
    #endif
    bigra9m_mod2(temp_U , temp_V , *Qoeff , Reminder) ; 
    
    #if DEBUG_KNUTHS
    printf("reminder : ????\n");
    bigra9m_print(*Reminder);
    #endif

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
    knuths_algorithm_d(a , b , c , d) ; 
    // repeated_subtraction_division(a , b , c , d) ; 

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
        for (int i = a.length -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] >= b.nums[i] ; 
            
        }
        return 0 ; 
       
    } else {
        return 0; 
    }
    
}

int bigra9m_isStrictlyBiggerThanNum(BigInt a , BigInt b) {
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
        for (int i = a.length -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] > b.nums[i] ; 
            
        }
        return 0 ; 
        
        // return a.nums[a.length-1] > b.nums[b.length-1] ; 
    } else {
        return 0; 
    }
    
}

#define S 10
#include <time.h>
#include <math.h>

uint64_t pow_ui64(uint64_t a , uint64_t b) {
    uint64_t r = 1 ;
    for (size_t i = 0; i < b; i++)
    {
        r *= a ; 
    }
    return r ; 
}


// bro this NEEDS MORE investegations
void bigra9m_pow(BigInt base , BigInt pow , BigInt *res) {
    BigInt i , inc , copy ; 
    bigra9m_assign_str(&i , "2");
    bigra9m_assign_str(&inc , "1");
    // bigra9m_assign_str(res , "1");
    bigra9m_assign(&copy , base);
    bigra9m_init(res );
    int j = 0;
    
    while (!bigra9m_isStrictlyBiggerThanNum(i , pow))
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



void bigra9m_mod2(BigInt dividend , BigInt divisor , BigInt quoeff , BigInt *c) {
    BigInt temp , temp2; 

    bigra9m_init(&temp) ;
    bigra9m_init(&temp2) ;
    #ifdef DEBUG_MOD2
        printf("multiplying : ");
        bigra9m_print(divisor) ; 
        printf("and : ");
        bigra9m_print(quoeff) ; 
    #endif
    bigra9m_mul(divisor , quoeff , &temp) ; 
    #ifdef DEBUG_MOD2

        printf("=  ");
        bigra9m_print(temp) ; 
    
        printf("subtracting : ") ; 
        bigra9m_print(dividend) ; 
        printf("and : ") ; 
        bigra9m_print(temp) ; 
    #endif    
    
    bigra9m_sub(dividend , temp , c);
    
    #ifdef DEBUG_MOD2
        printf("=  ");
        bigra9m_print(*c) ; 
    #endif
}


void bigra9m_mod(BigInt dividend , BigInt divisor , BigInt *c) {
    BigInt a ;
    bigra9m_div(dividend , divisor ,&a , c ) ; 
}


static int fermat_primality_test_uint64(uint64_t p) {
    srand(time(0)) ; 
    size_t s = S , a;
    for (size_t i = 0; i < s; i++)
    {
        a = (rand() % (p-1))  ;
        a = (a == 0 || a==1) ? 2 : a ;
        // printf("testing with a=%ld  p-1=%ld \tpow(a , p-1) %% p =%lu \n" , a , p-1   ,( pow_ui64(a , p-1) % p )  ) ; 
        // printf("pow(a , p-1):%lu  \n" ,   pow_ui64(a , p-1)   ) ; 
        if ( pow_ui64(a , p-1) % p != 1)
        {
            return 1 ;
        }
         
    }
    return 0 ; 
    
}

int bigra9m_fermat_primality_test(BigInt p) {
    srand(time(0)) ; 
    
    BigInt i , inc , inc2 , a , p_min1 , s , temp ;
    bigra9m_init(&i) ;
    bigra9m_init(&inc) ;
    bigra9m_init(&inc2) ;
    bigra9m_init(&a) ;
    bigra9m_init(&p_min1) ;

    bigra9m_assign_str(&i , "1") ; 
    bigra9m_assign_str(&inc , "1") ; 
    bigra9m_assign_str(&inc2 , "0") ; 
    // inc2.length = 0 ;
    bigra9m_assign_uint64_t(&s , S) ; 
    bigra9m_sub(p , inc , &p_min1) ; 
    // printf("hi\n");
    // bigra9m_init(&i) ;
    int j = 0 ; 
    while (!bigra9m_isBiggerThanNum(i , s))
    {
        // init a
        // printf("hi\n");
        bigra9m_assign_uint64_t(&a , 2 ) ; 
        // bigra9m_assign_uint64_t(&a , rand() % 100 ) ; 

        bigra9m_mod(a , p_min1 , &a ) ;
        // printf("its not mod\n"); 
        // check if a = 0 OR a= 1
        if (bigra9m_isEqualNum(temp , inc) || bigra9m_isEqualNum(temp , inc2))
        {
            bigra9m_assign_uint64_t(&a , 2) ; 
        }
        
        printf("a : ") ; 
        bigra9m_print(a) ; 
        printf("p min 1: ") ; 
        bigra9m_print(p_min1) ; 
        
        bigra9m_pow(a , p_min1 , &temp) ; 
        printf("temp : \n");
        bigra9m_print(temp);  
        // bigra9m_print(p);  
        bigra9m_mod(temp , p , &temp) ; 
        // printf("its not mod\n"); 


        if (!bigra9m_isEqualNum(temp , inc))
        {
            printf("====================================\n");
            printf("p is composite\n") ; 
            printf("====================================\n");
            return 1 ; 
        }
        bigra9m_add(i , inc , &i) ; 
    }
    printf("====================================\n");
    printf("p could be prime\n") ;     
    printf("====================================\n");
    return 0 ; 

}



int bigra9m_isEqualNum(BigInt a , BigInt b) {
    if (a.length != b.length)
    {
        return 0; 
    }

    for (size_t i = 0; i < a.length; i++)
    {
        if (a.nums[i] != b.nums[i])
        {
            return 0 ; 
        }
        
    }
    
    return 1 ;     
}






#if 0
int main(int argc , char **argv) {

    // BigInt ccc , rrrr ; 
    // bigra9m_init(&ccc ) ; 
    // bigra9m_init( &rrrr) ; 

    // bigra9m_assign_str(&ccc , "1020") ; 

    // bigra9m_mul_uint64(ccc , 5 , &rrrr) ; 

    // bigra9m_print(rrrr) ;

    // exit(0) ; 

    BigRa9m U , V  , Q , R;
    bigra9m_init(&U) ; 
    bigra9m_init(&V) ; 
    bigra9m_init(&Q) ; 
    bigra9m_init(&R) ; 

    // bigra9m_assign_str(&U , argv[1]) ; 
    // bigra9m_assign_str(&V , argv[2]) ; 

    // knuths_algorithm_d(U , V , &Q , &R) ; 

    // printf("final result : ") ; 
    // bigra9m_print(Q) ; 
    // printf("final reminder : ") ; 
    // bigra9m_print(R) ; 

    
    // exit(EXIT_SUCCESS)  ; 



    BigInt p_big ;
    bigra9m_init(&p_big) ;
    uint64_t p = 29 ; 
    bigra9m_assign_uint64_t(&p_big , p) ;  
    if (argc > 1)
    {
        p = atoi(argv[1]) ; 
        bigra9m_assign_str(&p_big , argv[1]) ; 
    }
    printf("testing on : ") ; 
    bigra9m_print(p_big) ; 

    int result2 = bigra9m_fermat_primality_test(p_big) ; 
    printf("ending bigra9m\n\n\n");

    int result = fermat_primality_test_uint64(p) ; 
    printf("result = %d\n" , result) ; 
    printf("result2 = %d\n" , result) ; 
    if (result == 0)
    {
        printf("%lu is likely prime\n" , p) ; 
    } else {
        printf("%lu is composite\n" , p) ; 
    }
    
    return 0 ; 
}
#endif