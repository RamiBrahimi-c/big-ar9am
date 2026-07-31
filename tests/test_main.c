/*
    a module to test any operations this way : 
    ./[executable] OPERATION_NAME NUMBER_1 NUMBER_2
    
    [OPERATION_NAME]: ADD/SUB/MUL/DIV   (doesnt matter in lowercase or uppercase)
    [NUMBER1]: -?[0-9]+ (any number and - is OPTIONAL)
    [NUMBER2]: -?[0-9]+ (any number and - is OPTIONAL)

*/
#include "bigra9m.h"
#include "utils.h"
#include <stdlib.h>

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


int main(int argc , char *argv[]) {
    if (argc > 1)
    {
        printf("********** TESTING MODE *****************\n") ; 
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
        
        
        
    }
    exit(EXIT_SUCCESS) ; 

}