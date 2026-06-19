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
vi adj[120001]; //input tree
int par[120001]; //parent in tree
int depth[120001]; //depth of ith node
int spt[18][240001]; //sparse table of euler tour (depth only)
int first[240001]; //first occurrence of ith node in tour
// int s_tag[120001]; //nearest ancestor tagged as s in tree
// int t_tag[120001]; //nearest ancestor tagged as t in tree
vector<tuple<int,int,int>> tag[120001]; //tags on ith vertex: {prisoner, depth of lca, s/t: 0:1}
vi top[120001]; //neighbors of ith vertex in topological dag
int seen[120001]; //seen in top: 0: unseen, 1: in stack, 2: seen

//depth of lca
int lca(int u, int v) {
    int l = first[u], r = first[v];
    if (r<l) swap(l,r);
    int sz = r+1-l, k;
    if (sz<=0) k = 0;
    else k = 31-__builtin_clz(sz);
    return min(spt[k][l], spt[k][r+1-sz]);
}

void solve(int testcase) {
    ii(n);
    //build tree
    fill_n(adj,n,vi());
    fill_n(tag,n,vector<tuple<int,int,int>>());
    // fill_n(s_tag,n,-1);
    // fill_n(t_tag,n,-1);
    par[0] = depth[0] = 0;
    fr(i,0,n-1) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //build depth, first, par, tour
    stack<pair<int,int>> st; //vertex, direction
    st.emplace(0,1);
    int tour_idx = 0;
    auto& tour = spt[0];
    while (!st.empty()) {
        auto [u,d] = st.top();
        st.pop();
        if (d==0) {
            tour[tour_idx++] = par[u];
            continue;
        }
        st.emplace(u,0);
        first[u] = tour_idx;
        tour[tour_idx++] = u;
        for (int v : adj[u]) {
            if (v==par[u]) continue;
            depth[v] = depth[u]+1;
            st.emplace(v,1);
            par[v] = u;
        }
    }
    //build sparse table
    int lim = 31-__builtin_clz(tour_idx);
    fr(k,1,lim+1) {
        fr(i,0,tour_idx+1-(1<<k)) {
            spt[k][i] = min(spt[k-1][i], spt[k-1][i+(1<<(k-1))]);
        }
    }

    //assign tags
    ii(m);
    fill_n(top,m,vi());
    fr(i,0,m) {
        ii(s); ii(t);
        s--; t--;
        int lca_d = lca(s,t);
        tag[s].emplace_back(i,lca_d,0);
        tag[t].emplace_back(i,lca_d,1);
    }
    
    //dfs, assign each path nearest anc s,t
    stack<tuple<int,int,int,int,int>> st1; //vertex, anc s, anc s depth, anc t, anc t depth
    st1.emplace(0,-1,-1,-1,-1);
    while (!st1.empty()) {
        auto [u,s,t,s_d,t_d] = st1.top();
        st1.pop();
        if (!tag[u].empty()) {
            int d = depth[u];
            for (auto [i,lca_d,type1] : tag[u]) {
                //handle tags on same vertex
                for (auto [j,_,type2] : tag[u]) {
                    if (i==j) continue;
                    if (type2==0) {
                        top[i].push_back(j);
                    } else {
                        top[j].push_back(i);
                    }
                }
                //handle nearest anc if in path
                if (s!=-1 && s_d>=lca_d && s!=i) {
                    top[i].push_back(s);
                }
                if (t!=-1 && t_d>=lca_d && t!=i) {
                    top[t].push_back(i);
                }
            }
            for (auto [i,_,type] : tag[u]) {
                if (type==0) {
                    s = i;
                    s_d = d;
                }
                else {
                    t = i;
                    t_d = d;
                }
            }
        }
        for (int v : adj[u]) {
            if (v==par[u]) continue;
            st1.emplace(v,s,t,s_d,t_d);
        }
    }
    //check top for cycles
    int res = 1;
    fill_n(seen,m,0);
    fr(i,0,m) {
        if (seen[i] == 2) continue;
        st.emplace(i,1);
        while (!st.empty() && res==1) {
            auto [u,d] = st.top();
            st.pop();
            if (d==0) {
                seen[u] = 2;
                continue;
            }
            st.emplace(u,0);
            if (seen[u]==1) continue;
            seen[u] = 1;
            for (auto v : top[u]) {
                if (seen[v]==2) continue;
                if (seen[v]==1) {
                    res = 0;
                    break;
                }
                st.emplace(v,1);
            }
        }
    }
    print(ny[res]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}