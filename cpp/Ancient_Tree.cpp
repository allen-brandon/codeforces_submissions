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
ll a[200001];
int b[200001];
vi adj[200001];

void testcase(int t) {
    ii(n); ii(k);
    fill_n(adj,n+1,vi());
    fr(i,0,n) {
        lli(x);
        a[i] = x;
    }
    fr(i,0,n) {
        ii(x);
        b[i] = x;
    }
    fr(i,0,n-1) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // if (t!=1) return;
    ll res_val = 0;
    ll& res = res_val;
    auto dfs = [](auto& dfs, ll& res, int u, int p) -> set<int> {
        set<int> s;
        int c1 = 0;
        int c2 = 0;
        for (int v : adj[u]) {
            if (v==p) continue;
            set<int> t = dfs(dfs,res,v,u);
            if (t.size()>s.size()) {
                s.swap(t);
            }
            for (auto x : t) {
                if (s.contains(x)) {
                    if (c1==0 || c1==x) {
                        c1 = x;
                    } else {
                        c2 = x;
                    }
                } else {
                    s.insert(x);
                }
            }
        }
        if (b[u]!=0) {
            s.insert(b[u]);
        } else if (c1!=0) {
            b[u] = c1;
        }
        int must = (c1!=0 && c1!=b[u]) || (c2!=0 && c2!=b[u]);
        res+=a[u]*must;
        return s;
    };
    dfs(dfs,res,0,0);
    //things that are dependent on the parent's color
    auto fill = [](auto& fill, int u, int p) -> void {
        if (b[u]==0) {
            b[u] = b[p];
        }
        for (int v : adj[u]) {
            if (v==p) continue;
            fill(fill,v,u);
        }
    };
    if (b[0]==0) {
        b[0] = 1;
    }
    fill(fill,0,0);
    print(res_val);
    vi ret(b,b+n);
    printv(ret);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(t,1,testcases+1) testcase(t);
}