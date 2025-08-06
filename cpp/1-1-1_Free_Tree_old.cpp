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

struct chash {
    static const int RANDOM = 1010101010;
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(int x) const { return hash_f(x)^RANDOM; }
};

ll inf = 151515151515151;
ll mod = 998244353;
ll res[200001];
int col[200001];
ll b[200001]; //sum of active edges
// array<gp_hash_table<int,ll,chash>,200001> cntr; //sum of edge weights by color
array<map<int,ll>,200001> cntr; //sum of edge weights by color
array<vector<pair<int,ll>>,200001> adj; //all edges
array<vector<pair<int,ll>>,200001> adj1; //all edges between central nodes

void testcase() {
    ii(n); ii(q);
    int th = sqrt(n)+3000;
    ll total = 0ll;
    fill_n(b,n+1,0ll);
    fill_n(adj.begin(),n+1,vector<pair<int,ll>>());
    fill_n(adj1.begin(),n+1,vector<pair<int,ll>>());
    // fill_n(cntr.begin(),n+1,gp_hash_table<int,ll,chash>());
    fill_n(cntr.begin(),n+1,map<int,ll>());
    fr(i,1,n+1) {
        ii(x);
        col[i] = x;
    }
    fr(i,0,n-1) {
        ii(u); ii(v); lli(c);
        adj[u].emplace_back(v,c);
        adj[v].emplace_back(u,c);
        b[u] += c*(col[u]!=col[v]);
        b[v] += c*(col[u]!=col[v]);
        total+=c*(col[u]!=col[v]);
    }
    fr(u,1,n+1) {
        if (adj[u].size()<=th) continue;
        for (auto [v,c] : adj[u]) {
            cntr[u][col[v]]+=c;
            if (adj[v].size()>th) {
                adj1[u].emplace_back(v,c);
            }
        }
    }
    fr(i,0,q) {
        ii(u); ii(x);
        int y = col[u];
        col[u] = x;
        if (adj[u].size()>th) {
            total += cntr[u][y];
            total -= cntr[u][x];
            for (auto [v,c] : adj1[u]) {
                cntr[v][y]-=c;
                if (cntr[v][y]==0) cntr[v].erase(y);
                cntr[v][x]+=c;
            }
        } else {
            ll old = 0, cur = 0;
            for (auto [v,c] : adj[u]) {
                old += c*(y!=col[v]);
                cur += c*(x!=col[v]);
                b[v] -= c*(y!=col[v]);
                b[v] += c*(x!=col[v]);
                if (adj[v].size()>th) {
                    cntr[v][y]-=c;
                    if (cntr[v][y]==0) cntr[v].erase(y);
                    cntr[v][x]+=c;
                }
            }
            total += cur-old;
            b[u] = cur;
        }
        res[i] = total;
    }
    fr(i,0,q) {
        print(res[i]);
    }
    // print("___________________");
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}