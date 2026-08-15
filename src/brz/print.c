#include "../../include/bigra9m.h"
#include <stdio.h>

// NOTE : can work with dynammic approach


void bigra9m_print(BigInt number) {
    // printf("length : (%ld) ||\t" , number.length) ; 
    if (number.length < 0)
    {
        printf("-");
        number.length *= -1 ; 
    } else if (!number.length) {
        printf("0") ; 
    }
    

    for (size_t i = 0 ; i < number.length ; i++)
    {
        uchar_t a = number.nums[number.length-i-1] ; 
        if (a==0 && i == 0)
        {
            printf("0") ; 
        }
        else if (a < 10 && number.length > 1 && i != 0)
        {
            printf("0%d" , a) ; 
        } else if (a ==0 ) {
            printf("00") ; 

        } else {
            printf("%d" , a) ; 

        }
        
        
    }
    printf("\n") ; 
    
}
