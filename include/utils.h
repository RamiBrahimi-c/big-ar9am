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


