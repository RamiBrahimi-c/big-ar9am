#include "../include/bigra9m.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX(a,b) (a>b ? a : b) 
#define MIN(a,b) (a<b ? a : b) 
// literally copying gmp style .-.
// reallocating `ptr` to size of `_newsize * sizeof(uint64_t)` WITHOUT initializing the new allocated space to 0 .
//  if realloc returns NULL we return -1 from wherever this macro is called . 
#define BRZ_ALLOCATE_U64(_ptr , _newsize ) do \
{\
    _ptr = realloc(_ptr , _newsize*sizeof(uint64_t)) ;  \
    if (_ptr == NULL) { \
        fprintf(stderr , "ERROR: realloc failed sadly");    \
        return -1;    \
    }  \
} while (0);

static inline int nextPowerOfTwo(int n) {
    if (n <= 1) return 2;
    
    int result = n - 1;
    result |= result >> 1;
    result |= result >> 2;
    result |= result >> 4;
    result |= result >> 8;
    result |= result >> 16;
    result |= result >> 32;
    result++;
    
    // If n was already a power of 2, double the result
    if (result == n) {
        result <<= 1;
    }
    
    return result;
}

