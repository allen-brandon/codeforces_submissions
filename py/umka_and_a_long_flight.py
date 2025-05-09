
from functools import cache
import time

case = int(input())

@cache
def fib(n):
    if n <= 1: return 1
    else: return fib(n-1)+fib(n-2) 

def solve(n, x, y):
    while n > 1:
        if fib(n+1)-fib(n) <= x < fib(n): return "NO"
        x, y = y, (x-fib(n) if x >= fib(n) else x)
        n-=1
    return "YES"

for _ in range(case):
    n, x, y = [int(x) for x in input().split()]
    #time.sleep(0.01)
    print(solve(n, y-1, x-1))
    