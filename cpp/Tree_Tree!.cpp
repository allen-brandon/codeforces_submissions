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
vi adj[200001];
int sz[200001];

void solve(int testcase) {
    ii(n); ii(k);
    fill_n(sz,n+1,1);
    fill_n(adj,n+1,vi());
    fr(i,0,n-1) {
        ii(u); ii(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // if (testcase!=2) return;
    //vertex, parent, direction
    stack<tuple<int,int,int>> st;
    st.emplace(1,1,1);
    while (!st.empty()) {
        auto [u,p,d] = st.top();
        st.pop();
        if (d==0) {
            for (auto& v : adj[u]) {
                if (v==p) continue;
                sz[u] += sz[v];
            }
            continue;
        }
        st.emplace(u,p,0);
        for (auto& v : adj[u]) {
            if (v==p) continue;
            st.emplace(v,u,1);
        }
    }
    // vi test(sz,sz+n+1);
    // printv(test);
    ll res = n;
    st.emplace(1,1,1);
    while (!st.empty()) {
        auto [u,p,_] = st.top();
        st.pop();
        for (auto& v : adj[u]) {
            if (v==p) {
                if (sz[u]>=k) res += n-sz[u];
                continue;
            }
            st.emplace(v,u,1);
            if (n-sz[v]>=k) res += sz[v];
        }
        // print(u << " " << res);
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}