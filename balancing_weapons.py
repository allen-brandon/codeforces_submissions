#import time
cases = int(input())



def solve(n, k, fire, damage):
    original = sorted([fire[i]*damage[i] for i in range(n)])

    msf = n
    best = [1]*n
    #Two pointer to find 
    #Try not changing each gun
    for i in range(n):
        match, valid = 0, 1
        minn, maxx = original[i], original[i]
        #Compare to each other gun
        for j in range(n):
            #Make sure each other gun can be changed to match
            if fire[j] > original[i]+k:
                valid = 0
                break
            if original[i]-(fire[j]*(original[i]//fire[j])) <= k and fire[j]*((original[i]//fire[j])+1)-original[i] <= k:
                match += int(abs(original[j]-original[i])<=k)
                continue
            if original[i]-(fire[j]*(original[i]//fire[j])) <= k: minn = min(minn, fire[j]*(original[i]//fire[j]))
            elif fire[j]*((original[i]//fire[j])+1)-original[i] <= k: maxx = max(maxx, fire[j]*((original[i]//fire[j])+1))
            else: valid = 0
            if maxx-minn > k: valid = 0
            if not valid: break
            match += int(abs(original[j]-original[i])<=k)
        if valid: msf = min(msf, n-match)
        
    return msf

for _ in range(cases):
    #time.sleep(0.1)
    n, k = [int(x) for x in input().split()]
    f = [int(x) for x in input().split()]
    d = [int(x) for x in input().split()]
    print(solve(n, k, f, d))