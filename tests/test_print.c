#include "../include/bigra9m.h"


#include <stdio.h>


int main() {

    BigRa9m a , b , c ; 

    bigra9m_inits(&a , &b , &c , NULL) ; 
    
    bigra9m_assign_str(&a , "-12345678910111213141516171819") ; 


    bigra9m_print(a) ;
    
    
    
    
    bigra9m_clears(&a , &b , &c , NULL) ; 



    return 0 ; 
}