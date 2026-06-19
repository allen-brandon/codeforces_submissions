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
vi adj[120001]; //tree
int depth[120001]; //depth in tree
pair<int,int> lr[120001]; //first/last occurrence in tour
int up[18][120001]; //1<<ith ancestor of v
vi top[5000001]; //neighbors of ith vertex in topological dag
// (0 to n*lim*2 for segments, n*lim*2 to n*lim*2+m for prisoners)
int seen[5000001]; //0:unseen, 1: in st, 2: seen and not in st

void solve(int testcase) {
    ii(n);
    fill_n(adj,n,vi());
    fr(i,0,n-1) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    //assign depth, lr, up[0]
    auto& par = up[0];
    par[0] = depth[0] = 0;
    int tour_idx = 0;
    stack<pair<int,int>> st;
    st.emplace(0,1); //vertex, direction
    while (!st.empty()) {
        auto [u,d] = st.top();
        st.pop();
        if (d==0) {
            lr[u] = {lr[u].first,tour_idx++};
            continue;
        }
        st.emplace(u,0);
        lr[u] = {tour_idx, tour_idx++};
        for (int v : adj[u]) {
            if (v==par[u]) continue;
            depth[v] = depth[u]+1;
            st.emplace(v,1);
            par[v] = u;
        }
    }

    
    //build lca table/segment order
    auto enc = [n](int k, int i, int io) { return 2*(k*n+i)+io; };
    int lim = 32-__builtin_clz(n);
    int offs = enc(lim-1,n,0);
    fill_n(top,offs,vi());
    fr(k,1,lim) {
        fr(i,0,n) {
            up[k][i] = up[k-1][up[k-1][i]];
            //in (implies s)
            top[enc(k,i,0)].push_back(enc(k-1,i,0));
            top[enc(k,i,0)].push_back(enc(k-1,up[k-1][i],0));
            //out (impllied by t)
            top[enc(k-1,i,1)].push_back(enc(k,i,1));
            top[enc(k-1,up[k-1][i],1)].push_back(enc(k,i,1));
        }
    }

    //is u ancestor of v
    auto anc = [](int u, int v) {
        return lr[u].first<=lr[v].first && lr[u].second>=lr[v].second;
    };

    //connect to all segments in path from par[s] to lca(s,t)
    auto path = [&](int i, int s, int t) {
        if (anc(s,t)) {
            if (s==t) return;
            top[i].push_back(enc(0,s,0));
            top[enc(0,s,1)].push_back(i);
            return;
        }
        int u = s;
        for (int k = lim-1; k>=0; k--) {
            if (!anc(up[k][u],t)) {
                top[i].push_back(enc(k,u,0));
                top[enc(k,u,1)].push_back(i);
                u = up[k][u];
            }
        }
        //only include lca itself if it's not t
        if (par[u]==t) {
            top[i].push_back(enc(0,u,0));
            top[enc(0,u,1)].push_back(i);
        } else {
            top[i].push_back(enc(1,u,0));
            top[enc(1,u,1)].push_back(i);
        }
    };

    //build topological ordering
    ii(m);
    fill_n(top+offs,m,vi());
    fr(i,offs,offs+m) {
        ii(s); ii(t);
        s--; t--;
        //connect s endpoint
        top[enc(0,s,0)].push_back(i);
        top[enc(0,s,1)].push_back(i); //s endpoint implied by an t at this spot
        //connect t endpoint
        top[i].push_back(enc(0,t,0));
        top[i].push_back(enc(0,t,1)); //t endpoint implied by any s at this spot
        //connect path segments
        if (!anc(s,t)) path(i,par[s],t);
        if (!anc(t,s)) path(i,par[t],s);
    }

    //ensure no cycles
    int res = 1;
    fill_n(seen,offs+m,0);
    fr(i,offs,offs+m) {
        if (seen[i]==2) continue;
        st.emplace(i,1);
        while (!st.empty() && res==1) {
            auto [u,d] = st.top();
            st.pop();
            if (d==0) {
                seen[u] = 2;
                continue;
            }
            if (seen[u]==1) continue;
            st.emplace(u,0);
            seen[u] = 1;
            for (int v : top[u]) {
                if (seen[v]==2) continue;
                if (seen[v]==1) {
                    res = 0;
                    break;
                }
                st.emplace(v,1);
            }
        }
    }
    // print(lim << " " << n << " " << m);
    // fr(i,0,m) {
    //     print("_______" << i << "_______");
    //     printv(top[i+offs]);
    // }
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