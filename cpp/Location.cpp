#ifdef LOCAL
#include "_pch.hpp"
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#define USE_OUTPUT_FILE(file) freopen(file, "w", stdout);
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define USE_INPUT_FILE(file)
#define USE_OUTPUT_FILE(file)
#endif

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order(), order_of_key()
typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define fr(i,l,r) for (int i=l; i<r; ++i)
#define print(_) cout << _ << "\n";
#define printv(_) for (const auto& x : _) cout << x << ' '; cout << '\n';
#define printm(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
array<pair<int,int>,4> didj = {{{-1,0},{0,1},{1,0},{0,-1}}};
array<string,2> ny = {"No","Yes"};
ll inf = 151515151515151;
int mod = 1000000007;
int a[50001];
int b[50001];
int lz[250]; //lazy val per block
ll mn[250]; //min val per block
pair<int,int> lr[250]; //left/right bounds per block idx
vector<int> fac[50001]; //factors for i
vector<int> pfac[50001]; //prime factors for i
int mul[250][50001]; //min multiple of j in block i
ll dp[250][50001]; //min lcm/gcd in block i (in b) for uniform value j (in a)
tuple<int,int,int> queries[50001];
ll res[50001]; //ans to type 2 queries

void solve(int testcase) {
    ii(n); ii(q);
    int k = int(sqrt(n))+1; //size of blocks
    int m = (n-1)/k+1; //# of blocks
    int lim{}; //max element
    int res_idx{}; //# of type 2 queries
    fill_n(lz,m,-1);
    fr(i,0,m) {
        int l = k*i;
        int r = min(n,k*i+k);
        lr[i] = {l,r};
    }
    fr(i,0,n) {
        ii(x);
        a[i] = x;
        lim = max(lim, x);
    }
    fr(i,0,n) {
        ii(x);
        b[i] = x;
        lim = max(lim, x);
    }

    //input queries
    fr(i,0,q) {
        ii(t);
        if (t==1) {
            ii(l); ii(r); ii(x);
            l--;
            queries[i] = {l,r,x};
            lim = max(lim, x);
        } else {
            ii(l); ii(r);
            l--;
            queries[i] = {l,r,0};
        }
    }
    lim++;

    //precalc factors/prime factors
    for (int i = 1; i < lim; i++) {
        for (int j = i; j<lim; j+=i) {
            fac[j].push_back(i);
        }
    }
    for (int i = 2; i < lim; i++) {
        if (!pfac[i].empty()) continue;
        for (int j = i; j<lim; j+=i) {
            pfac[j].push_back(i);
        }
    }

    //precalc mul
    fr(idx,0,m) {
        auto [l,r] = lr[idx];
        fill_n(mul[idx],lim,mod);
        fr(i,l,r) {
            int x = b[i];
            for (int& d : fac[x]) {
                mul[idx][d] = min(mul[idx][d], x);
            }
        }
    }
    
    //precalc dp
    fr(idx,0,m) {
        auto [l,r] = lr[idx];
        for (int x = 1; x < lim; x++) {
            dp[idx][x] = mul[idx][x]==mod? inf : mul[idx][x]/x;
            for (int& p : pfac[x]) {
                dp[idx][x] = min(dp[idx][x], dp[idx][x/p]*p);
            }
        }
    }

    auto score = [](ll x, ll y) {
        ll g = gcd(x,y);
        return (x/g)*(y/g);
    };

    //set new mn[idx]
    auto update_block = [&](int idx) {
        auto [l,r] = lr[idx];
        ll msf = inf;
        fr(i,l,r) {
            msf = min(msf, score(a[i],b[i]));
        }
        mn[idx] = msf;
    };
    
    //fill block idx with x (left of pivot) and y (right of pivot), recalc mn[idx]
    auto fill_block = [&](int x, int y, int idx, int piv) {
        if (x==-1 && y==-1) return;
        auto [l,r] = lr[idx];
        if (x!=-1) fill(a+l,a+piv,x);
        if (y!=-1) fill(a+piv,a+r,y);
        update_block(idx);
    };
    
    //a[l:r] = x
    auto update = [&](int l, int r, int x) {
        int l_idx = l/k, r_idx = (r-1)/k;
        if (l_idx==r_idx) {
            fill_block(lz[l_idx],lz[l_idx],l_idx,l);
            fr(i,l,r) a[i] = x;
            update_block(l_idx);
            lz[l_idx] = -1;
            return;
        }
        fill_block(lz[l_idx],x,l_idx,l);
        fill_block(x,lz[r_idx],r_idx,r);
        lz[l_idx] = -1;
        lz[r_idx] = -1;
        fr(idx,l_idx+1,r_idx) {
            lz[idx] = x;
            mn[idx] = dp[idx][x];
        }
    };

    //min lcm/gcd for a[l:r]
    auto query = [&](int l, int r) {
        ll ans = inf;
        int l_idx = l/k, r_idx = (r-1)/k;
        if (l_idx==r_idx) {
            fill_block(lz[l_idx],lz[l_idx],l_idx,l);
            lz[l_idx] = -1;
            fr(i,l,r) ans = min(ans,score(a[i],b[i]));
            return ans;
        }
        fill_block(lz[l_idx],lz[l_idx],l_idx,l);
        fill_block(lz[r_idx],lz[r_idx],r_idx,r);
        lz[l_idx] = -1;
        lz[r_idx] = -1;
        fr(i,l,lr[l_idx].second) ans = min(ans,score(a[i],b[i]));
        fr(i,lr[r_idx].first,r) ans = min(ans,score(a[i],b[i]));
        fr(idx,l_idx+1,r_idx) ans = min(ans,mn[idx]);
        return ans;
    };

    //set initial block values
    fr(idx,0,m) {
        update_block(idx);
    }
    
    //resolve queries
    fr(i,0,q) {
        auto [l,r,x] = queries[i];
        if (x!=0) {
            update(l,r,x);
        } else {
            res[res_idx++] = query(l,r);
        }
        // vi test1(a,a+n);
        // printv(test1);
        // vi test2(b,b+n);
        // printv(test2);
        // vi test3(mn,mn+m);
        // printv(test3);
        // vi test4(lz,lz+m);
        // printv(test4);
        // print("");
    }
    fr(i,0,res_idx) {
        print(res[i]);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}