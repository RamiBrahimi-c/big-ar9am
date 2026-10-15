#include "bigra9m.h"
#include <stdio.h>




int main() {

    BigRa9m a  ,b , c ; 
    bigra9m_inits(&a  ,&b , &c  , NULL) ; 
    bigra9m_assign_str(&a , "1732584193") ;
    // bigra9m_assign_str(&a , "11995979615323155970225324646634127279766003328522376058975679999443384431222502893756576383323456781833089454226216570710569820048984638890690127185137506777439690887288261780410196104612529552830402829057409279113934815319986829298723597437215540600112506788736853345415387618064362196162305544129834337126140699859923845533139797795121160478779041229468263097371339051334913703533195172812449747655121592774385206373389119658938397578505105228020075415450185207302492279346351530437036812108110311923979703710509097450956811339554260190246448134357082351686008723842670544296207775155778142941957338944078592676111") ;
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
        printf("%x" , buf[i]) ; 
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