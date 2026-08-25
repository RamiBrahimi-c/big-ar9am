#include "bigra9m.h"



 int bigra9m_is_clean_lastdigit(BigInt a) {
    if (a.length == 0)
        return 1 ; 
    return a.nums[abs(a.length)-1] != 0  ;
}
 void bigra9m_clean_lastdigit(BigInt *a) {
    if (a->length==0)
    {
        return ; 
    }
    
    if (a != NULL && a->nums[abs(a->length)-1] ==0)
    {
        if (a->length > 0)
        {
            a->length-- ; 
        } else {
            a->length++ ; 

        }
        
    }
    
} 
