#import time
from collections import Counter
cases = int(input())
def solve(n, e, edges):
    #Soft check for e and v
    #Make sure number of nodes is valid
    if int(n**(1/2))**2!=n or n < 9: return "NO"
    rt = int(n**(1/2))
    #Make sure number of edges is valid
    if rt*(rt+1) != e: return "NO"

    #Build adjacency list
    adj = [[] for _ in range(n)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
    #Make sure adjacencies are correct
    softCheck = {}
    for node in range(n):
        softCheck[len(adj[node])] = softCheck.get(len(adj[node]), 0)+1
    if len(softCheck) > 2: return "NO"
    if softCheck.get(2, 0) != n-rt: return "NO"
    if softCheck.get(4, 0) != rt: return "NO"
    #Tarjan's to find strongly connected components
    seen, idx, link, identity = set(), [-1]*n, [-1]*n, [-1]*n
    def dfs(node, parent):
        idx[node] = len(seen)
        identity[len(seen)] = node
        link[node] = len(seen)
        seen.add(node)
        for neighbor in adj[node]:
            if neighbor == parent: continue
            if neighbor in seen:
                link[node] = min(link[node], idx[neighbor])
            else:
                dfs(neighbor, node)
                link[node] = min(link[node], link[neighbor])
    #Make sur not to start in center cycle
    for i in range(n):
        if len(adj[i]) != 2: continue
        dfs(i, -1)
        break
    else: return "NO"
    flag = Counter(link)
    #Make sure graph is connected
    if -1 in flag: return "NO"
    #Make sure there are rt+1 components
    if len(flag) != rt+1: return "NO"
    #Make sure all compenents are correct size
    freq = Counter(flag.values())
    if len(freq) != 2: return "NO"
    if freq[rt] != 1: return "NO"
    if freq[rt-1] != len(flag)-1: return "NO"
    center = -1
    for node in range(n):
        if flag[link[node]] == rt and len(adj[node]) == 4:
            center = node
            break
    else: return "NO"
    for node in range(n):
        if flag[link[node]] == rt: continue
        if len(adj[node]) == 4 and link[node] != idx[center]: return "NO"
    return "YES"

for _ in range(cases):
    input()
    #input()
    #time.sleep(0.1) #DELETE THIS LINE
    v, e = [int(x) for x in input().split()]
    edges = [None]*e
    for i in range(e):
        edges[i] = [int(x)-1 for x in input().split()]
    print(solve(v, e, edges))