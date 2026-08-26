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
#include "bigra9m.h"

int main() {

  BigInt a ; 
  bigra9m_init(&a) ; 
  
  bigra9m_assign_str(&a , "123456789") ; 
  bigra9m_print(a) ; 
  
  bigra9m_clear(&a) ; 

    int *arr = malloc(sizeof(int)*5) ; 


    arr = realloc(arr  , sizeof(int)*10) ; 



    free(arr) ; 

    srand(time(NULL)) ; 


    int num ; 
    printf("enter smth : \n") ; 
    // scanf("%d" , &num) ; 

	int high = 100 ;
      // Limit rejection to at most 1 retry on average
    int divisor = RAND_MAX / (high + 1);
    do {
        num = rand() / divisor;
    } while (num > high);


    printf("value of num is %d %x \n" , num , num) ; 
    // func(0x45  , 0x45 , 0x12  , 0x69, 0x89, 0) ; 


    return 0 ; 
}