#include "../include/bigra9m.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    BigRa9m a , b , c ; 

    bigra9m_inits(&a , &b , &c , NULL) ; 
    
    bigra9m_assign_str(&a , "2") ; 

    printf("a initially : ") ; 
    bigra9m_print(a) ;
    
    // bigra9m_ji() ; 
    char *buffer = bigra9m_get_str(&a) ; 
    printf("result -> %s \n" , buffer) ;
    printf("strlen(result) = %ld \n" , strlen(buffer)) ; 
    // for (int i = 0 ; i < strlen(buffer) ; i++) 
    // printf("string got : %c \n" , buffer[i]) ; 
    
    free(buffer)  ; 
    bigra9m_clears(&a , &b , &c , NULL) ; 



    return 0 ; 
}