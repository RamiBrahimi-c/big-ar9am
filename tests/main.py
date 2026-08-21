import os

def multiply(a , p, b , q, base):                            # Operands containing rightmost digits at index 1 
    product = [0] * 20                                        # Allocate space for result
    for b_i in range(0 , q): 
        print(f"b_i : {b_i}")                                         # for all digits in b
        carry = 0
        for a_i in range(0 , p) :                                        # for all digits in a
            print(f"a_i : {a_i}")                                         # for all digits in b
            product[a_i + b_i ] += carry + a[a_i] * b[b_i]
            carry = product[a_i + b_i - 1] / base
            product[a_i + b_i ] = product[a_i + b_i ] % base
        product[b_i + p-1] = carry                               # last digit comes from final carry
    return product
 

def fib_r(n) : 
    if n == 0 : 
        return 0
    if n == 1 : 
        return 1
    return fib_r(n-1) + fib_r(n)

# greet.py
import sys

# Ensure an argument was passed
if len(sys.argv) > 1:
    operation = sys.argv[1]
    num1 = int(sys.argv[2]) 
    num2 = int(sys.argv[3])
    # print(f"Hello, {operation}!")
    # print(sys.argv)
    operation_lower = operation.lower()
    match operation_lower : 
        case "mul" :
            result = num1 * num2
            print(f"{num1} {operation} {num2} = {result}")

        case "add" :
            result = num1 + num2
            print(f"{num1} {operation} {num2} = {result}")
        case "sub" :
            result = num1 - num2
            print(f"{num1} {operation} {num2} = {result}")
        case "div" :
            result = int(num1 / num2)
            print(f"{num1} {operation} {num2} = {result}")

        case "mod_exp" :
            num3 = int(sys.argv[4])
            result = pow(num1 , num2 , num3)
            print(f"({num1} ^ {num2}) % {num3} = {result}")

        case _ :
            print(f"idk what operation is this {operation}")
else:
    print("Hello, World!")
