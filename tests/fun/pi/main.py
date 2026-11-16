import mpmath
mpmath.mp.dps = 10010          # decimal places of precision
pi = mpmath.mp.pi
s = str(pi)
print(len(s.split('.')[1]))    # digits after decimal
print(s[:10002])