#ifndef RANDOM_H
#define RANDOM_H

#include <stddef.h>   
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef WIN32
#include <windows.h>
#include <wincrypt.h>
#include <bcrypt.h>

#endif

#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#include <fcntl.h>
#include <unistd.h>

#endif



int getRandomBytes(unsigned char *buffer , size_t length) ; 
int getRandomInt( int high) ;
uint64_t getRandomU64_t(uint64_t high) ;




#ifdef __cplusplus
    }
#endif

#endif 