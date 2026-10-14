

import sys
import random



import random


S = 1000


def fermat_primality(p ) :
    if p < 2: return f"p:{p} is composite"
    if p in (2, 3): return f"p:{p} is prime"
    if p % 2 == 0: return f"p:{p} is composite"

    global S
    print(f"S={S}")
    for i in range(1 , S+1) : 
        a = random.randint(2 , p-2)
        # z = (a**r) % p 
        temp = pow(a , p -1 , p)
        if temp != 1 :
            # return False
            return f"p:{p} is composite"

    return f"p:{p} is likely prime"

# factorize_for_miller_rabin(29)
if len(sys.argv) > 1:
    p = int(sys.argv[1])
    print(f"p = {p} ")
    print(f"my miller-rabin : {fermat_primality(p )}")

    import sympy
    print(f"sympy : {sympy.isprime(p)}")
else :
    print("provide a prime number !!!")    
    print("USAGE : [./prgrm] p")    
    sys.exit(0)

