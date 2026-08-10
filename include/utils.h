#include "../include/bigra9m.h"


#define TEST_MULTIPLICATION(a_str , b_str) do\
{   printf("================ TESTING MULTIPLICATION ================\n" );\
    BigInt a , b , c ;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    bigra9m_mul(a , b , &c);\
    printf("result : \n" );\
    bigra9m_print(c);\
    printf("=========================================================\n");\
} while (0);


#define TEST_ADDITION(a_str , b_str) do\
{   printf("================ TESTING ADDITION ================\n" );\
    BigInt a , b , c ;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    bigra9m_add(a , b , &c);\
    printf("result : \n" );\
    bigra9m_print(c);\
    printf("=========================================================\n");\
} while (0);


#define TEST_SUBTRACTION(a_str , b_str) do\
{   printf("================ TESTING SUBTRACTION ================\n" );\
    BigInt a , b , c ;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    bigra9m_sub(a , b , &c);\
    printf("result : \n" );\
    bigra9m_print(c);\
    printf("=========================================================\n");\
} while (0);


#define TEST_DIVISION(a_str , b_str) do\
{   printf("================ TESTING DIVISION ================\n" );\
    BigInt a , b , c  , d;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    bigra9m_init(&c );\
    bigra9m_init(&d );\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    bigra9m_div(a , b , &c , &d);\
    printf("result : \n" );\
    printf("Qoeff : " );\
    bigra9m_print(c);\
    printf("Reminder : " );\
    bigra9m_print(d);\
    printf("=========================================================\n");\
} while (0);

#define TEST_POWER_EXPO(a_str , b_str) do\
{   printf("================ TESTING POWER ================\n" );\
    BigInt a , b , c  , d;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    bigra9m_init(&c );\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    bigra9m_pow(a , b , &c );\
    printf("result : \n" );\
    bigra9m_print(c);\
    printf("=========================================================\n");\
} while (0);


#define TEST_MODULO(a_str , b_str) do\
{   printf("================ TESTING MODULO ================\n" );\
    BigInt a , b , c  , d;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    bigra9m_init(&c );\
    bigra9m_init(&d );\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    bigra9m_mod(a , b  , &d );\
    printf("result : \n" );\
    bigra9m_print(d);\
    printf("=========================================================\n");\
} while (0);

#define TEST_MODULO2(a_str , b_str , c_str) do\
{   printf("================ TESTING MODULO 2 ================\n" );\
    BigInt a , b , c  , d;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    bigra9m_assign_str(&c , c_str);\
    bigra9m_init(&d );\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    printf("c : \n" );\
    bigra9m_print(c);\
    bigra9m_mod2(a , b ,c   , &d );\
    printf("result : \n" );\
    bigra9m_print(d);\
    printf("=========================================================\n");\
} while (0);

#define TEST_EQ(a_str , b_str) do\
{   printf("================ TESTING EQUALITY ================\n" );\
    BigInt a , b ;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    printf("result : %s \n" , bigra9m_isEqualNum(a , b) == 0 ? "not equal" : "equal" );\
    printf("=========================================================\n");\
} while (0);

#define TEST_BG(a_str , b_str) do\
{   printf("================ TESTING STRICTLY BIGGER ================\n" );\
    BigInt a , b ;\
    bigra9m_assign_str(&a , a_str);\
    bigra9m_assign_str(&b , b_str);\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : \n" );\
    bigra9m_print(b);\
    printf("result : %s \n" , bigra9m_isStrictlyBiggerThanNum(a , b) == 0 ? "false" : "true" );\
    printf("=========================================================\n");\
} while (0);

#define TEST_MULTIPLICATION_uint64_t(a_str , _b) do\
{   printf("================ TESTING MULTIPLICATION with uint62_t ================\n" );\
    BigInt a  , c ;\
    bigra9m_assign_str(&a , a_str);\
    printf("a : \n" );\
    bigra9m_print(a);\
    printf("b : %lu \n" , _b);\
    bigra9m_mul_uint64(a , _b , &c);\
    printf("result : \n"  );\
    bigra9m_print(c);\
    printf("=========================================================\n");\
} while (0);
