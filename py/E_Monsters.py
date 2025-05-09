#import time
from heapq import *



def solve(n, m, vals, adj):
    root, size = list(range(n)), [1 for _ in range(n)]
    heaps = {}
    def find(a):
        while root[root[a]] != root[a]: root[a] = root[root[a]]
        return root[a]
    def union(a, b):
        a, b = find(a), find(b)
        if a == b: return
        size[a]+=size[b]
        root[b] = a
    #Merge a into b
    def merge(a, b):
        smaller, larger = heaps[a] if a in heaps else [(vals[x], x) for x in adj[a]], heaps[b]
        for x in smaller:
            if find(x[1]) != find(b): heappush(larger, x)
    
    for i in range(n):
        if vals[i] or root[i] != i: continue
        h = [(vals[v], v) for v in adj[i]]
        heaps[i] = h
        heapify(h)
        while h and h[0][0] <= size[i]:
            _, node = heappop(h)
            node = find(node)
            if node == i: continue
            merge(node, i)
            union(i, node)
    print("Yes" if max(size) == n else "No")
            




t = int(input())
for _ in range(t):
    n, m = [int(x) for x in input().split()]
    vals = [int(x) for x in input().split()]
    adj = [[] for _ in range(n)]
    for _ in range(m):
        u, v = [int(x)-1 for x in input().split()]
        adj[u].append(v)
        adj[v].append(u)
    #time.sleep(0.5)
    solve(n, m, vals, adj)