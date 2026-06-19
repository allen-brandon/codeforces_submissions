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
ll mod = 1000000007;
ll fac[40];
ll comb[40][40];

void solve(int testcase) {
    lli(n); lli(k);
    // if (testcase!=6) return;
    fac[0] = 1ll;
    fac[1] = 1ll;
    for (ll i = 2; i<40; i++) {
        fac[i] = fac[i-1]*i;
    }
    fr(i,0,32) {
        fill_n(comb[i],40,0ll);
        comb[i][0] = 1;
        comb[i][1] = i;
        fr(j,2,i+1) {
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
        }
    }
    // fr(i,0,8) {
    //     vll row(comb[i],comb[i]+8);
    //     printv(row);
    // }
    // return;
    auto choose = [](ll n, ll k) {
        return comb[n][k];
    };
    // print(n << " " << k);
    ll bl = 31-__builtin_clz(n);
    ll res = bl+1<=k;
    for (ll i = 0; i < bl; i++) {
        ll cost = i+1;
        ll x = k-cost; //remaining moves
        if (x>=i) {
            res+=(1<<i);
        } else {
            for (ll y = 0ll; y<=x; y++) {
                res += choose(i,y);
            }
        }
    }
    print(n-res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}