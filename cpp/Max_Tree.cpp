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
vector<pair<int,int>> adj[200001];

void solve(int testcase) {
    ii(n);
    fill_n(adj,n,vector<pair<int,int>>());
    fr(i,0,n-1) {
        ii(u); ii(v); lli(x); lli(y);
        u--; v--;
        adj[u].emplace_back(v,x>y);
        adj[v].emplace_back(u,x<=y);
    }
    // if (testcase!=3) return;
    vi res(n,0);
    auto dfs = [](int u, int p, int l, int r, vi& res, auto self) -> pair<int,int> {
        for (auto [v,dx] : adj[u]) {
            if (v==p) continue;
            auto [l1,r1] = self(v,u,l,r,res,self);
            l = l1; r = r1;
            if (dx==1) {
                res[v] = l++;
            } else {
                res[v] = r--;
            }
        }
        return {l,r};
    };
    auto [l,r] = dfs(0,0,1,n,res,dfs);
    res[0] = l;
    printv(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}