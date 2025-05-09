cases = int(input())
def solve(n, x1, y1, x2, y2):
    ring1 = min(x1, n-1-x1, y1, n-1-y1)
    ring2 = min(x2, n-1-x2, y2, n-1-y2)
    return abs(ring1-ring2)
for _ in range(cases):
    n, x1, y1, x2, y2 = (int(x) for x in input().split())
    print(solve(n, x1-1, y1-1, x2-1, y2-1))