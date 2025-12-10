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
vi adj[200001];
int par[200001];

void solve(int testcase) {
    ii(n);
    fill_n(adj,n+1,vi());
    fr(i,0,n-1) {
        ii(u); ii(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // if (testcase!=2) return;
    vector<pair<int,int>> nodes;
    auto dfs = [n](auto& nodes, int u, int p, int d, auto& dfs) -> void {
        nodes.emplace_back(d,u);
        for (int v : adj[u]) {
            if (v==p) continue;
            par[v] = u;
            dfs(nodes, v, u, d+1, dfs);
        }
    };
    dfs(nodes, 1, 1, 0, dfs);
    sort(nodes.begin(),nodes.end());
    vi path = {n};
    while (par[path.back()] != 1) {
        path.push_back(par[path.back()]);
    }
    set pathset(path.begin(),path.end());
    vector<string> res;
    int depth = 0;
    while (!nodes.empty()) {
        if (pathset.contains(nodes.back().second)) {
            nodes.pop_back();
            continue;
        }
        if ((nodes.back().first&1) == (depth&1)) {
            res.push_back("1");
        } else {
            res.push_back("2 " + to_string(nodes.back().second));
            res.push_back("1");
            nodes.pop_back();
        }
        depth++;
    }
    while (path.size() > 1) {
        int u = path.back();
        path.pop_back();
        res.emplace_back("2 " + to_string(u));
        res.push_back("1");

    }
    res.pop_back();
    res.pop_back();
    print(res.size());
    for (auto x : res) {
        print(x);
    }
    print("");
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}