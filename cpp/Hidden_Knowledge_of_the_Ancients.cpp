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
int a[200001];

void solve(int testcase) {
    ii(n); ii(k); lli(lb); lli(rb);
    lb--; //it's exclusive now
    fr(i,0,n) {
        ii(x);
        a[i] = x;
    }
    // if (testcase!=3) return;
    //>=k, >k
    map<int,ll> c1, c2;
    ll d1 = 0, d2 = 0;
    ll res = 0;
    ll l = 0, m = 0;
    for (ll r = 0; r<n; r++) {
        c1[a[r]]++;
        if (c1[a[r]]==1) d1++;
        c2[a[r]]++;
        if (c2[a[r]]==1) d2++;
        while (m<=r && d1>=k) {
            c1[a[m]]--;
            d1-=(c1[a[m++]]==0);
        }
        while (l<=r && d2>k) {
            c2[a[l]]--;
            d2-=(c2[a[l++]]==0);
        }
        // print(l << " " << m << " " << r);
        ll lb1 = max(lb, r+1ll-m);
        ll rb1 = min(rb, r+1ll-l);
        // print(lb1 << " " << rb1);
        res += max(0ll, rb1 - lb1);
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}