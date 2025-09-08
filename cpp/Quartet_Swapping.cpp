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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_of_key()
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
ll mod = 998244353;

void testcase() {
    ii(n);
    vi a;
    vi b;
    a.reserve(n>>1);
    b.reserve(n>>1);
    fr(i,0,n) {
        ii(x);
        if (i&1) {
            b.push_back(x);
        } else {
            a.push_back(x);
        }
    }
    ordered_set sl;
    int p1 = 0, p2 = 0;
    for (int x : a) {
        int idx = sl.order_of_key(x);
        int inv = sl.size()-idx;
        sl.insert(x);
        p1^=(inv&1);
    }
    sl.clear();
    for (int x : b) {
        int idx = sl.order_of_key(x);
        int inv = sl.size()-idx;
        sl.insert(x);
        p2^=(inv&1);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    vi res;
    res.reserve(n);
    fr(i,0,n) {
        if (i&1) {
            res.push_back(b[i>>1]);
        } else {
            res.push_back(a[i>>1]);
        }
    }
    if (p1 != p2) swap(res[res.size()-1],res[res.size()-3]);
    printv(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}
