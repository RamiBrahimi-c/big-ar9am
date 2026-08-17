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
    uint64_t *nums ; 
    int length ; // if length < 0 then the number is negative , if > 0 then its positive , if 0 its 0 -gmp style- 
    int capacity ; 
};


void bigra9m_print(BigInt number) ;

// proper initialization for BigInt struct which does :
//  - set the .nums[] array to 0
//  - set .length to 0 
//  in short set the struct to `0`
int bigra9m_init(BigInt *) ;

// a function to handle variable length of parameters and initilize each one of them by calling `bigra9m_init` 
int bigra9m_inits(BigInt * , ...) ;


void bigra9m_init_str(BigInt *a , const char *num_str) ;


// NOTE : maybe we should consider making every parameter a pointer 

//  elementary opeartion gng (dummy not optimized not sure even if they are BUG-LESS ) 
//  c is the result of a OP b (OP = * , + , - , /)
//  c = a OP b 
void bigra9m_add(BigInt a , BigInt b , BigInt *c ) ;
void bigra9m_mul(BigInt *a , BigInt *b , BigInt *c) ;
void bigra9m_sub(BigInt a , BigInt b , BigInt *c) ;
void bigra9m_div(BigInt a , BigInt b , BigInt *c , BigInt *d) ;

void bigra9m_mul_uint64(BigInt *a , uint64_t b , BigInt *c) ;
void bigra9m_add_1(BigInt a , uint64_t b , BigInt *c ) ;


// calculates `res` = base^(pow) 
void bigra9m_pow(BigInt base , BigInt pow , BigInt *res) ;

// calculates `c` = `divedend` % `divisor` 
void bigra9m_mod(BigInt dividend , BigInt divisor , BigInt *c) ;

// calculates `c` = `divedend` % `divisor` 
// same as `bigra9m_mod2` just works this way : 
//  reminder = dividend - divisor * quoeff
void bigra9m_mod2(BigInt dividend , BigInt divisor , BigInt quoeff , BigInt *c) ;


////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE : the functions below need to get called AFTER calling one of the **init** functions !!!!!
////////////////////////////////////////////////////////////////////////////////////////////////////

// assigning BigInt b to BigInt a   (a = b) 
void bigra9m_assign(BigInt *a , BigInt b  ) ;
// assign (num_str) a number in string (char *) format to BigInt struct
void bigra9m_assign_str(BigInt *a , const char *num_str) ;
// assign a number x of type`uint64_t` to BigInt *a
int bigra9m_assign_uint64_t(BigInt *a , uint64_t x) ;



int bigra9m_is_zero(BigInt a) ;
int bigra9m_is_positive(BigInt a) ;
int bigra9m_is_negative(BigInt a) ;

int bigra9m_isBiggerThanNum(BigInt a , BigInt b) ;
int bigra9m_isStrictlyBiggerThanNum(BigInt a , BigInt b) ;
int bigra9m_isEqualNum(BigInt a , BigInt b) ;



int bigra9m_is_clean_lastdigit(BigInt a) ;
void bigra9m_clean_lastdigit(BigInt *a) ;

// it cleans the BigInt that was set before by `bigra9m_init` or `bigra9m_inits` 
// to free resources and avoid memory leaks ...
void bigra9m_clear(BigInt *a) ; 
// same as `bigra9m_clear` but handles one or more parameters .
void bigra9m_clears(BigInt *a  , ...) ; 


#endif