#include "bigra9m.h"
#include <stdio.h>




int main() {

    BigRa9m a  ,b , c ; 
    bigra9m_inits(&a  ,&b , &c  , NULL) ; 
    
    char arr[] = {0x10 , 0x10 } ; 
    int length = sizeof(arr) / sizeof(arr[0])  ;
    uint64_t buf[1024] ; 
    size_t buf_len = 1 ; 

    bigra9m_import(&a ,length  , sizeof(arr[0])    ,  arr) ; 
    printf("a : {capac : %d , len : %d }   \n" , a.capacity , a.length ) ; 
    bigra9m_print(a) ; 
    
    bigra9m_export(buf , &buf_len , sizeof(uint64_t) , &a) ; 
    printf("exported len : %ld \n" , buf_len) ; 
    for (size_t i = 0; i < buf_len; i++)
    {
        printf(" %u " , buf[i]) ; 
    }printf("\n") ; 
    

    bigra9m_clears(&a  ,&b , &c  , NULL) ; 

    return 0  ;
}