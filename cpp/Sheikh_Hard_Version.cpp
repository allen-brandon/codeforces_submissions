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
pair<int,int> res[200001];
ll a[200001];
//1-indexed
ll spref[200001]; //sum
ll xpref[200001]; //xor
int nxt[200001];
int prv[200001];

void solve(int testcase) {
    ii(n); ii(q);
    spref[0] = 0ll;
    xpref[0] = 0ll;
    fr(i,0,n) {
        lli(x);
        a[i] = x;
        spref[i+1] = spref[i]+x;
        xpref[i+1] = xpref[i]^x;
    }
    int cur = -1;
    fr(i,0,n) {
        if (a[i]!=0) {
            cur = i;
        }
        prv[i] = cur;
    }
    cur = n;
    nxt[n] = n;
    for (int i = n-1; i>=0; i--) {
        if (a[i]!=0) {
            cur = i;
        }
        nxt[i] = cur;
    }
    auto f = [&](int l, int r) -> ll {
        return ll(spref[r+1]-spref[l])-ll(xpref[r+1]^xpref[l]);
    };
    fr(i,0,q) {
        ii(lb); ii(rb);
        lb--; rb--;
        ll x = f(lb,rb);
        if (x==0) {
            res[i] = {lb+1,lb+1};
            continue;
        }
        int l = nxt[lb], r = prv[rb];
        if (l>r) {
            res[i] = {lb+1,lb+1};
            continue;
        }
        //prioritize r
        while (l<r && f(l,r-1)==x) r = prv[r-1];
        while (l<r && f(l+1,r)==x) l = nxt[l+1];
        res[i] = {l+1,r+1};
        while (r<=rb) {
            while (l<r && f(l+1,r)==x) l = nxt[l+1];
            if (r-l < res[i].second-res[i].first) res[i] = {l+1,r+1};
            r = nxt[r+1];
        }
    }
    // if (testcase!=4) return;
    fr(i,0,q) {
        print(res[i].first << " " << res[i].second);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}