#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
// #include "bigra9m.h"
#include "../include/bigra9m.h"
#include "../include/utils.h"
#include "../include/test.h"
// #include "utils.h"
// #include "test.h"



int main(int argc , char *argv[]) {
    if (argc < 2)
    {
        printf("nah\n") ; 
        return 1 ; 
    }
    
    uint64_t a = 0xffffffffffff ; 
    BigInt c ; 
    int x = 5 ; 

    printf("a = %lu \t %x \n" , a , a) ; 
    // printf("next power of 2 of %d is %d \n" , x , nextPowerOfTwo(x)) ; 
    // bigra9m_init(&c) ; 

    // bigra9m_assign_uint64_t(&c , a) ; 
    bigra9m_init_str(&c ,argv[1] ) ; 

    printf("BASE : %d \n" , BASE) ; 
    printf("capacity : %d \n" , c.capacity) ; 
    printf("length : %d \n" , c.length) ; 

    bigra9m_print(c) ; 



    return 0 ; 
}