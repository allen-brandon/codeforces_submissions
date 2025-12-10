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
ll mod = 998244353;
ll a[5001];
ll dp[5001][5001][2];

void solve(int testcase) {
    ii(m);
    map<int,ll> d;
    fr(i,0,m) {
        ii(x);
        d[x]++;
    }
    int n = d.size();
    int i = 0;
    for (auto [x,f] : d) {
        a[i++] = f;
    }
    fr(i,0,n) {
        fr(j,0,m) {
            fr(k,0,1) {
                dp[i][j][k] = -1;
            }
        }
    }
    if (testcase!=1) return;
    sort(a,a+n,[](ll x, ll y) {return x>y;});
    // vll test(a,a+n);
    // printv(test);
    auto dfs = [](int i, int j, int x, int n, int m, auto& dfs) {
        if (j>=a[0]) x = 1;
        if (i==n) return x? 1ll : 0ll;
        if (dp[i][j][x]!=-1) return dp[i][j][x];
        ll res = 0;
        if (j >= a[i]) {
            res = (res + dfs(i+1,j,x,n,m,dfs)) % mod;
        }
        fr(k,1,a[i]+1) {
            ll ub = a[i]-k;
            ll lb = ((a[i]-k-1)/k)+1;
            res = (res + (ub+1-lb)*dfs(i+1,max(j,k),x,n,m,dfs)) % mod;
        }
        dp[i][j][x] = res;
        return res;
    };
    ll res = dfs(0,0,1,n,m,dfs);
    res = (res + dfs(1,a[0],0,n,m,dfs)) % mod;
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}