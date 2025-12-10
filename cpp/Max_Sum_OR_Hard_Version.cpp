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

void solve(int testcase) {
    lli(l); lli(r);
    ll lb = l;
    ll n = r+1-l;
    // if (testcase!=4) return;
    auto dfs = [lb](ll l, ll r, int bit, ll offs, vll& res, auto& self) -> void {
        // print(l+offs << " " << r+offs);
        ll x = 1ll<<bit;
        if (l>r) {
            return;
        } else if (l==r) {
            ll lx = l+offs;
            res[lx-lb] = lx;
            return;
        }
        ll z = l&x, z1 = r&x;
        if (z == z1) {
            if (z==0ll) {
                self(l, r, bit-1, offs, res, self);
            } else {
                self(l^x, r^x, bit-1, offs^x, res, self);
            }
            return;
        }
        ll i = 0;
        while (x-1-i>=l && x+i<=r) {
            ll lx = x-1-i+offs, rx = x+i+offs;
            res[lx-lb] = rx;
            res[rx-lb] = lx;
            i++;
        }
        if (x-1-i<l) {
            self(x+i, r, bit, offs, res, self);
        } else {
            self(l, x-1-i, bit, offs, res, self);
        }
    };
    vll res(n);
    ll bit = 0;
    while (1ll<<bit <= r) bit++;
    bit--;
    dfs(l, r, bit, 0, res, dfs);
    auto printsum = [&](vll& a) {
        ll res = 0;
        for (ll i = 0; i < n; i++) {
            res += (l+i) | a[i];
        }
        print(res);
    };
    printsum(res);
    printv(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}