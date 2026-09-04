#include "../../include/bigra9m.h"
#include <stdlib.h>
// TODO : please test this with script.sh !!!!!!!!!!!!
// NOTE : can work with dynammic approach (apparently ;-;)


int bigra9m_is_zero(BigInt a) {
    return a.length == 0 ; 
}

int bigra9m_is_positive(BigInt a) {
    return a.length > 0 ; 
}

int bigra9m_is_negative(BigInt a) {
    return a.length < 0 ; 
}



int bigra9m_isEqualNum(BigInt a , BigInt b) {
    if (a.length != b.length)
    {
        return 0; 
    }

    for (size_t i = 0; i < (size_t)abs(a.length); i++)
    {
        if (a.nums[i] != b.nums[i])
        {
            return 0 ; 
        }
        
    }
    
    return 1 ;     
}


// TODO : needs more testing
int bigra9m_isBiggerThanNum(BigInt a , BigInt b) {
    if (a.length * b.length < 0)
    {
        return a.length > b.length ;   
    } 
    
    if (a.length > b.length)
    {
        return 1; 
    }else if (a.length < b.length) {
        return 0; 

    } else if (a.length == b.length && a.length > 0) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] >= b.nums[i] ; 
            
        }
        return 1 ; 
       
    } else if (a.length == b.length && a.length < 0 ) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] <= b.nums[i] ; 
            
        }
        return 1; 
    }

    return 1 ;
}

int bigra9m_isStrictlyBiggerThanNum(BigInt a , BigInt b) {
    if (a.length * b.length < 0)
    {
        return a.length > b.length ;   
    } 
    
    if (a.length > b.length)
    {
        return 1; 
    }else if (a.length < b.length) {
        return 0; 

    } else if (a.length == b.length && a.length > 0) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] > b.nums[i] ; 
            
        }
        return 0 ; 
        
        // return a.nums[a.length-1] > b.nums[b.length-1] ; 
    } else if (a.length == b.length && a.length < 0 ) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] < b.nums[i] ; 
            
        }

        return 0; 
    }

    return 0 ;
}


// TODO : needs more testing
int bigra9m_isLowerThanNum(BigInt a , BigInt b) {
    if (a.length * b.length < 0)
    {
        return a.length < b.length ;   
    } 
    
    if (a.length > b.length)
    {
        return 0; 
    }else if (a.length < b.length) {
        return 1; 

    } else if (a.length == b.length && a.length > 0 ) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] <= b.nums[i] ; 
            
        }
        return 1 ; 
       
    } else if (a.length == b.length && a.length < 0 ) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] >= b.nums[i] ; 
            
        }
        return 1 ; 

        return 1; 
    }

    return 1 ;
}

int bigra9m_isStrictlyLowerThanNum(BigInt a , BigInt b) {
    if (a.length * b.length < 0)
    {
        return a.length < b.length ;   
    } 
    
    if (a.length > b.length)
    {
        return 0; 
    }else if (a.length < b.length) {
        return 1; 

    } else if (a.length == b.length && a.length > 0) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] < b.nums[i] ; 
            
        }
        return 0 ; 
       
    } else if (a.length == b.length && a.length < 0 ) {
        for (int i = abs(a.length) -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] > b.nums[i] ; 
            
        }
 
        return 0; 
    }

    return 0 ;
}


int bigra9m_isOdd(BigInt *a) {
    if (a == NULL || a->length == 0 ) 
        return 0 ;
    
        
    return a->nums[0] % 2 == 1 ; 
}

int bigra9m_isEven(BigInt *a) {
    if (a == NULL) 
    return 0 ;
    if (a->length == 0) 
        return 1 ;
    
        
    return a->nums[0] % 2 == 0 ; 
}

int bigra9m_isEqual_uint64(BigInt a , uint64_t b) {
    BigRa9m temp ; // im too lazy gng
    bigra9m_init(&temp) ;
    bigra9m_assign_uint64_t(&temp , b) ; 
    int result = bigra9m_isEqualNum(a , temp) ;  
    bigra9m_clear(&temp) ; 

    return result ; 
}
