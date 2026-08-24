#include "../include/bigra9m.h"
#include <stdio.h>


int main() {


    BigInt a ; 
    bigra9m_init(&a ) ; 

    bigra9m_assign_uint64_t(&a , 13) ; 
    
    int result = bigra9m_miller_rabin(a  ) ; 
    printf("%s \n" , result==0 ? "composite" : "prime");



    bigra9m_clear(&a) ; 
    return 0 ;
}