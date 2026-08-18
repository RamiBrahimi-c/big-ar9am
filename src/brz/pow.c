#include "../../include/bigra9m.h"

// NOTE : configured with dynammic approach

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
    bigra9m_inits(&i ,&copy , NULL  );
    
    
    bigra9m_assign_uint64_t(&i , 2);
    // bigra9m_assign_str(&inc , "1");
    // bigra9m_assign_str(res , "1");
    bigra9m_assign(&copy , base);
    // bigra9m_init(res );
    int j = 0;
    
    while (!bigra9m_isStrictlyBiggerThanNum(i , pow))
    {
        // bigra9m_print(base);
        // bigra9m_print(copy);
        
        bigra9m_mul(&base , &copy , res);
        bigra9m_assign(&copy , *res);
        bigra9m_add_1(i , 1 , &i) ;
        j++ ; 
        // bigra9m_print(*res);
    }
    bigra9m_clears(&i ,&copy , NULL  );
    
}

