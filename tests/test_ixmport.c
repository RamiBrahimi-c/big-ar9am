#include "bigra9m.h"
#include <stdio.h>




int main() {

    BigRa9m a  ,b , c ; 
    bigra9m_inits(&a  ,&b , &c  , NULL) ; 
    bigra9m_assign_str(&a , "78125304527642179820962536583426076273") ;
    // bigra9m_assign_str(&a , "78125304527642179820962536583426076273") ;

    char arr[] = {0x10 , 0x10 } ; 
    int length = sizeof(arr) / sizeof(arr[0])  ;
    uchar_t buf[1024] ; 
    size_t buf_len = 1 ; 

    printf("a : {capac : %d , len : %d }   \n" , a.capacity , a.length ) ; 
    bigra9m_print(a) ; 
    for (size_t i = 0; i < a.length; i++)
    {
        printf(" %lx " , a.nums[i]) ; 
    }printf("\n") ;
    
    bigra9m_export(buf , &buf_len , sizeof(uchar_t) , &a) ; 
    printf("exported len : %ld \n" , buf_len) ; 
    for (size_t i = 0; i < buf_len; i++)
    {
        printf(" %x " , buf[i]) ; 
    }printf("\n") ; 
    
    bigra9m_import(&b ,buf_len  , 1    ,  buf) ; 
    printf("b : {capac : %d , len : %d }   \n" , b.capacity , b.length ) ; 
    bigra9m_print(b) ; 
    for (size_t i = 0; i < b.length; i++)
    {
        printf(" %lx " , b.nums[i]) ; 
    }printf("\n") ; 

    bigra9m_clears(&a  ,&b , &c  , NULL) ; 

    return 0  ;
}