#include "bigra9m.h"


void bigra9m_gcd(BigInt *a , BigInt *b , BigInt *c) {
    BigInt temp  , temp_a , temp_b ; 
    bigra9m_inits(&temp , &temp_a , &temp_b , NULL  ) ; 

    bigra9m_assign(&temp_a , *a) ; 
    bigra9m_assign(&temp_b , *b) ; 

    while (!bigra9m_is_zero(temp_b))
    {

        bigra9m_mod(temp_a , temp_b , &temp) ;
        bigra9m_assign(&temp_a , temp_b) ; 
        bigra9m_assign(&temp_b , temp) ; 

    }
    
    bigra9m_assign(c , temp_a) ; 

    bigra9m_clears(&temp , &temp_a , &temp_b , NULL  ) ; 
}


