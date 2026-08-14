/*
    module for testing with gmp
*/
#include <gmp.h>
#include <stdio.h>


int main() {

    mpz_t a , b , c ;

    mpz_inits(a , b , c , NULL) ; 

    mpz_set_str(a , "123" , 10) ; 
    mpz_set_str(b , "600" , 10) ; 
    mpz_set_str(c , "544" , 10) ; 

    printf("before : \n");
    gmp_printf("a : %Zd\n" , a) ; 
    gmp_printf("b : %Zd\n" , b) ; 
    gmp_printf("c : %Zd\n" , c) ; 

    // mpz_sub(c , a , c) ; 
    mpz_mod(a , b , c) ; 

    printf("after : \n");
    gmp_printf("a : %Zd\n" , a) ; 
    gmp_printf("b : %Zd\n" , b) ; 
    gmp_printf("c : %Zd\n" , c) ; 


    mpz_clears(a , b , c , NULL) ; 

    return 0 ; 
}