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
ll mod = 998244353;

using res_val = pair<vector<pair<int,int>>,int>;
res_val solve(int n, ll m) {
    ll rem = (ll(n)*ll(n+1))/2 - m;
    if (m<n || rem<0) {
        return res_val({}, -1);
    }
    int k = 0;
    vector<pair<int,int>> res;
    for (int x = n; x>0; --x) {
        if (rem == 0) {
            if (k==0) {
                k = x;
                continue;
            } else {
                res.emplace_back(k,x);
            }
        } else {
            ll cur = min(rem, ll(x-1));
            int v = x-cur;
            res.emplace_back(x-cur,x);
            rem-=cur;
        }
    }
    return res_val(res, k);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    vector<res_val> res(testcases);
    fr(testcase,0,testcases) {
        ii(n); lli(m);
        res[testcase] = solve(n,m);
    }
    fr(i,0,testcases) {
        auto [vec, k] = res[i];
        print(k);
        if (k!=-1) {
            for (auto [u,v] : vec) {
                print(u << " " << v);
            }
        }
    }
}