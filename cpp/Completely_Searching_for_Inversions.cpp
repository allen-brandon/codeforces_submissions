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
ll mod = 998244353;
vector<pair<int,ll>> adj[100001];
vi inv[100001]; //reverse adj
ll o[100001]; //how many 1s after vertex u
ll z[100001]; //how many 0s after vertex u
ll dp[100001]; //how many inversions inside subgraph at u
int ind[100001];


void solve(int testcase) {
    ii(n);
    stack<int> st;
    fill_n(inv,n,vi());
    fr(u,0,n) {
        adj[u] = vector<pair<int,ll>>();
        ii(x);
        ind[u] = x;
        fr(j,0,x) {
            ii(v); lli(w); v--;
            adj[u].emplace_back(v,w);
            inv[v].push_back(u);
        }
        if (x==0) st.push(u);
    }
    fill_n(o,n,0ll);
    fill_n(z,n,0ll);
    fill_n(dp,n,0ll);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        reverse(adj[u].begin(),adj[u].end());
        for (auto [v,w] : adj[u]) {
            dp[u] = (dp[u] + dp[v]) % mod; //inversions in this subgraph
            dp[u] = (dp[u] + z[v]*w) % mod; //0's in this subgraph with this edge
            dp[u] = (dp[u] + z[u]*w) % mod; //0's after this subgraph with this edge
            dp[u] = (dp[u] + z[u]*o[v]) % mod; //0's after this subraph with ones in this subgraph
            z[u] = (z[u] + z[v]+(w^1)) % mod;
            o[u] = (o[u] + o[v]+w) % mod;
        }
        for (int v : inv[u]) {
            // print("("<<u<<","<<v<<") "<<w);
            if (--ind[v]) continue;
            st.emplace(v);
        }
    }
    // vll test(o,o+n);
    // printv(test);
    // vll test1(z,z+n);
    // printv(test1);
    // vll test2(dp,dp+n);
    // printv(test2);
    print(dp[0]%mod);
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