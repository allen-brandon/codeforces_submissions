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
int sieve[10000001];
int factors[10000001][8];

void solve(int testcase) {
    lli(n); lli(m);
    //if n is prime, wn(n,x<n) == 0
    //ret 0
    //if n isn't prime:
    //find nearest prime p<n
    //all wp(n,x<p) == 0
    //for any x | p<=x<n (~150):
    //find largest p|n
    //take p^e < m
    //this Wm(n,x<n) yields smallest v(x) that's different
    if (testcase==1) {
        fill_n(sieve,10000001,0);
        fr(i,2,10000001) {
            if (sieve[i]!=0) continue;
            for (int j = i+i; j<10000001; j+=i) {
                factors[j][sieve[j]++] = i;
            }
        }
    }
    // if (testcase!=4) return;
    if (sieve[n]==0) {
        print(0);
        return;
    }
    auto v = [&](ll x, ll k, ll e) {
        ll res = 0;
        for (ll i = 1; ; i++) {
            ll y = pow(k,i);
            ll z = x/y;
            if (z==0ll) break;
            res += z;
        }
        return res/e;
    };
    //largest power of largest factor in n <= m, and exponent
    auto find_factors = [&](ll x) -> vll {
        vll res;
        if (sieve[x]==0) res.push_back(x);
        fr(i,0,sieve[x]) res.push_back(factors[x][i]);
        return res;
    };
    // prefix min of lowest possible w(n,x<n)
    vll mi;
    ll cur = inf;
    // for (ll x = n-1; prime_found == 0; x--) {
    for (ll x = n-1; cur!=0ll; x--) {
        vll fac = find_factors(x+1);
        // print(x);
        // printv(fac);
        //compare with x+1
        for (auto p : fac) {
            ll k = p;
            ll e = 1;
            while (k<=m) {
                if (v(x,p,e)!=v(x+1,p,e)) {
                    // if (cur>v(x,p,e)) print("cur changed to " << v(x,p,e) << " at " << x << " based on (" << p << ", " << e << ")");
                    cur = min(cur, v(x,p,e));
                }
                k*=p;
                e++;
            }
        }
        // print("___");
        mi.push_back(cur);
    }
    // printv(mi);
    // partial_sum(mi.begin(), mi.end(), mi.begin(), [](ll x, ll y) { return min(x,y); });
    // printv(mi);'
    ll res = accumulate(mi.begin(),mi.end(),0ll);
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}