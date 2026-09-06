#include "bigra9m.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>


// we suppose that len < 4
uint32_t buf_to_u64(uchar_t *buf , size_t len , size_t *new_len) {
    uint32_t res = 0 ;
    
    if (len < 4)
    {
        for (size_t i = 0; i < len; i++)
        {
            res |= buf[i] << (i*8) ;         
        }
        *new_len = 1 ; 
    }
    
    *new_len = (size_t) ceil(len / 4) ;

    for (size_t i = 0; i < *new_len ; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            res |= buf[j] << (j*8) ;
            
        }
        
    }
    

}



void bigra9m_import(BigInt *rop, size_t count, size_t size , const void *op) {
    const uint8_t *orig_buf = (const uint8_t *) op ; 
    
    int index = 0 ; 
    int dense_index = 0 ; 

    size_t full_capac = count * size ;
    
    // printf("full capa : %ld\n" , full_capac) ; 
    
    size_t len = ceil(full_capac/4) ;
    len = (len == 0) ? 1 : len ; 
    
    uint32_t *dest = malloc(sizeof(uint32_t) * len) ; 
    if (dest==NULL)
    {
        fprintf(stderr , "ERROR : malloc failed allocating %ld byte :(\n" , sizeof(uint32_t) * len ) ; 
        return ; 
    }
     
    rop->length = len ; 

    if (nextPowerOfTwo(len) >  rop->capacity  ) {
        rop->length = len ;
        rop->capacity = nextPowerOfTwo(len) ;
        BRZ_ALLOCATE_U64(rop->nums , rop->capacity ) 
        memset(rop->nums + len  , 0 , sizeof(uint64_t)*(rop->capacity -  len )) ;
    }
    
    memcpy(dest , orig_buf ,full_capac ) ; 
    for (size_t i = 0; i < len ; i++)
    {
        rop->nums[i] =(uint64_t) (dest[i] % BASE ) ; 
    }
    

    // if (size < 4)
    // {
        
    // } else if (size > 4) {

    // }
    


}



void bigra9m_export(void *rop, size_t *countp , size_t size, const BigInt* op)  {

    if (bigra9m_is_zero(*op))
    {
        *countp = 0 ; 
        return ; 
    }
    
    // basic core here is that we deal with `rop` as an array of bytes ... (i dont give a damn shit about endianess or anything else , )

    uchar_t *buf = (uchar_t *) rop ; 

    *countp = ceil(op->length * sizeof(uint32_t) / size) ;
    *countp = (*countp == 0) ? 1 : *countp ; 

    size_t j = 0 ;
    for (size_t i = 0; i < op->length ; i++)
    {
        // grab `size`-bits 
        uint32_t temp = op->nums[i] ; 
        // put them here : 
        #if 1
        buf[j + 3]  = (temp & 0xff000000) >> 24  ; 
        buf[j + 2]  = (temp & 0x00ff0000) >> 16  ; 
        buf[j + 1]  = (temp & 0x0000ff00) >> 8   ; 
        buf[j ]     =  temp & 0x000000ff         ; 
        #else
        buf[i ]     = (temp & 0xff000000) >> 24  ; 
        buf[i + 1]  = (temp & 0x00ff0000) >> 16  ; 
        buf[i + 2]  = (temp & 0x0000ff00) >> 8   ; 
        buf[i + 3]  =  temp & 0x000000ff         ; 
        
        #endif
        j += 4 ; 
    }
    

}
