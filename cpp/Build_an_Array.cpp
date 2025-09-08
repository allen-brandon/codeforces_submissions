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
ll mod = 1000000007;
int a[100001];

void solve(int testcase) {
    lli(n); lli(k);
    //# of turns to build x when y is previous
    auto f = [](int x, int y) -> ll {
        ll res = 1;
        ll exc = 1;
        while ((x&1)==0) {
            if (y==(x>>1)) {
                int z = x;
                while ((z&1)==0) {
                    exc<<=1;
                    z>>=1;
                }
            }
            x>>=1;
            res<<=1;
        }
        return res+1ll-exc;
    };
    ii(x);
    a[0] = x;
    ll prev = f(x,0);
    ll extra = prev;
    fr(i,1,n) {
        ii(x);
        a[i] = x;
        extra+=f(a[i],a[i-1]);
    }
    ll msf = extra;
    fr(i,1,n) {
        int x=a[i], y=a[i-1];
        extra -= prev;
        extra -= f(x,y);
        extra += f(y,x);
        prev = f(x,0);
        extra += prev;
        msf = max(msf,extra);
    }
    print(ny[msf>=k]);

}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}