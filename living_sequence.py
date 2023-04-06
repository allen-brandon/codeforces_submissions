cases = int(input())

def find(x):
    return

def solve(k):
    l, r = 10**13
    while r-l>1:
        mid = l+(r-l)//2
        if find(mid) <= k:
            l = mid
        else:
            r = mid
    return l


for _ in range(cases):
    print(solve(int(input())))