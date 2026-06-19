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
vi adj[500001];
vector<pair<int,int>> tags[500001]; // idx in res, depth
bitset<500001> res;

void solve(int testcase) {
    ii(n); ii(m);
    adj[1].clear();
    tags[1].clear();
    fr(v,2,n+1) {
        adj[v].clear();
        tags[v].clear();
        ii(u);
        adj[u].emplace_back(v);
    }
    si(s);
    fr(i,0,m) {
        ii(u); ii(d);
        tags[u].emplace_back(i,d);
    }
    //vertex, depth -> freq of chars by depth
    auto dfs = [&](int u, int d, auto& dfs) -> map<int,int> {
        map<int,int> f;
        f[d] ^= 1<<(s[u-1]-'a');
        for (auto v : adj[u]) {
            auto f1 = dfs(v,d+1,dfs);
            if (f1.size()>f.size()) swap(f,f1);
            for (auto& [k,x] : f1) {
                f[k]^=x;
            }
        }
        for (auto [idx,d1] : tags[u]) {
            res[idx] = __builtin_popcount(f[d1])<=1;
        }
        return f;
    };
    dfs(1,1,dfs);
    fr(i,0,m) {
        print(ny[res[i]]);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}