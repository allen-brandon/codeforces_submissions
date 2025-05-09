case = int(input())

def solve(x, arr):
    n = len(arr)
    last = arr[-1]
    for i in range(n-1, 0, -1):
        arr[i] = min(arr[i], arr[i-1])
    return " ".join([str(x) for x in arr + [last]])

for _ in range(case):
    print(solve(int(input()), [int(x) for x in input().split()]))