#include "../../include/bigra9m.h"

// NOTE : not configured yet with dynammic approach


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

        // if (!bigra9m_is_negative(temp))
        
            k=0 ; 
            for (size_t i = j; i < j + n + 1; i++)
            {
                U.nums[i] = temp.nums[k]  ; 
                k++ ; 

            }
        // U.length = 

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
