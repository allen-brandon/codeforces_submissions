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
ll a[200001]; //sum of weights of u
int col[200001]; //col of u
int par[200001][2]; //parent of u
ll res[200001]; //answers
array<map<int,ll>,200001> c; //weight of cols for u's children
array<vector<pair<int,ll>>,200001> adj;


void testcase() {
    ii(n); ii(q);
    fr(i,0,n) {
        ii(x);
        col[i] = x;
        adj[i].clear();
        c[i].clear();
        a[i]=0;
    }
    fr(i,0,n-1) {
        ii(u); ii(v); ii(w);
        --u; --v;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    stack<pair<int,int>> st;
    st.emplace(0,0);
    ll cur = 0;
    while (!st.empty()) {
        auto [u,p] = st.top();
        st.pop();
        for (auto [v,w] : adj[u]) {
            a[u]+=w;
            if (v==p) continue;
            cur += w*(col[u]!=col[v]);
            c[u][col[v]]+=w;
            st.emplace(v,u);
            par[v][0] = u;
            par[v][1] = w;
        }
    }
    fr(i,0,q) {
        ii(u); ii(x);
        --u;
        int y = col[u];
        cur+=c[u][y];
        cur-=c[u][x];
        if (u!=0) {
            auto [p,w] = par[u];
            cur+=w*(col[p]==y);
            cur-=w*(col[p]==x);
            c[p][y]-=w;
            c[p][x]+=w;
        }
        res[i] = cur;
        col[u] = x;
    }
    fr(i,0,q) {
        print(res[i]);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}