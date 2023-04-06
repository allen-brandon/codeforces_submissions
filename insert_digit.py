cases = int(input())
def solution(x, d):
    for i, c in enumerate(x):
        if c < d:
            return x[:i] + d + x[i:]
    return x + d

for _ in range(cases):
    _, d = input().split()
    print(solution(input(), d))