#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>


void func(int a , ...) {
  va_list  ap;

  va_start (ap, a);

  do
    {
    //   mpq_init (x);
        printf("a : %x \n" , a) ; 
      a = va_arg (ap, int);
    }
  while (a != 0);

  va_end (ap);    
}

#define BASE ((__uint64_t) (1ull<<32)) 

// #include "bigra9m.h"
#include <stdint.h>
#include <string.h>

#define CROSSPLATFORM_LITTLE_ENDIAN (*(unsigned char *) &(__uint16_t) {1} == 1 )


void func() {

	static int a = 1 ; 
	
}



int main() {

    uint64_t buffer_u64[3] ;  
    unsigned char buffer_c[] = {0x01 , 0x23 , 0x45 , 0x67 ,
                      0x89 , 0xab , 0xcd , 0xef  , 
                      0x01 , 0x23 , 0x45 , 0x67  } ;  

      memcpy(buffer_u64 , buffer_c , 12 * sizeof(unsigned char)) ; 
    
    printf("buf (u64) : ") ; 
    for (size_t i = 0; i < 3; i++)
    {
		printf(" %lx " , buffer_u64[i]) ; 
    }printf("\n") ; 
    
    printf("buf (uchar) : ") ; 
    for (size_t i = 0; i < 12; i++)
    {
		printf(" %x " , buffer_c[i]) ; 
    }printf("\n") ; 


	__uint32_t num = 0x12345678 ;
	__u_char *buffer = "hi" ;
	__uint64_t mega = (__uint64_t) buffer ; 

	unsigned char cc = (unsigned char) num ;
	printf("%x\n" , cc) ;
	printf("%lu\n" , mega) ;
	if (!CROSSPLATFORM_LITTLE_ENDIAN)
	{
		/* code */
		printf("big endian\n") ; 
	}else {
		printf("little endian\n") ; 
	}
	 
    printf("%d\n" ,  (*(unsigned char *) &(__uint16_t) {1} == 1 ) ) ; 



  exit(EXIT_SUCCESS) ; 
  int c = 55 % BASE ; 
  printf("c : %d in base %lu \n" ,c , BASE ) ; 

  exit(0) ; 
  // BigInt a ; 
  // bigra9m_init(&a) ; 
  
  // bigra9m_assign_str(&a , "123456789") ; 
  // bigra9m_print(a) ; 
  
  // bigra9m_clear(&a) ; 

  //   int *arr = malloc(sizeof(int)*5) ; 


  //   arr = realloc(arr  , sizeof(int)*10) ; 



  //   free(arr) ; 

  //   srand(time(NULL)) ; 


  //   int num ; 
  //   printf("enter smth : \n") ; 
  //   // scanf("%d" , &num) ; 

	// int high = 100 ;
  //     // Limit rejection to at most 1 retry on average
  //   int divisor = RAND_MAX / (high + 1);
  //   do {
  //       num = rand() / divisor;
  //   } while (num > high);


  //   printf("value of num is %d %x \n" , num , num) ; 
    // func(0x45  , 0x45 , 0x12  , 0x69, 0x89, 0) ; 


    return 0 ; 
}