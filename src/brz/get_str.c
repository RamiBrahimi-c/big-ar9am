#include "bigra9m.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG_GETSTR 0

char *bigra9m_get_str(BigInt *number) {
    int sign = 1 ; 
    if (number->length < 0)
    {
        sign = -1 ; 
    
    } else if (!number->length) {
    
        char *buf = malloc(sizeof(char)*2) ;
        if (buf==NULL) {
            fprintf(stderr , "ERROR : malloc failed to allocate two bytes ? (wonder about the chance of this happening)\n") ;
            return NULL ;  
        }
        buf[0] = '0' ; 
        buf[1] = '\0' ; 
        return buf; 
    }


    // ig this is the bottleneck of the whole thing , since im working ONLY with base 10 then the next line is part of the whole thing that might need to get changed if the target base changes
    // plus i am really tired to calculate the exact amount of bytes so i chose this approach to approximate it ~typical engineer ik~
    int total_num = ceil(log10(BASE) * abs(number->length)) ;
    total_num = total_num < 1 ? 1 : total_num ;   

    char *buffer = calloc(total_num ,sizeof(char) ) ; // calloc instead of malloc just so that valgrind shuts up
    if (buffer == NULL)
    {
        fprintf(stderr , "ERROR : calloc just failed to allocate %ld !!!!\n" ,sizeof(uchar_t)*total_num ) ; 
        return NULL;
    }

    BigInt a , temp , base;
    bigra9m_inits(&temp , &base , NULL) ;  
    bigra9m_init_assign(&a , *number) ;
    
    if (bigra9m_is_negative(a)) {
        a.length *= -1 ; 
    }
    
    bigra9m_assign_uint64_t(&base , 10) ;  
    int counter = 0 ; 

    #if DEBUG_GETSTR    
        printf("total num : %d \n", total_num ) ; 
        bigra9m_print(a) ; 
    #endif
    
    for (size_t i = 0; i < total_num; i++)
    {
        bigra9m_div(&a , &base , &a , &temp) ;        
        
        if (!temp.length) buffer[ i ] =  '0' ;
        else              buffer[ i ] = (temp.nums[0] + '0') ;
        
        counter++ ; 
        
        if (bigra9m_is_zero(a)) break;
    }

    #if DEBUG_GETSTR
        printf("total_num : %ld \t counter : %d \n" ,total_num , counter ) ; 
    #endif

    buffer = realloc(buffer , counter + 1) ; // you see +1 cuz i wanna be extra sure and not put '\0' anywhere !!! 
    if (buffer==NULL) {
        fprintf(stderr , "ERROR: failed to realloc to %ld !!! \n" , counter + 1) ; 
    }

    // reversing it : 
    char *beg , *end ; 
    for (int k = 0 ; k < counter / 2 ; k++) {
        char temp = buffer[k] ; 
        buffer[k] = buffer[counter - k - 1 ] ; 
        buffer[counter - k - 1 ] = temp ; 
    }

    buffer[counter] = '\0' ; 

    #if DEBUG_GETSTR
    for (int i = 0; i < counter ; i++)
    {
        #if DEBUG_GETSTR
        printf("===== iteration %d ====\t" , i) ; 
        #endif
        if ( buffer[i ] > '9' || buffer[i ] < '0'  ) continue;
        printf("%c" , buffer[ i ]) ; 
    }printf("\n") ; 
    #endif

    bigra9m_clears(&a , &temp , &base , NULL) ; 
    return buffer ; 

}
