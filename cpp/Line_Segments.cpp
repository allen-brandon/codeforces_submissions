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
    lli(x1); lli(y1); lli(x2); lli(y2);
    ll d1 = (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
    if (n==1) {
        lli(x);
        print(ny[d1==x*x]);
        return;
    }
    ll d2 = 0, msf=0;
    fr(i,0,n) {
        lli(y);
        msf = max(msf,y);
        d2+=y;
    }
    ll mi = max(0ll,msf*2-d2);
    ll ma = d2;
    bool res = mi*mi<=d1 && ma*ma>=d1;
    print(ny[res]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}