/*
    a module to test any operations this way : 
    ./[executable] OPERATION_NAME NUMBER_1 NUMBER_2
    
    [OPERATION_NAME]: ADD/SUB/MUL/DIV   (doesnt matter in lowercase or uppercase)
    [NUMBER1]: -?[0-9]+ (any number and - is OPTIONAL)
    [NUMBER2]: -?[0-9]+ (any number and - is OPTIONAL)

*/
#include "bigra9m.h"
#include "utils.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>

#if 0
    #define DEBUG
#endif

void string_to_lowercase(char *str) {
    if (str == NULL) return;
    
    // Loop until the null-terminator is reached
    for (int i = 0; str[i] != '\0'; i++) {
        // Explicitly cast to unsigned char to prevent undefined behavior with negative values
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

uint64_t string_to_uint62(char *str) {
    return strtol(str , NULL , 10) ;
}

int main(int argc , char *argv[]) {
    if (argc > 1)
    {
        // printf("********** TESTING MODE *****************\n") ; 
        
        if (argc > 3 && strcmp(argv[1] , "mod_exp")==0)
            printf("(%s ^ %s) %% %s = " ,argv[2]  , argv[3] , argv[4] ) ;
        else if (argc > 3)
            printf("%s %s %s = " ,argv[2] , argv[1] , argv[3] ) ;
        
        string_to_lowercase(argv[1]);
        if (strcmp(argv[1] , "sub")==0)
        {
            TEST_SUBTRACTION(argv[2] , argv[3]) ; 
        }
        if (strcmp(argv[1] , "add")==0)
        {
            TEST_ADDITION(argv[2] , argv[3]) ; 
        }
        
        if (strcmp(argv[1] , "mul")==0)
        {
            TEST_MULTIPLICATION(argv[2] , argv[3]) ; 
        }
        
        if (strcmp(argv[1] , "div")==0)
        {
            TEST_DIVISION(argv[2] , argv[3]) ; 
        }
        
        if (strcmp(argv[1] , "pow")==0)
        {
            TEST_POWER_EXPO(argv[2] , argv[3]) ; 
        }
        
        if (strcmp(argv[1] , "mod")==0)
        {
            TEST_MODULO(argv[2] , argv[3]) ; 
        }
        
        if (strcmp(argv[1] , "eq")==0)
        {
            TEST_EQ(argv[2] , argv[3]) ; 
        }
        
        if (strcmp(argv[1] , "mod2")==0)
        {
            TEST_MODULO2(argv[2] , argv[3] ,argv[4]) ; 
        }

        if (strcmp(argv[1] , "mod_exp")==0)
        {
            // printf("huh\n") ; 
            TEST_MODULO_EXPO(argv[2] , argv[3] ,argv[4]) ; 
        }

        if (strcmp(argv[1] , "bg")==0)
        {
            TEST_BG(argv[2] , argv[3]) ; 
        }

        if (strcmp(argv[1] , "beq")==0)
        {
            TEST_BEQ(argv[2] , argv[3]) ; 
        }
        // lower than
        if (strcmp(argv[1] , "lw")==0)
        {
            TEST_LW(argv[2] , argv[3]) ; 
        }
        // lower than or equal
        if (strcmp(argv[1] , "leq")==0)
        {
            TEST_LEQ(argv[2] , argv[3]) ; 
        }

        if (strcmp(argv[1] , "mul_u64")==0)
        {
            TEST_MULTIPLICATION_uint64_t(argv[2] , string_to_uint62(argv[3])) ; 
        }
        // fermat test
        if (strcmp(argv[1] , "prime_fr")==0)
        {
            TEST_PRIMALITY_FERMAT(argv[2]) ; 
        }

        // fast fermat test
        if (strcmp(argv[1] , "prime_fr_f")==0)
        {
            TEST_PRIMALITY_FERMAT_FAST(argv[2]) ; 
        }
        // miller-rabin test
        if (strcmp(argv[1] , "prime_mr")==0)
        {
            TEST_PRIMALITY_MILLER_RABIN(argv[2]) ; 
        }
        
        if (strcmp(argv[1] , "rng")==0)
        {
            TEST_RNG(argv[2]) ; 
        }

        if (strcmp(argv[1] , "rng_bits")==0)
        {
            TEST_RNG_bits(argv[2]) ; 
        }
        
        if (strcmp(argv[1] , "rng_prime")==0)
        {
            TEST_RNG_PRIME(argv[2]) ; 
        }

        if (strcmp(argv[1] , "rng_prime_bits")==0)
        {
            TEST_RNG_PRIME_bits(argv[2]) ; 
        }

        if (strcmp(argv[1] , "even")==0)
        {
            TEST_EVEN(argv[2]) ; 
        }

        if (strcmp(argv[1] , "odd")==0)
        {
            TEST_ODD(argv[2]) ; 
        }

        if (strcmp(argv[1] , "x")==0)
        {
            printf("result : %lu \n" , string_to_uint62(argv[2])) ;  
        }
    }
    exit(EXIT_SUCCESS) ; 

}