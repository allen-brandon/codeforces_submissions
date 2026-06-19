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
ll mod = 998244353;
vi adj[200001];
int mx[200001]; //max v in subtr of u
pair<int,int> lr[200001]; //left/right indices in tour
ll a[800004]; //euler tour 

//point set, range add
class segment_tree {
    private:
    int n;
    public:
    segment_tree(int m) {
        n = 1<<(32-__builtin_clz(m-1));
        fill_n(a,n*2,0ll);
    }
    ll query(int l, int r) {
        ll res{};
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) res += a[l++];
            if (r&1) res += a[--r];
        }
        return res;
    }
    void set(int i, ll x) {
        for (i+=n, a[i]=x, i>>=1; i>0; i>>=1) {
            a[i] = a[i<<1] + a[i<<1|1];
        }
    }
};

void solve(int testcase) {
    //dp[max_leaf] = 1 to start
    //go u 0->n-1
    // if u>mx[u], dp[u] += dp[all v < u not in u's subtree]
    ii(n);
    fill_n(adj,n,vi());
    fill_n(mx,n,0);
    fr(i,0,n-1) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // if (testcase!=5) return;
    stack<tuple<int,int,int>> stk;
    stk.emplace(n-1,n-1,1);
    int tour_idx = 0;
    while (!stk.empty()) {
        auto [u,p,d] = stk.top();
        stk.pop();
        if (d==0) {
            for (auto v : adj[u]) {
                if (v==p) continue;
                mx[u] = max(mx[u],v);
                mx[u] = max(mx[u],mx[v]);
            }
            lr[u] = {lr[u].first,tour_idx++};
            continue;
        }
        stk.emplace(u,p,0);
        lr[u] = {tour_idx,tour_idx++};
        for (auto v : adj[u]) {
            if (v==p) continue;
            stk.emplace(v,u,1);
        }
    }
    int highest_leaf = 0;
    segment_tree st(tour_idx);
    fr(u,0,n-1) {
        if (adj[u].size()==1) highest_leaf = u;
    }
    st.set(lr[highest_leaf].first, 1); //start at highest leaf
    if (testcase!=4) return;
    print(highest_leaf);
    fr(u,highest_leaf+1,n) {
        if (mx[u]>u) continue;
        print(u << " " << mx[u]);
        auto [l,r] = lr[u];
        ll x = st.query(0,l) + st.query(r,tour_idx);
        if (u==7) {
            print("test" << " " << x);
        }
        if (mx[u]==u-1) {
            auto [l1,r1] = lr[mx[u]];
            x = st.query(l1,l1+1);
        }
        st.set(l,x);
    }
    // print("___");
    auto [l,r] = lr[n-1];
    ll res = st.query(l,l+1);
    print(res%mod);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}