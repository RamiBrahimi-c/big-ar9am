#include "../include/bigra9m.h"

#define FANCY_DETAILED_PRINTING 0


#define TEST_MULTIPLICATION(a_str , b_str) do\
{   \
    BigInt a , b , c ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_init(&c);\
    bigra9m_mul(&a , &b , &c);\
    bigra9m_print(c);\
    bigra9m_clears(&a , &b , &c , NULL);\
} while (0);


#define TEST_ADDITION(a_str , b_str) do\
{   \
    BigInt a , b , c ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_init(&c);\
    bigra9m_add(a , b , &c);\
    bigra9m_print(c);\
    bigra9m_clears(&a , &b , &c , NULL);\
} while (0);


#define TEST_SUBTRACTION(a_str , b_str) do\
{   \
    BigInt a , b , c ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_init(&c);\
    bigra9m_sub(&a , &b , &c);\
    bigra9m_print(c);\
    bigra9m_clears(&a , &b , &c , NULL);\
} while (0);


#define TEST_DIVISION(a_str , b_str) do\
{   \
    BigInt a , b , c  , d;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_inits(&c , &d , NULL);\
    bigra9m_div(&a , &b , &c , &d);\
    bigra9m_print(c);\
    bigra9m_clears(&a , &b , &c  , &d, NULL);\
} while (0);

#define TEST_POWER_EXPO(a_str , b_str) do\
{   \
    BigInt a , b , c  ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_init(&c );\
    bigra9m_pow(&a , &b , &c );\
    bigra9m_print(c);\
    bigra9m_clears(&a , &b , &c  , NULL);\
} while (0);


#define TEST_MODULO(a_str , b_str) do\
{   \
    BigInt a , b , c  , d;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_inits(&c , &d , NULL );\
    bigra9m_mod(a , b  , &d );\
    bigra9m_print(d);\
    bigra9m_clears(&a , &b , &c  , &d, NULL);\
} while (0);

#define TEST_MODULO2(a_str , b_str , c_str) do\
{   \
    BigInt a , b , c  , d;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_init_str(&c , c_str);\
    bigra9m_init(&d );\
    bigra9m_mod2(a , b ,c   , &d );\
    bigra9m_print(d);\
    bigra9m_clears(&a , &b , &c , &d , NULL);\
} while (0);

#define TEST_EQ(a_str , b_str) do\
{   \
    BigInt a , b ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    printf("%s\n" , bigra9m_isEqualNum(a , b) == 1 ? "True" : "False") ; \
    bigra9m_clears(&a , &b  , NULL);\
} while (0);

#define TEST_LEQ(a_str , b_str) do\
{   \
    BigInt a , b ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    printf("%s\n" , bigra9m_isLowerThanNum(a , b) == 1 ? "True" : "False") ; \
    bigra9m_clears(&a , &b  , NULL);\
} while (0);

#define TEST_LW(a_str , b_str) do\
{   \
    BigInt a , b ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    printf("%s\n" , bigra9m_isStrictlyLowerThanNum(a , b) == 1 ? "True" : "False") ; \
    bigra9m_clears(&a , &b  , NULL);\
} while (0);

#define TEST_BEQ(a_str , b_str) do\
{   \
    BigInt a , b ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    printf("%s\n" , bigra9m_isBiggerThanNum(a , b) == 1 ? "True" : "False") ; \
    bigra9m_clears(&a , &b  , NULL);\
} while (0);

#define TEST_BG(a_str , b_str) do\
{   \
    BigInt a , b ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    printf("%s\n" , bigra9m_isStrictlyBiggerThanNum(a , b) == 1 ? "True" : "False") ; \
    bigra9m_clears(&a , &b  , NULL);\
} while (0);

#define TEST_MULTIPLICATION_uint64_t(a_str , _b) do\
{   \
    BigInt a  , c ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init(&c );\
    bigra9m_mul_uint64(&a , _b , &c);\
    bigra9m_print(c);\
    bigra9m_clears(&a , &c , NULL);\
} while (0);

#define TEST_PRIMALITY_FERMAT(a_str ) do\
{   \
    BigInt a   ;\
    bigra9m_init_str(&a , a_str);\
    int _result = bigra9m_fermat_primality_test(a );\
    printf("%s\n" , _result==0 ? "composite" : "prime");\
    bigra9m_clears(&a  , NULL);\
} while (0);

#define TEST_PRIMALITY_FERMAT_FAST(a_str ) do\
{   \
    BigInt a   ;\
    bigra9m_init_str(&a , a_str);\
    int _result = bigra9m_fermat_primality_test_fast(a );\
    printf("%s\n" , _result==0 ? "composite" : "prime");\
    bigra9m_clears(&a  , NULL);\
} while (0);

#define TEST_PRIMALITY_MILLER_RABIN(a_str ) do\
{   \
    BigInt a   ;\
    bigra9m_init_str(&a , a_str);\
    int _result = bigra9m_miller_rabin(a  );\
    printf("%s\n" , _result==0 ? "composite" : "prime");\
    bigra9m_clears(&a  , NULL);\
} while (0);

#define TEST_MODULO_EXPO(a_str , b_str , mod_str ) do\
{   \
    BigInt a , b , mod , res   ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_init_str(&mod , mod_str);\
    bigra9m_init(&res);\
    bigra9m_modular_exponentiation(&a , &b , &mod , &res );\
    bigra9m_print(res);\
    bigra9m_clears(&a , &b , &mod , &res , NULL);\
} while (0);


#define TEST_RNG(a_str ) do\
{   \
    BigInt a , b   ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init(&b );\
    setrandom_bigra9m2( &b , &a ) ;  \
    bigra9m_print(b) ; \
    bigra9m_clears(&a , &b  , NULL);\
} while (0);

#define TEST_RNG_PRIME(a_str ) do\
{   \
    BigInt a , b   ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init(&b );\
    generate_prime_bigra9m( &b , &a ) ;  \
    bigra9m_print(b) ; \
    bigra9m_clears(&a , &b  , NULL);\
} while (0);

#define TEST_RNG_PRIME_bits(a_str ) do\
{   int a ; \
    BigInt  b   ;\
    a = atoi(a_str);\
    printf("bits : %d \n" , a) ; \
    bigra9m_init(&b );\
    generate_prime_bigra9m2( &b , a ) ;  \
    bigra9m_print(b) ; \
    bigra9m_clears( &b  , NULL);\
} while (0);

// exactly bits-length
#define TEST_RNG_PRIME_bits2(a_str ) do\
{   int a ; \
    BigInt  b   ;\
    a = atoi(a_str);\
    printf("bits : %d \n" , a) ; \
    bigra9m_init(&b );\
    generate_prime_bigra9m3( &b , a ) ;  \
    bigra9m_print(b) ; \
    bigra9m_clears( &b  , NULL);\
} while (0);

#define TEST_RNG_bits(a_str ) do\
{   int a ;\
    BigInt  b   ;\
    a = atoi(a_str);\
    printf("bits : %d \n" , a) ; \
    bigra9m_init(&b );\
    setrandom_bigra9m( &b , a ) ;  \
    bigra9m_print(b) ; \
    bigra9m_clears( &b  , NULL);\
} while (0);

#define TEST_EVEN(a_str ) do\
{    BigInt  a , b   ;\
    bigra9m_init_str(&b , a_str );\
    printf("%s\n" , bigra9m_isEven(&b)==1 ? "True" : "False") ; \
    bigra9m_clears( &b  , NULL);\
} while (0);

#define TEST_ODD(a_str ) do\
{    BigInt  a , b   ;\
    bigra9m_init_str(&b , a_str );\
    printf("%s\n" , bigra9m_isOdd(&b)==1 ? "True" : "False") ; \
    bigra9m_clears( &b  , NULL);\
} while (0);

#define TEST_GCD(a_str , b_str) do\
{    BigInt  a , b , c   ;\
    bigra9m_init_str(&a , a_str );\
    bigra9m_init_str(&b , b_str );\
    bigra9m_init(&c  );\
    bigra9m_gcd(&a , &b , &c ) ; \
    bigra9m_print(c);\
    bigra9m_clears( &a , &b , &c  , NULL);\
} while (0);

#define TEST_MODULO_INVERSE(a_str , b_str) do\
{   \
    BigInt a , b , c  , d ;\
    bigra9m_init_str(&a , a_str);\
    bigra9m_init_str(&b , b_str);\
    bigra9m_inits(&c , &d , NULL );\
    bigra9m_gcd(&a , &b , &d) ;\
    if (!bigra9m_isEqual_uint64(d , 1)) {printf("pass\n");  } \
    else { \
    bigra9m_modinverse(&a , &b  , &c );\
    bigra9m_print(c);}\
    bigra9m_clears(&a , &b , &c  , &d, NULL);\
} while (0);
