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
ll modfac[100001];

ll modpow(ll n, ll k) {
    ll res = 1;
    while (k!=0) {
        if (k&1) {
            res = (res*n)%mod;
        }
        n = (n*n)%mod;
        k>>=1;
    }
    return res;
}

ll modcomb(ll n, ll k) {
    if (n<k) return 0;
    ll res = 1;
    if (n<100001) {
        res = (res*modfac[n])%mod;
        res = (res*modpow(modfac[n-k],mod-2))%mod;
    } else {
        fr(i,n+1-k,n+1) {
            res = (res*i)%mod;
        }
    }
    ll inv = modfac[k];
    return (res * modpow(inv,mod-2)) % mod;
}

pair<ll,ll> solve(ll a, ll b, ll k) {
    ll n = (((a-1)*k)%mod+1) % mod;
    ll m = ((((b-1)*modcomb(n,a))%mod * k)%mod + 1)%mod;
    return {n,m};
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    if (modfac[0]==0) {
        modfac[0] = 1;
        fr(i,1,100001) {
            modfac[i] = (modfac[i-1]*i) % mod;
        }
    }
    ii(testcases);
    vector<pair<ll,ll>> res(testcases);
    fr(testcase,0,testcases) {
        lli(a); lli(b); lli(k);
        res[testcase] = solve(a,b,k);
    }
    for (auto [n,m] : res) {
        print(n << " " << m);
    }
}