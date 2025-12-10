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

bitset<1000001> ind;
ll e[1000001]; //edge weight
int rt[1000001]; //dsu parent
int id[1000001]; //dsu id
int krt[1000001]; //krt vertex for component (<m = edge/internal, >=m = vertex/leaf)
int adj[2000001][2]; //krt children
ll pop[1000001]; //krt pop of odd degree graph vertices in krt subtree
ll costs[1000001]; //cost to link odd degree vertices in krt subtree

int find(int u) {
    int v = rt[u];
    while (rt[v]!=v) v=rt[v];
    rt[u] = v;
    return v;
}

void join(int u, int v, int i) {
    if (id[u]<id[v]) swap(u,v);
    int krt_u = krt[u], krt_v = krt[v];
    adj[i][0] = krt_u;
    adj[i][1] = krt_v;
    krt[v] = i;
    rt[u] = v;
}

void solve(int testcase) {
    ii(n); ii(m);
    iota(krt,krt+n,m);
    iota(rt,rt+n,0);
    fill_n(pop,m,0ll);
    fill_n(costs,m,0ll);
    fr(i,0,n) {
        ind[i] = 0;
    }
    ll res = 0;
    int largest = 0; //largest relevant edge id
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        lli(w);
        ind[u] = ind[u]^1;
        ind[v] = ind[v]^1;
        e[i] = w;
        adj[i][0] = -1;
        adj[i][1] = -1;
        res += w;
        u = find(u);
        v = find(v);
        if (u != v) {
            join(u,v,i); //connect these components with new vertex in krt
            largest = i;
        } else { //redundant edge within component, could possibly lower weights
            adj[i][0] = krt[u];
            krt[u] = i;
            largest = i;
        }
    }
    // if (testcase!=4) return;

    //find # of odd degree vertices in given krt subtree
    stack<tuple<int,int,int>> parse_st;
    parse_st.emplace(largest,largest,1);
    while (!parse_st.empty()) {
        auto [u,p,d] = parse_st.top();
        parse_st.pop();
        if (d==0) {
            for (auto v : adj[u]) {
                if (v==p || v==-1) continue;
                if (v>=m) {
                    pop[u] += ll(ind[v-m]);
                } else {
                    pop[u] += pop[v];
                }
            }
            continue;
        }
        parse_st.emplace(u,p,0);
        pop[u] = 0ll;
        for (auto v : adj[u]) {
            if (v==p || v==-1 || v>=m) continue;
            parse_st.emplace(v,u,1);
        }
    }

    //add cost to match odd degree vertices in given KRT subtree
    //(with current prefix min edge weight along path from root)
    stack<tuple<int,int,ll>> st;
    st.emplace(largest,largest,inf);
    while (!st.empty()) {
        auto [u,p,cost] = st.top();
        st.pop();
        ll cur_pop = pop[u];
        if (cur_pop==0ll) continue;
        //match all vertices through this edge
        if (cost!=inf) res -= (pop[u]/2) * cost;
        cost = min(cost, e[u]);
        res += (pop[u]/2) * cost;
        for (auto v : adj[u]) {
            if (v==p || v>=m || v==-1) continue;
            st.emplace(v,u,cost);
        }
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_input.txt");
    // print(1000000 << " " << 999999);
    // fr(i,2,1000001) {
    //     print(1 << " " << i << " " << 1);
    // }
    // return 0;
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    mt19937 rng(1);
    fr(i,0,1000001) id[i] = rng();
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}