#ifndef BIGRA9M_H
#define BIGRA9M_H


#include <stdint.h>
#include <string.h>



#define BASE 100
#define MAX_LEN 10000



typedef unsigned char uchar_t ; 
typedef struct BigInt BigInt ; 


struct BigInt
{   
    uint64_t nums[MAX_LEN] ; 
    size_t length ; 
};


void bigra9m_init() ;

void bigra9m_print(BigInt number) ;


void bigra9m_assign(BigInt *a , BigInt b  ) ;

void bigra9m_add(BigInt a , BigInt b , BigInt *c ) ;
void bigra9m_mul(BigInt a , BigInt b , BigInt *c) ;
void bigra9m_sub(BigInt a , BigInt b , BigInt *c) ;
void bigra9m_div(BigInt a , BigInt b , BigInt *c) ;













#endif