#ifndef BIGRA9M_H
#define BIGRA9M_H


#include <stdint.h>
#include <string.h>



#define BASE 100
#define MAX_LEN 10000



typedef unsigned char uchar_t ; 
typedef struct BigRa9m BigInt ; 
typedef struct BigRa9m BigRa9m ; 


struct BigRa9m
{   
    uint64_t nums[MAX_LEN] ; 
    size_t length ; 
};


void bigra9m_print(BigInt number) ;

// proper initialization for BigInt struct which does :
//  - set the .nums[] array to 0
//  - set .length to 1 
//  in short set the struct to `0`
void bigra9m_init(BigInt *) ;

// assigning BigInt b to BigInt a   (a = b) 
void bigra9m_assign(BigInt *a , BigInt b  ) ;


//  elementary opeartion gng (dummy not optimized not sure even if they are BUG-LESS ) 
//  c is the result of a OP b (OP = * , + , - , /)
//  c = a OP b 
void bigra9m_add(BigInt a , BigInt b , BigInt *c ) ;
void bigra9m_mul(BigInt a , BigInt b , BigInt *c) ;
void bigra9m_sub(BigInt a , BigInt b , BigInt *c) ;
void bigra9m_div(BigInt a , BigInt b , BigInt *c) ;

// assign (num_str) a number in string (char *) format to BigInt struct
void bigra9m_assign_str(BigInt *a , uchar_t *num_str) ; 

#endif