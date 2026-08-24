#include "random.h"
#include <stdio.h>
#include <string.h>

int getRandomBytes(unsigned char *buffer , size_t length) {
    #ifdef WIN32
        // printf("hi from win32\n");

        NTSTATUS result = BCryptGenRandom( NULL,(BYTE *) buffer, length, BCRYPT_USE_SYSTEM_PREFERRED_RNG );

        return (result == 0) ? 0 : 1 ;

    #endif
    #if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        // printf("hi from unix system\n");
        int fd = open("/dev/urandom", O_RDONLY);
        if (fd < 0) {
            fprintf(stderr , "Error opening /dev/urandom");
            return 1;
        }

        size_t bytes_read = 0;

        // 2. Loop to handle partial reads reliably
        while (bytes_read < length) {
            ssize_t result = read(fd, buffer + bytes_read, length - bytes_read);
            
            if (result < 0) {
                fprintf(stderr , "Error reading data");
                close(fd);
                return 1;
            }
            
            bytes_read += result;
        }

        close(fd);

        return 0 ;

    #endif


}


int getRandomInt(int high) {
    if (high < 1)
    {
        fprintf(stderr , "high value cant be < 1\n") ; 
        return 1 ; 
    }
    
    unsigned char temp[4] ; 
    int result = getRandomBytes(temp , 4) ; 
    if (result != 0)
    {
        fprintf(stderr , "an error happened when calling getRandomBytes(..)\n") ; 
        return result ; 
    }
    int res_int  ;
    memcpy(&res_int , temp , sizeof(int)) ; 
    res_int = (res_int < 0 ? -res_int : res_int) % high ; 

    return res_int  ;
}

uint64_t getRandomU64_t(uint64_t high) {
    if (high < 1)
    {
        fprintf(stderr , "high value cant be < 1\n") ; 
        return 1 ; 
    }
    
    // res_int = (res_int < 0 ? -res_int : res_int) % high ; 

    // Limit rejection to at most 1 retry on average
    uint64_t divisor = UINT64_MAX / (high + 1);
    uint64_t num;
    uint64_t res_int  ;
    unsigned char temp[8] ; 

    do {
        int result = getRandomBytes(temp , 8) ; 
        if (result != 0)
        {
            fprintf(stderr , "an error happened when calling getRandomBytes(..)\n") ; 
            return result ; 
        }
        memcpy(&res_int , temp , sizeof(uint64_t)) ; 

        num = res_int / divisor;
    } while (num > high);


    return num  ;
}

