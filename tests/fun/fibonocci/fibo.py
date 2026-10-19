def fibonacci(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b

# Example usage: calculate the 10th Fibonacci number
n = 1000
print(f"Fibonacci number {n} is: {fibonacci(n)}")
