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
int link[200001];
int id[200001];
int dist[200001][2];
bitset<200001> bridges;
bitset<200001> seen;
int edges[200001][2];
vector<pair<int,int>> adj[200001];
int t;

void solve(int testcase) {
    ii(n); ii(m);
    fill_n(adj,n,vector<pair<int,int>>());
    fr(i,0,n+1) {
        link[i] = -1;
        seen[i] = 0;
        id[i] = -1;
    }
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        if (u>v) swap(u,v);
        edges[i][0] = u;
        edges[i][1] = v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    vector<int> path;
    stack<tuple<int,int,int>> st;
    st.emplace(0,-1,1);
    seen[0] = 1;
    while (!st.empty()) {
        auto [u,i,d] = st.top();
        st.pop();
        if (d==0) {
            path.pop_back();
            continue;
        }
        st.emplace(u,i,0);
        path.push_back(i);
        if (u==n-1) break;
        for (auto [v,j] : adj[u]) {
            if (seen[v]==1) continue;
            seen[v] = 1;
            st.emplace(v,j,1);
        }
    }
    fr(i,0,m) bridges[i] = 0;
    t = 0;
    auto dfs = [](int u, int p, auto self) -> void {
        id[u] = t;
        link[u] = t++;
        for (auto [v,i] : adj[u]) {
            if (v==p) continue;
            if (id[v]==-1) {
                self(v,u,self);
                link[u] = min(link[u],link[v]);
                if (link[v]>id[u]) {
                    bridges[i] = 1;
                }
            } else {
                link[u] = min(link[u],id[v]);
            }
        }
    };
    fr(i,0,n) {
        if (id[i]==-1) dfs(i,i,dfs);
        seen[i] = 0;
    }
    sort(path.begin(),path.end());
    queue<int> q;
    for (int i : path) {
        if (i==-1 || bridges[i]==0) continue;
        auto [u,v] = edges[i];
        if (seen[u]==0) {
            seen[u] = 1;
            dist[u][0] = 0;
            dist[u][1] = i;
            q.push(u);
        }
        if (seen[v]==0) {
            seen[v] = 1;
            dist[v][0] = 0;
            dist[v][1] = i;
            q.push(v);
        }
    }
    bool invalid = q.empty();
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v,_] : adj[u]) {
            if (seen[v]==1) continue;
            q.push(v);
            seen[v] = 1;
            dist[v][0] = dist[u][0]+1;
            dist[v][1] = dist[u][1];
        }
    }
    ii(queries);
    vi res;
    res.reserve(queries);
    if (invalid) {
        fr(i,0,queries) {
            ii(u);
            res.push_back(-1);
        }
    } else {
        fr(i,0,queries) {
            ii(u); u--;
            res.push_back(dist[u][1]+1);
        }
    }
    printv(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}