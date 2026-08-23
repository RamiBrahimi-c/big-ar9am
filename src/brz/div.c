#include "../../include/bigra9m.h"
#include "../../include/utils.h"

// NOTE : not configured yet with dynammic approach
// NOTE : more tests needed !!!!
// NOTE IMPORTANT : i changed the signature of knuth's algorithm cuz this one `knuths_algorithm_d(BigInt U , BigInt V ,BigInt *Qoeff , BigInt *Reminder)`
// caused a double free somehow for a reason i STILL DO NOT KNOW yet ... 

#define DEBUG_KNUTHS 0

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
        bigra9m_sub(&R , &D  , &temp2) ; 
        bigra9m_add(Q , temp  , &Q) ; 
        bigra9m_assign(&R , temp2) ; 
        
        // bigra9m_print(R) ; 
        // bigra9m_print(D) ; 
        // bigra9m_print(temp2) ; 
    }
    
    bigra9m_assign(Qoeff , Q) ; 
    bigra9m_assign(Reminder , R) ; 
    
}

// here it is like 
// the range provided concerns **a**
static void brz_assign_range(BigInt *a ,BigInt b , int start , int end ) {
    if (end < start || start < 0 || end < 0  )
    {
        fprintf(stderr , "ERROR ; a.len = %d  start : %d  end %d \n" , a->length , start , end) ; 
        return ; 
    }
    if (a->capacity < end - start + 1)
    {
        a->capacity = nextPowerOfTwo(end - start + 1) ; 
        BRZ_ALLOCATE_U64(a->nums , a->capacity)
        memset(a->nums + abs(a->length) , 0x0 , sizeof(uint64_t)*(a->capacity - abs(a->length))) ; 
    }

    int k = 0 ; 
    for (size_t i = start; i <= end; i++)
    {
        a->nums[i] = b.nums[k] ; 
        k++ ; 
    }
    // a->length = k ; 
    
    
}

// here it is like 
// the range provided concerns **b**
static void brz_assign_range2(BigInt *a ,BigInt b , int start , int end ) {
    if (end < start || start < 0 || end < 0  )
    {
        fprintf(stderr , "ERROR ; a.len = %d  start : %d  end %d \n" , a->length , start , end) ; 
        return ; 
    }
    if (a->capacity < end - start + 1)
    {
        a->capacity = nextPowerOfTwo(end - start + 1) ; 
        BRZ_ALLOCATE_U64(a->nums , a->capacity)
        memset(a->nums + abs(a->length) , 0x0 , sizeof(uint64_t)*(a->capacity - abs(a->length))) ; 
    }

    int k = 0 ; 
    for (size_t i = start; i <= end; i++)
    {
        a->nums[k] = b.nums[i] ; 
        k++ ;

    }
    a->length = k ; 
    
    
}


// when n == 1 
static void simple_knuths_algorithm_d(BigInt U , BigInt V ,BigInt *Qoeff , BigInt *Reminder) {
    
    #if DEBUG_KNUTHS
        printf("simple knuth !!!") ; 
    #endif 
    int n = U.length  ; 
    int j = n -1 ; 
    uint64_t r = 0 ; 
    BigInt temp_U , temp_V ;
    // printf("calling init from simple_knuths_algorithm_d for temp_U") ; 
    bigra9m_init_assign(&temp_U , U) ; 
    // printf("calling init from simple_knuths_algorithm_d for temp_V") ; 
    bigra9m_init_assign(&temp_V , V) ; 
    
    
    do {
        // step 3 : Calculate q^

        uint64_t q_hat = (r*BASE + U.nums[j]) / V.nums[0] ; 
        r = (r*BASE + U.nums[j]) % V.nums[0] ; 
        Qoeff->nums[j] = q_hat ; 
        j-- ; 

    } while (j>=0) ; 

    // bigra9m_clears(&temp , &temp2 , NULL) ; 


    while (!bigra9m_is_clean_lastdigit(*Qoeff))
    {
        bigra9m_clean_lastdigit(Qoeff) ; 
    }
    
    while (!bigra9m_is_clean_lastdigit(*Reminder))
    {
        bigra9m_clean_lastdigit(Reminder) ; 
    }
    
    bigra9m_mod2(temp_U , temp_V , *Qoeff , Reminder) ; 

    // printf("calling clears from simple_knuths_algorithm_d for temp_V , temp_U") ; 
    bigra9m_clears(&temp_U , &temp_V , NULL) ; 
}


// fuck this algorithm
// TODO : this algo stills need to do the length correctly plus calculating the reminder ..
static void knuths_algorithm_d(BigInt *U , BigInt *V ,BigInt *Qoeff , BigInt *Reminder) {
    // BigInt U , V ; 
    // bigra9m_init_assign(&U , U_origin ) ; 
    // bigra9m_init_assign(&V , V_origin ) ; 
    
    #if DEBUG_KNUTHS
        printf("knuth's algorithm here !!!!!\n");
        printf("DIVIDEND : \n") ; 
        bigra9m_print(*U); 
        printf("DIVISOR : \n") ; 
        bigra9m_print(*V); 
    #endif
    uint64_t D = (BASE-1) / V->nums[V->length-1] ;
    BigInt temp_U , temp_V ;
    // bigra9m_inits()
    
    // printf("calling init from knuths_algorithm_d for temp_U") ; 
    bigra9m_init_assign(&temp_U , *U) ; 
    // printf("calling init from knuths_algorithm_d for temp_V") ; 
    bigra9m_init_assign(&temp_V , *V) ; 
    
    int m = U->length - V->length ; 
    int j = m ;
    int n = V->length ;
    Qoeff->length = m +1; 
    if (n==1)
    {
        simple_knuths_algorithm_d(*U , *V , Qoeff , Reminder) ; 
        // printf("calling clears from knuths_algorithm_d for temp_V temp_U") ; 

        bigra9m_clears(&temp_U , &temp_V , NULL) ; 
        return ; 
    }
    
    // step 1 : [Normalize]
    while(V->nums[V->length-1] < BASE/2) {
        // uint64_t d = (uint64_t) (BASE-1) / V.nums[V.length-1] ; 
        uint64_t d = 2 ; 
        
        bigra9m_mul_uint64(U , d , U) ;
        bigra9m_mul_uint64(V , d , V) ;
    }  
    
    #if DEBUG_KNUTHS
    if (V->nums[V->length-1] >= BASE/2)
    {
        printf("yes normalized\n") ; 
        printf("DIVIDEND : \n") ; 
        bigra9m_print(*U); 
        printf("DIVISOR : \n") ; 
        bigra9m_print(*V); 

    } else {
        printf("no not normalized\n") ; 

    }
    #endif
    
    /*
        NOTE in this phase , U is supposed to get added a 0 on its left
        make sure to have enough allocated space ...
    */
    m = U->length - V->length ; 
    n = V->length ; 
    Qoeff->length = m +1; 
    
    #if DEBUG_KNUTHS
        printf("m = %d \n" , m) ; 
        printf("n = %d \n" , n) ; 
    #endif    
    // step 2 : [Initilize]
    j = m ; 
    if (j < 0)
    {
        exit(55) ; 
    }
    
    BigInt temp , temp2;
    
    // printf("calling init from knuths_algorithm_d for temp:%p , temp2:%p" , &temp , &temp2) ; 
    bigra9m_inits(&temp , &temp2 , NULL) ; 
    do {
        
        // step 3 : Calculate q^
    #if DEBUG_KNUTHS
        printf("U->nums[j+n] = %lu \n" , U->nums[j+n] ) ; 
        printf("U->nums[j+n-1] = %lu \n" , U->nums[j+n-1] ) ; 
        printf("V->nums[n-1] = %lu \n" , V->nums[n-1] ) ; 
        
        printf("U : ")  ;
        bigra9m_print(*U) ; 
    #endif
        uint64_t q_hat = (U->nums[j+n]*BASE + U->nums[j+n-1]) / V->nums[n-1] ; 
        uint64_t r_hat = (U->nums[j+n]*BASE + U->nums[j+n-1]) % V->nums[n-1] ; 

        while (q_hat == BASE ||  q_hat * V->nums[n-2] > BASE*r_hat + U->nums[j+n-2])
        {
            q_hat-- ; 
            r_hat += V->nums[n-1] ; 

            if (r_hat >= BASE)
            {
                break;
            }
            
        }

        // step 4 : [Multiply and Subtract]

        int k = 0 ;  

        brz_assign_range2(&temp , *U , j , j+ n ) ; 
        // temp now has digits of (U) from (j) to (n+j)
        
        bigra9m_assign_uint64_t(&temp2 , 0) ; 

        bigra9m_mul_uint64(V , q_hat , &temp2) ; 

    #if DEBUG_KNUTHS

        printf("temp2 : ") ; 
        bigra9m_print(temp2) ; 
        printf("temp before : ") ; 
        bigra9m_print(temp) ; 


        printf("after cleaning\n") ; 
        printf("temp2 : ") ; 
        bigra9m_print(temp2) ; 
        printf("temp before : ") ; 
        bigra9m_print(temp) ; 
    #endif
        bigra9m_sub(&temp , &temp2 , &temp ) ; 
    #if DEBUG_KNUTHS
        
        printf("temp after: ") ; 
        bigra9m_print(temp) ;
    #endif         
        #if DEBUG_KNUTHS

        // printf("U before :") ; 
        // bigra9m_print(*U) ; 
        // printf("temp before :") ; 
        // bigra9m_print(temp) ; 
        #endif
        brz_assign_range(U , temp , j , j + n) ; 
    #if DEBUG_KNUTHS
        
        // printf("U after :") ; 
        // bigra9m_print(*U) ; 
    #endif        
    
    // step 5 : [Test Reminder]
    #if DEBUG_KNUTHS
        
        printf("q_hat : %lu \n" , q_hat) ; 
        // bigra9m_print(*U) ; 
    #endif        


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
            bigra9m_add(*V , temp , &temp) ;
            

            brz_assign_range(U , temp , j , j + n) ; 

        }
        // step 7 : [Loop on j]
        j-- ; 

    } while (j>=0) ; 
    
    
    
    // printf("calling clears from knuths_algorithm_d for temp %p , temp2 %p" , &temp , &temp2) ; 
    bigra9m_clears(&temp , &temp2 , NULL) ; 


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
    // printf("calling mod2\n") ; 
    bigra9m_mod2(temp_U , temp_V , *Qoeff , Reminder) ; 
    
    #if DEBUG_KNUTHS
    printf("reminder : ????\n");
    bigra9m_print(*Reminder);
    #endif


    bigra9m_clears(&temp_U , &temp_V , NULL) ; 
}



void bigra9m_div(BigInt *a , BigInt *b , BigInt *c ,  BigInt *d) {
    if (bigra9m_is_zero(*b) ) {
        fprintf(stderr , "ERROR : trying to devide on 0 !\n" ) ;
        return ; 
    }

    if (bigra9m_is_zero(*a) )
    {
        bigra9m_assign_uint64_t(c , 0) ; 
        bigra9m_assign(d , *a ) ; 

        return ; 
    }
    if (bigra9m_isStrictlyLowerThanNum(*a , *b))
    {
        bigra9m_assign_uint64_t(c , 0) ; 
        bigra9m_assign(d , *a) ; 
        return ; 
    }
    if (bigra9m_isEqualNum(*a , *b))
    {
        bigra9m_assign_uint64_t(c , 1) ; 
        bigra9m_assign_uint64_t(d , 0) ; 
        return ; 
    }
        
    int sign = 1 ; 

    if (a->length * b->length < 0)
    {
        sign = -1 ; 
    }

    if (a==c || b==c)
    {
        BigInt  temp_a , temp_b ; 
        
        // printf("calling init from bigra9m_div for temp_a %p , temp_b %p" , &temp_a , &temp_b) ; 
        bigra9m_inits(  &temp_a , &temp_b  , NULL) ; 

        bigra9m_assign(&temp_a , *a) ; 
        bigra9m_assign(&temp_b , *b) ; 

        // c gotta be initilized 
        memset(c->nums , 0x0 , sizeof(uint64_t)*c->capacity) ; 
        
        // lets allocate for our result ...

        if (nextPowerOfTwo(abs(temp_a.length)-abs(temp_b.length) + 1 ) >  c->capacity  ) {
            c->capacity = nextPowerOfTwo(abs(temp_a.length)-abs(temp_b.length) + 1) ;
            BRZ_ALLOCATE_U64(c->nums , c->capacity ) 
            memset(c->nums + abs(c->length)  , 0 , sizeof(uint64_t)*(c->capacity -  abs(c->length) )) ;

        }

        // basecase_multiplication(temp_a , temp_b , c) ; 
        knuths_algorithm_d(&temp_a , &temp_b , c , d) ; 

        c->length *= sign ; 
        
        // printf("calling clear from bigra9m_div for temp_a temp_b") ; 
        bigra9m_clears(&temp_a , &temp_b , NULL) ; 
        
    } else {
        BigInt   temp_a , temp_b ; 
        // printf("else calling init from bigra9m_div for temp_a %p , temp_b %p" , &temp_a , &temp_b) ; 
        bigra9m_inits( &temp_a , &temp_b , NULL) ; 

        bigra9m_assign(&temp_a , *a) ; 
        bigra9m_assign(&temp_b , *b) ; 
        
        // c gotta be initilized 
        // memset(c->nums , 0x0 , sizeof(uint64_t)*c->capacity) ; 
        // printf("uh?\n") ; 
        
        // lets allocate for our result ...
        if (nextPowerOfTwo(abs(a->length)-abs(b->length) + 1 ) >  c->capacity  ) {
            c->capacity = nextPowerOfTwo(abs(a->length)-abs(b->length) + 1) ;
            BRZ_ALLOCATE_U64(c->nums , c->capacity ) 
            memset(c->nums + abs(c->length)  , 0 , sizeof(uint64_t)*(c->capacity -  abs(c->length) )) ;

        }

        knuths_algorithm_d(&temp_a , &temp_b , c , d) ; 
        // printf("======================== knuth done \n") ; 
        // basecase_multiplication(*a , *b , c) ; 
        c->length *= sign ; 
        // printf("what?\n") ;
        
        // printf("calling clear from bigra9m_div for temp_a %p temp_b %p" , &temp_a , &temp_b) ; 
        // printf("temp_a.nums = %p \n" , temp_a.nums) ;
        // bigra9m_clear(&temp_a ) ; 
        bigra9m_clears(&temp_a , &temp_b , NULL) ; 
    }


    // knuths_algorithm_d(a , b , c , d) ; 
    // repeated_subtraction_division(a , b , c , d) ; 

}
