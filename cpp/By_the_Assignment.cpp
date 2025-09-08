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
ll mod = 998244353;
int a[200001];
int link[200001];
int col[200001];
int id[200001];
vector<pair<int,int>> adj[200001];
bitset<400001> bridges;
int t;

void solve(int testcase) {
    ii(n); ii(m); ii(x);
    fill_n(adj,n+1,vector<pair<int,int>>());
    fill_n(col,n+1,-1);
    fr(i,0,n+1) {
        link[i] = -1;
        id[i] = -1;
    }
    fr(i,0,m) bridges[i] = 0;
    t = 0;
    fr(i,0,n) {
        ii(y);
        a[i] = y;
    }
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        if (u>v) swap(u,v);
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    // if (testcase!=3) return;
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
    dfs(0,0,dfs);
    ll res = 1;
    fr(i,0,n) {
        if (col[i]!=-1) continue;
        bool found = false;
        vi q = {i};
        col[i] = 1;
        int val = -1;
        while (!q.empty()) {
            vi tmp;
            for (int u : q) {
                if (a[u]!=-1) {
                    if (val==-1) {
                        val = a[u];
                    } else if (val!=a[u]) {
                        print(0);
                        return;
                    }
                }
                for (auto [v,j] : adj[u]) {
                    if (bridges[j]==1) continue;
                    if (col[v]==col[u]) {
                        found = true;
                    }
                    else if (col[v]==-1) {
                        tmp.push_back(v);
                        col[v] = col[u]^1;
                    }
                }
            }
            q.swap(tmp);
        }
        if (found) {
            if (val>0) {
                print(0);
                return;
            }
        } else if (val==-1) {
            res = (res*x) % mod;
        }
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}