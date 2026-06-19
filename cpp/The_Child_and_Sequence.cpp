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
tuple<ll,ll,ll> a[262145]; //{max,min} in range
ll sz[262145]; //size of ith subtree
ll lz[262145]; //{val, timestamp} of update

struct segment_tree {
    private:
    int n;
    public:
    segment_tree(int n) : n(n) {
        fill_n(sz+n,n,1);
        fill_n(lz,n,-1);
        for (int i = n-1; i>0; i--) {
            sz[i] = sz[i<<1]<<1;
            update(i);
        }
    }
    
    void prop(int u) {
        if (lz[u]==-1ll) return;
        ll tmp = lz[u];
        lz[u] = -1;
        a[u<<1] = {tmp,tmp,tmp*sz[u<<1]};
        a[u<<1|1] = {tmp,tmp,tmp*sz[u<<1|1]};
        lz[u<<1] = tmp;
        lz[u<<1|1] = tmp;
    }

    void update(int u) {
        auto [lmi,lma,lsu] = a[u<<1];
        auto [rmi,rma,rsu] = a[u<<1|1];
        a[u] = {min(lmi,rmi),max(lma,rma),lsu+rsu};
    }
    
    void set(int u, int l, int r, int lb, int rb, ll x) {
        auto [mi,ma,su] = a[u];
        if (lb>=r || rb<=l) return;
        if (lb>=l && rb<=r) {
            a[u] = {x,x,x*sz[u]};
            lz[u] = x;
            return;
        }
        int m = (lb+rb)>>1;
        prop(u);
        set(u<<1,l,r,lb,m,x);
        set(u<<1|1,l,r,m,rb,x);
        update(u);
    }
    
    void modset(int u, int l, int r, int lb, int rb, ll x) {
        auto [mi,ma,su] = a[u];
        if (lb>=r || rb<=l || ma<x) return;
        if (lb>=l && rb<=r && mi==ma)  {
            ll y = mi%x;
            a[u] = {y,y,y*sz[u]};
            lz[u] = y;
            return;
        }
        int m = (lb+rb)>>1;
        prop(u);
        modset(u<<1,l,r,lb,m,x);
        modset(u<<1|1,l,r,m,rb,x);
        update(u);
    }

    ll query(int u, int l, int r, int lb, int rb) {
        if (lb>=r || rb<=l) return 0ll;
        if (lb>=l && rb<=r) return get<2>(a[u]);
        ll res = 0ll;
        int m = (lb+rb)>>1;
        prop(u);
        res += query(u<<1,l,r,lb,m);
        res += query(u<<1|1,l,r,m,rb);
        return res;
    }
};


void solve(int testcase) {
    ii(k); ii(m);
    int n = k==1? 1 : 1<<(32-__builtin_clz(k-1));
    fill_n(a,n*2,tuple<ll,ll,ll>({0ll,0ll,0ll}));
    fill_n(lz,n*2,-1ll);
    fr(i,0,k) {
        lli(x);
        a[i+n] = {x,x,x};
    }
    auto st = segment_tree(n);
    vll res;
    fr(i,0,m) {
        ii(t);
        if (t==1) {
            ii(l); ii(r); l--;
            res.push_back(st.query(1,l,r,0,n));
        } else if (t==2) {
            ii(l); ii(r); lli(x); l--;
            st.modset(1,l,r,0,n,x);
        } else {
            ii(l); lli(x); l--;
            st.set(1,l,l+1,0,n,x);
        }
    }
    // print("");
    for (auto x : res) print(x);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}