import sys
import random



import random

def random_witnesses(k, n):
    return [random.randrange(2, n-1) for _ in range(k)]

S = 1000
def miller_rabin_deepseek(n, k=1000): # provided by deepseek
    if n < 2: return False
    if n in (2, 3): return True
    if n % 2 == 0: return False

    d, s = n-1, 0
    while d % 2 == 0:
        d //= 2
        s += 1

    for a in random_witnesses(k , n):
        x = pow(a, d, n)
        if x == 1 or x == n-1:
            continue
        for _ in range(s-1):
            x = (x * x) % n
            if x == n-1:
                break
        else:
            return False
    return True

def factorize_for_miller_rabin(p) :

    u = 1
    r = 1
    while (p -1) % u == 0 :
        u = u * 2
    u = int(u/2)

    r = (p-1) // u

    # make `u` number of power of 2
    # u = 4 => 2^(u) = 2^(2) = 4
    t= u
    k = 1
    while t > 2 :
        k = k + 1
        t = t >> 1

    # print(f"testing factorizing : {(p-1)//(2**k)}")
    # print(f"testing factorizing : {(r)==(p-1)//(2**k)}")
    return k , int(r)

def miller_rabin(p , u , r) :
    if p < 2: return f"p:{p} is composite"
    if p in (2, 3): return f"p:{p} is prime"
    if p % 2 == 0: return f"p:{p} is composite"

    global S
    print(f"S={S}")
    for i in range(1 , S+1) : 
        a = random.randint(2 , p-2)
        # z = (a**r) % p 
        z = pow(a , r , p)
        if z != 1 and z != p-1 :
            for j in range(1 , u) :
                z = (z**2) % p
                if z == p-1 : # this line is crucial ...
                    break 
                if z == 1 : 
                    return f"p:{p} is composite"
            if z != p-1 : 
                return f"p:{p} is composite"

    return f"p:{p} is likely prime"

# factorize_for_miller_rabin(29)
if len(sys.argv) > 1:
    p = int(sys.argv[1])
    u , r = factorize_for_miller_rabin(p)
    if (((2**u) * r ) + 1) != p : 
        print("factorizing failed")
        print(f"p = {p} u = {u} r = {r}")
        sys.exit(0)
    print(f"p = {p} u = {u} r = {r}")
    print(f"my miller-rabin : {miller_rabin(p , u , r)}")
    print(f"deepseek's miller-rabin : {miller_rabin_deepseek(p)}")
    import sympy
    print(f"sympy : {sympy.isprime(p)}")
else :
    print("provide a prime number !!!")    
    print("USAGE : [./prgrm] p")    
    sys.exit(0)

