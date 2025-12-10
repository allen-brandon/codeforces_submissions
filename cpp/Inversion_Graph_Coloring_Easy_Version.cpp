#ifdef LOCAL
#include "_pch.hpp"
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define USE_INPUT_FILE(file)
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
ll mod = 1000000007;
int a[300];
ll cache[301][301][301];

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        ii(x);
        a[i] = x;
        fr(j,0,n+1) {
            fr(k,0,n+1) {
                cache[i][j][k] = -1;
            }
        }
    }
    // if (testcase!=1) return;
    auto dfs = [](int i, int l, int r, int n, auto self) -> ll {
        if (i==n) return 1ll;
        if (cache[i][l][r]!=-1) return cache[i][l][r];
        ll res = self(i+1,l,r,n,self);
        int x = a[i];
        if (x>=r) {
            res = (res + self(i+1,l,x,n,self)) % mod;
        } else if (l==0) {
            res = (res + self(i+1,x,r,n,self)) % mod;
        } else if (x>=l) {
            res = (res + self(i+1,x,r,n,self)) % mod;
        }
        // print(x << " " << l << " " << r << ": " << res);
        cache[i][l][r] = res;
        return res;
    };
    ll res = dfs(0,0,0,n,dfs);
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}