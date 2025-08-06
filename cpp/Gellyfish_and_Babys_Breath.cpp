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
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_by_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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

//2^k % mod
ll twopow(ll k) {
    ll base = 2;
    ll res = 1;
    while (k!=0) {
        if (k&1) {
            res*=base;
            res%=mod;
        }
        k>>=1;
        base*=base;
        base%=mod;
    }
    return res;
}
array<ll,100001> a;
array<ll,100001> b;
array<ll,100001> res;

void solve(ll n) {
    ll p_ma=0, q_ma=0;
    for (int i=0; i<n; ++i) {
        if (a[i]>a[p_ma]) p_ma=i;
        if (b[i]>b[q_ma]) q_ma=i;
        int p, q;
        if (a[p_ma]>b[q_ma]) {
            p = a[p_ma];
            q = b[i-p_ma];
        } else if (b[q_ma]>a[p_ma]) {
            p = a[i-q_ma];
            q = b[q_ma];
        } else if (b[i-p_ma]>a[i-q_ma]) {
            p = a[p_ma];
            q = b[i-p_ma];
        } else {
            p = a[i-q_ma];
            q = b[q_ma];
        }
        res[i] = (twopow(p)+twopow(q)) % mod;
    }

    for (int i=0; i<n; ++i) {
        cout << res[i] << " ";
    }
    cout << "\n";
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    for (int testcase=0; testcase<t; ++testcase) {
        ii(n);
        for (int i=0; i<n; ++i) {
            lli(p);
            a[i] = p;
        }
        for (int i=0; i<n; ++i) {
            lli(q);
            b[i] = q;
        }
        solve(n);
    }
}