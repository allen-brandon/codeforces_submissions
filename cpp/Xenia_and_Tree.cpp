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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_by_key()
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
int mod = 998244353;
int tour[200002];
int depth[100001];
int first[100001];
int pop[100001];
int res[100001];
bitset<100001> removed;
array<vi,100001> adj;
array<vector<pair<int,int>>,100001> anc;

class SparseTable {
    private:
    vector<vi> table;

    public:
    SparseTable(int n) {
        vi cur; cur.reserve(n);
        fr(i,0,n) cur.push_back(tour[i]);
        table.push_back(cur);
        int j = 1;
        while ((1<<j)<=n) {
            vi cur; cur.reserve(n+1-(1<<j));
            fr(i,0,n+1-(1<<j)) {
                cur.push_back(min(table.back()[i], table.back()[i+(1<<(j-1))]));
            }
            table.push_back(cur);
            ++j;
        }
    }
    int query(int l, int r) {
        int m = r+1-l;
        int j = 0;
        while ((1<<j) <= m) ++j;
        --j;
        return min(table[j][l], table[j][r+1-(1<<j)]);
    }
};

class CentroidTree {
    private:
    vi a;
    public:
    CentroidTree(int n, auto& dist, auto& table) {
        this -> a = vi(n,mod);
        fr(i,0,n) removed[i] = 0;
        // u, n, c
        stack<tuple<int, int, int>> st;
        st.emplace(0,n,-1);
        while (!st.empty()) {
            auto [u,n,c] = st.top();
            st.pop();
            bool centroid = true;
            for (auto v : adj[u]) {
                if (removed[v]) continue;
                int v_n = pop[v];
                if (v_n*2>n) {
                    centroid = false;
                    pop[u] = n-v_n;
                    st.emplace(v,n,c);
                    break;
                }
            }
            if (centroid) {
                removed[u] = 1;
                if (c!=-1) {
                    int d = dist(u,c,table);
                    anc[u].push_back({c,d});
                    for (auto [c2, _] : anc[c]) {
                        anc[u].push_back({c2,dist(u,c2,table)});
                    }
                }
                for (auto v : adj[u]) {
                    if (removed[v]) continue;
                    st.emplace(v,pop[v],u);
                }
            }
        }
    };

    void update(int u) {
        if (a[u]==0) return;
        a[u] = 0;
        for (auto [c,d] : anc[u]) {
            a[c] = min(a[c], d);
        }
    }
    
    int query(int u) {
        int msf = a[u];
        for (auto [c,d] : anc[u]) {
            msf = min(msf, d+a[c]);
        }
        return msf;
    }
};

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    fill_n(adj.begin(), n+1, vi());
    fill_n(anc.begin(), n+1, vector<pair<int,int>>());
    fr(i,0,n-1) {
        ii(u); ii(v);
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int tour_idx = 0;
    //p: parent if x==1 else most recently resolved child
    stack<tuple<int,int,int,int>> st;
    st.emplace(0,-1,0,1);
    while (!st.empty()) {
        auto [u,p,d,x] = st.top();
        st.pop();
        if (x==0) {
            tour[tour_idx++] = d;
            pop[u]+=pop[p];
            continue;
        }
        pop[u] = 1;
        depth[u] = d;
        tour[tour_idx] = d;
        first[u] = tour_idx++;
        for (auto v : adj[u]) {
            if (v==p) continue;
            st.emplace(u,v,d,0);
            st.emplace(v,u,d+1,1);
        }
    }
    SparseTable table(tour_idx);
    auto dist = [](int u, int v, auto& table) -> int {
        int lb = first[u], rb = first[v];
        if (lb>rb) swap(lb, rb);
        int lca_d = table.query(lb, rb);
        return depth[u]+depth[v]-lca_d*2;
    };
    CentroidTree ct(n, dist, table);
    ct.update(0);
    int res_idx = 0;
    fr(q,0,m) {
        ii(t); ii(u);
        --u;
        if (t==1) {
            ct.update(u);
        } else {
            res[res_idx++] = ct.query(u);
        }
    }
    fr(i,0,res_idx) {
        print(res[i]);
    }
}