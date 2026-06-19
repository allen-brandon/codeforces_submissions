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
mt19937 rng(1);

vi adj[120001]; //neighbors of ith vertex in tree
int par[120001]; //parent of i in tree
int par1[120001]; //nearest tagged ancestor of i
pair<int,int> spt[18][240001]; //sparse table of euler tour: {depth, vertex}
int first[120001]; //first/last occurrence of i in euler tour
tuple<int,int,int> stl[120001]; //s/t vertices for ith prisoner
vector<tuple<int,int>> tag[120001]; //tag of ith vertex in tree: {0/1:s/t, jth prisoner, depth of lca of jth (s,t)}
tuple<int,int,int,int> paths[240001]; //all s->lca, t->lca paths: {size, prisoner, endpoint, lca depth}
vi top[120001]; //topological graph of prisoners
vi rev[120001]; //reverse topological graph of prisoners
int depth[120001]; //depth of ith vertex
int rt[120001]; //dsu parent
int id[120001]; //height control
int mn[120001]; //min depth vertex in component
int seen[120001]; //0: unseen, 1: seen and in stack, 2: completed

int find(int u) {
    int v = rt[u];
    while (v!=rt[v]) v = rt[v];
    rt[u] = v;
    return v;
}

int join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u==v) return u;
    if (id[u]<id[v]) swap(u,v);
    rt[u] = v;
    mn[v] = min(mn[v],mn[u],[](int u, int v) { return depth[u]<depth[v]; });
    return v;
}

//{depth,vertex} lca of u and v
int lca(int u, int v) {
    // if (depth[u]<depth[v]) swap(u,v);
    int l1 = first[u];
    int l2 = first[v];
    int l = min(l1,l2);
    int r = max(l1,l2)+1;
    int sz = r-l, j;
    if (sz<=0) j = 0;
    else j = 31-__builtin_clz(sz);
    pair<int,int> res = spt[j][l];
    res = min(res, spt[j][r-(1<<j)]);
    return res.second;
}

void solve(int testcase) {
    ii(n);
    fill_n(adj,n,vi());
    fill_n(tag,n,vector<tuple<int,int>>());
    fr(i,0,n) id[i] = rng();
    fr(i,0,n-1) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //assign depth, parents, first/last occurrence, build tour
    stack<tuple<int,int>> st;
    st.emplace(0,1);
    par[0] = 0;
    depth[0] = 0;
    int tour_idx = 0;
    auto& tour = spt[0];
    while (!st.empty()) {
        auto [u,d] = st.top();
        st.pop();
        int p = par[u];
        if (d==0) {
            tour[tour_idx++] = {depth[p], p};
            continue;
        }
        first[u] = tour_idx;
        tour[tour_idx++] = {depth[u], u};
        st.emplace(u,0);
        for (auto v : adj[u]) {
            if (v==p) continue;
            par[v] = u;
            depth[v] = depth[u]+1;
            st.emplace(v,1);
        }
    }

    //build sparse table
    int k = tour_idx-1;
    int lim = 31-__builtin_clz(k);
    fr(j,1,lim+1) {
        fr(i,0,k+1-(1<<j)) {
            spt[j][i] = min(spt[j-1][i],spt[j-1][i+(1<<(j-1))]);
        }
    }
    ii(m);
    fr(i,0,m) {
        ii(s); ii(t);
        s--; t--;
        int l = lca(s,t);
        stl[i] = {s,t,l};
        tag[s].emplace_back(0,i);
        tag[t].emplace_back(1,i);
    }
    // if (testcase!=3) return;

    //create par1
    st.emplace(0,-1);
    while (!st.empty()) {
        auto [u,p] = st.top();
        st.pop();
        if (!tag[u].empty()) p = u;
        par1[u] = p;
        for (int v : adj[u]) {
            if (v==par[u]) continue;
            st.emplace(v,p);
        }
    }
    
    //assimilate ith prisoner into top/rev from s/t in path up to target depth from u
    auto path = [&](int i, int u, int d1, int type) {
        u = mn[find(u)];
        int d = depth[u];
        while (d>=d1) {
            int v = par1[u];
            if (v==-1 || depth[v]<d1) return;
            for (auto [type1,j] : tag[v]) {
                if (type!=type1 || i==j) continue;
                if (type==0) {
                    top[i].push_back(j);
                } else {
                    rev[j].push_back(i);
                }
            }
            if (u==0) break;
            u = par[mn[join(u,v)]];
            d = depth[u];
        }
    };
    
    //create all paths
    fr(i,0,m) {
        auto [s,t,l] = stl[i];
        int d = depth[l];
        paths[i*2] = {d-depth[s],i,s,d};
        paths[(i*2)|1] = {d-depth[t],i,t,d};
    }
    sort(paths,paths+m*2);

    //handle s in paths
    fill_n(top,m,vi());
    iota(rt,rt+n,0);
    iota(mn,mn+n,0);
    fr(idx,0,m*2) {
        auto [sz,i,u,d] = paths[idx];
        path(i,u,d,0);
    }

    //handle t in paths
    fill_n(rev,m,vi());
    iota(rt,rt+n,0);
    iota(mn,mn+n,0);
    fr(idx,0,m*2) {
        auto [sz,i,u,d] = paths[idx];
        path(i,u,d,0);
    }
    fr(i,0,m) {
        top[i].insert(top[i].end(),rev[i].begin(),rev[i].end());
    }
    // fr(i,0,m) {
    //     print(i);
    //     printv(top[i]);
    //     print("___________");
    // }
    //check for cycle
    fill_n(seen,m,0);
    int res = 1;
    fr(i,0,m) {
        if (seen[i]==2) continue;
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
    ll cur = 0;
    fr(i,0,n) {
        cur += top[i].size();
    }
    printv(top[1]);
    print(cur);
    // print(ny[res]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    fio;
    // print(10000);
    // fr(i,1,10000) {
    //     print(i << " " << i+1);
    // }
    // print(5000);
    // fr(i,1,5001) {
    //     print(i << " " << 10001-i);
    // }
    // return 0;d
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}