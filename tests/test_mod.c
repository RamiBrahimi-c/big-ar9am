/*
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bigra9m.h"
#include "../include/utils.h"
#include "../include/test.h"

#define N 100


int64_t modInverse(int64_t a, int64_t m) {
    if (m == 1) return 0;
    if (a == 0) return 0;
    
    // Make sure a is within modulus
    a = a % m;
    
    int64_t x0 = 0, x1 = 1;
    int64_t q, t;
    int64_t m0 = m;
    int64_t a_s = a;
    int64_t m_s = m;
    int i = 0 ; 
    while (a_s > 1) {
        printf("================== iteration : %d ==================\n" , i) ; 
        if (m_s == 0) return 0; // Prevent division by zero
        
        q = a_s / m_s;
        t = m_s;
        m_s = a_s % m_s;
        a_s = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
        printf("q : %lld\n" , q) ; 
        printf("t : %lld\n" , t) ; 
        printf("m_s : %lld\n" , m_s) ; 
        printf("a_s : %lld\n" , a_s) ; 
        printf("x0 : %lld\n" , x0) ; 
        printf("x1 : %lld\n" , x1) ; 

        printf("=====================================================\n") ; 
        i++ ; 
    }
    
    if (x1 < 0) {
        x1 += m0;
    }
    
    return (int64_t)x1;
}

int main(int argc , char* argv[])
{
    if (argc > 1)
    {
        printf("in uint64_t %lld \n" , modInverse(6525349 , 5066801)) ;
        return 0 ; 
    }
    

    uint64_t a2 = 0 ; 


    BigInt a  , c  ,d , e , f;
    
    bigra9m_init(&e) ; 
    // bigra9m_init_str(&a , "347743917315751756602767635338") ; 
    // bigra9m_init_str(&c , "27189594572672358713") ; 
    bigra9m_init_str(&a , "720345492") ; 
    bigra9m_init_str(&c , "1217007970222890782168670757093700580186946994928410939559160094010355364677598288516263055662615203741679206348400644292906592198925206720672617760471") ; 
    bigra9m_init_str(&d , "10077888510094265010058794928453996837131964607675418300131786246016662743339366290465040835562407373039467469206297641234746021900731213230123047536670145") ; 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 
    printf("after : \n") ; 

    bigra9m_modular_exponentiation(&a , &c , &d , &e) ; 
    // bigra9m_modinverse(&a , &c , &d) ; 


    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 
    printf("d : ") ; 
    bigra9m_print(d) ; 
    printf("e : ") ; 
    bigra9m_print(e) ; 

    // bigra9m_inits(&d , &e ,  &f, NULL) ;
    
    bigra9m_clears(&a , &c , &d , NULL) ; 

}