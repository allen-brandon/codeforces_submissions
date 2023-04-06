cases = int(input())

def solve(k):
    res = k
    x = 10
    while x<=res:
        res += divmod(k, x)[0]
        k = divmod(res, x)[1]
        x//=10
    return res


for _ in range(cases):
    print(solve(int(input())))