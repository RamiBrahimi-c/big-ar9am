#ifndef BIGRA9M_H
#define BIGRA9M_H


#include <stdint.h>
#include <string.h>

#include "RandomLib---Cross-Platform-Random-Number-Generator/random.h"

#define BASE ((1ULL<<32))
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

// init our BigRa9m from a string , like init and assign at the same time ; 
void bigra9m_init_str(BigInt *a , const char *num_str) ;
// init our BigInt from another BigInt , like init and assogn from another BigInt 
int bigra9m_init_assign(BigInt *a , BigInt b  ) ;



// NOTE : maybe we should consider making every parameter a pointer 

//  elementary opeartion gng (dummy not optimized not sure even if they are BUG-LESS ) 
//  c is the result of a OP b (OP = * , + , - , /)
//  c = a OP b 
void bigra9m_add(BigInt a , BigInt b , BigInt *c ) ;
void bigra9m_mul(BigInt *a , BigInt *b , BigInt *c) ;
void bigra9m_sub(BigInt *a , BigInt *b , BigInt *c) ;
void bigra9m_div(BigInt *a , BigInt *b , BigInt *c , BigInt *d) ;
// same as div , we just dont need the reminder here 
void bigra9m_div2(BigInt *a , BigInt *b , BigInt *c ) ;

// `c = a * b` calculates product of BigInt `a` with a uint64_t `b`
// **NOTE** : `a` could be negative here .
void bigra9m_mul_uint64(BigInt *a , uint64_t b , BigInt *c) ;
// `c = a + b` calculates addition of BigInt `a` with a uint64_t `b`
// **NOTE** : `a` could **NOT** be negative here .
void bigra9m_add_1(BigInt a , uint64_t b , BigInt *c ) ;



// calculates `res` = base^(pow) 
void bigra9m_pow(BigInt *base , BigInt *pow , BigInt *res) ;

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

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Functions below are like comparison functions and returns 0 (False) or 1 (True) ///////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// a == 0 ? 
int bigra9m_is_zero(BigInt a) ;
// a > 0 ? strictly positive 
int bigra9m_is_positive(BigInt a) ;
// a < 0 ? negative positive
int bigra9m_is_negative(BigInt a) ;

// a >= b
int bigra9m_isBiggerThanNum(BigInt a , BigInt b) ;
// a > b
int bigra9m_isStrictlyBiggerThanNum(BigInt a , BigInt b) ;
// a == b
int bigra9m_isEqualNum(BigInt a , BigInt b) ;
// a < b
int bigra9m_isLowerThanNum(BigInt a , BigInt b) ;
// a <= b
int bigra9m_isStrictlyLowerThanNum(BigInt a , BigInt b) ;

// a == b , b is uint64_t here 
int bigra9m_isEqual_uint64(BigInt a , uint64_t b) ;

// a % 2 == 1
int bigra9m_isOdd(BigInt *a) ;
// a % 2 == 0
int bigra9m_isEven(BigInt *a) ;

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Functions below doesnt touch memory but just manipulate length ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


// is last digit not a zero ?
int bigra9m_is_clean_lastdigit(BigInt a) ;
// if last digit is not a zero then get rid of it .
void bigra9m_clean_lastdigit(BigInt *a) ;


///////////////////////////////////////////////////////////////////////////////////////////////////
/// Functions below are necessary cuz they are the responsible for freeing memory , /////////////// 
/// of course , after calling one of the `init` functions previously //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


// it cleans the BigInt that was set before by `bigra9m_init` or `bigra9m_inits` 
// to free resources and avoid memory leaks ...
void bigra9m_clear(BigInt *a) ; 
// same as `bigra9m_clear` but handles one or more parameters .
void bigra9m_clears(BigInt *a  , ...) ; 



// fermat test on primality
int bigra9m_fermat_primality_test(BigInt p) ;
// fermat test but done with modular exponentiation and is very fast
int bigra9m_fermat_primality_test_fast(BigInt p) ;

// modular exponentiation to calculate : 
// `res = (base ^ exponent) % modulus `
void bigra9m_modular_exponentiation(BigInt *base , BigInt *exponent , BigInt *modulus, BigInt *res) ;

// miller-rabin test for primality 
int bigra9m_miller_rabin(BigInt p ) ;

// set a random BigRa9m in range 0..(2^bits -1)
int setrandom_bigra9m(BigInt *a  , int bits) ;
// set a random BigRa9m in range 0..high
int setrandom_bigra9m2(BigInt *a , BigInt *high )  ;


// set a random prime BigRa9m in range 0..high
int generate_prime_bigra9m(BigInt *a , BigInt *high) ;
// set a random prime BigRa9m in range 0..(2^bits -1)
int generate_prime_bigra9m2(BigInt *a , int bits) ;
// set a random prime BigRa9m to exactly bits-length random prime number (meant to be used in for cryptography)
int generate_prime_bigra9m3(BigInt *a , int bits) ;


// calculates grand common divisor between `a` and `b`
// `c = gcd(a,b)`
void bigra9m_gcd(BigInt *a , BigInt *b , BigInt *c) ;
// calculates the modulo inverse of `a` , 
// `c = a^(-1) mod b `, or `a * c = 1 mod b` 
void bigra9m_modinverse(BigInt *a , BigInt *b , BigInt *c) ;


// *****************************************************************************************************************************
// *****************************************************************************************************************************
// these section has 2 interesting functions , import/export 
// *import* : from a buffer or an array of length @count and size of @size for each cell into a BigRa9m @rop
// *export* : from a BigRa9m @rop into a buffer or an array of length @countp and size of @size for each cell  
// *****************************************************************************************************************************
// *****************************************************************************************************************************

// NOTES : also i might go back and do :
// TODO : consider this signature : 
//      bigra9m_import(BigInt *rop , size_t count, int order, size_t size, int endian, size_t nails , const void *op)                       
//      bigra9m_export(BigInt *rop , size_t *countp, int order, size_t size, int endian, size_t nails, , const void *op)                       
// (pov : maybe not with @nails)

// TODO : a further explanation is needed here !!! on how these 2 work exactly


void bigra9m_import(BigInt *rop, size_t count, size_t size , const void *op) ;
void bigra9m_export(void *rop, size_t *countp , size_t size, const BigInt* op) ; 


#endif