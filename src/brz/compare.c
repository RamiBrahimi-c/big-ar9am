#include "../../include/bigra9m.h"


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

    for (size_t i = 0; i < a.length; i++)
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

    } else if (a.length == b.length && a.length != 0) {
        for (int i = a.length -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] >= b.nums[i] ; 
            
        }
        return 0 ; 
       
    } else {
        return 0; 
    }
    
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

    } else if (a.length == b.length && a.length != 0) {
        for (int i = a.length -1 ; i >= 0; i--)
        {
            if (a.nums[i] == b.nums[i])
            {
                continue;
            }
            return a.nums[i] > b.nums[i] ; 
            
        }
        return 0 ; 
        
        // return a.nums[a.length-1] > b.nums[b.length-1] ; 
    } else {
        return 0; 
    }
    
}
