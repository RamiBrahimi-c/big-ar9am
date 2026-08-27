#include "../../include/bigra9m.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// NOTE : can work with dynammic approach
#define DEBUG_PRINT 0

void bigra9m_print(BigInt number) {
    // printf("length : (%ld) ||\t" , number.length) ; 
    if (number.length < 0)
    {
        printf("-");
        number.length *= -1 ; 
    } else if (!number.length) {
        printf("0") ; 
        return ; 
    }

    #if 1

    
    int total_num = ceil(log2(BASE) * abs(number.length)) -1;
    total_num = total_num < 1 ? 1 : total_num ;   
    uchar_t *buffer = calloc(total_num ,sizeof(uchar_t) ) ; // calloc instead of malloc just so that valgrind shuts up
    if (buffer == NULL)
    {
        fprintf(stderr , "ERROR : malloc just failed to allocate %ld !!!!\n" ,sizeof(uchar_t)*total_num ) ; 
        return ;
    }
    BigInt a , temp , base;
    bigra9m_inits(&temp , &base , NULL) ;  
    bigra9m_init_assign(&a , number) ;
    
    
    bigra9m_assign_uint64_t(&base , 10) ;  
    int counter = 0 ; 
    // printf("total num : %d \n", total_num ) ; 
    for (size_t i = 0; i < total_num; i++)
    {
        if (bigra9m_is_zero(a))
        {
            break;
        }
        #if DEBUG_PRINT
        printf("a.len : %d\n " , a.length) ; 
        for (size_t i = 0; i < a.length; i++)
        {
            printf(" %lu " , a.nums[i]) ; 
        }printf("\n") ; 
        #endif
        
        bigra9m_div(&a , &base , &a , &temp) ;
        
        #if DEBUG_PRINT
        printf("after :  \n" ) ; 
        printf("a.len : %d \n" , a.length) ; 
        for (size_t i = 0; i < a.length; i++)
        {
            printf(" %lu " , a.nums[i]) ; 
        }printf("\n") ; 
        
        printf("temp : %d \n" , temp.length) ; 
        for (size_t i = 0; i < temp.length; i++)
        {
            printf(" %lu " , temp.nums[i]) ; 
        }printf("\n") ; 
        
        printf("temp.num : %lu \n" ,temp.nums[0] ) ; 
        #endif
        
        if (!temp.length)
        {
            buffer[i] =  '0' ;
            
        } else {
            
            buffer[i] = (temp.nums[0] + '0') ;
        }
            
        
        
        // printf("total num : %lu == %c \n", temp.nums[0] , temp.nums[0] + '0' ) ; 
        if (a.length == 0)
        break; ; 
    }
    
    for (int i = 0; i < total_num ; i++)
    {
        // if ((buffer[buffer[total_num- i - 1 ]] ^ 0x0) == 0 )
        // continue;
        if ( buffer[total_num- i - 1 ] > '9' || buffer[total_num- i - 1 ] < '0'  )
        continue;
        
        printf("%c" , buffer[total_num- i - 1 ]) ; 
    }printf("\n") ; 
    

    free(buffer) ; 
    bigra9m_clears(&a , &temp , &base , NULL) ; 
    
    #endif
    
}
