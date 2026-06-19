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
const ll nlim = 1048576; //tour * 2, segtree * 2

//segtree element
struct seq {
    int zo{}; //0,1,0,1...
    int oz{}; //1,0,1,0...
    int tw{}; //2,3,2,3...
    int th{}; //3,2,3,2...

    seq() = default;

    seq (int z, int o, int t, int th) : zo(z), oz(o), tw(t), th(th) {};

    seq(int x) : zo(x==0), oz(x==1), tw(x==2), th(x==3) {}
};

//identity sequence (nothing)
seq e;

//combines x and y into a new sequence
seq op(seq l, seq r) {
    int zo = l.zo, oz = l.oz, tw=l.tw, th=l.th;
    zo += zo&1? max(r.oz, r.zo-1) : max(r.zo, r.oz-1);
    oz += oz&1? max(r.zo, r.oz-1) : max(r.oz, r.zo-1);
    tw += tw&1? max(r.th, r.tw-1) : max(r.tw, r.th-1);
    th += th&1? max(r.tw, r.th-1) : max(r.th, r.tw-1);
    return seq(zo,oz,tw,th);
};

//applies mapping to sequence
seq f(int x, seq s) {
    if (x==0) return s;
    return seq(s.tw,s.th,s.zo,s.oz);
};

//composes update f into update g
int c(int f, int g) {
    return f^g;
}

int vals[nlim>>2];
int tour[nlim>>1];
pair<int,int> lr[nlim>>2];
int res[nlim>>2];
vi adj[nlim>>2];
seq a[nlim];
int lz[nlim];

struct segment_tree {
    private:
    int n;
    public:
    segment_tree(int k) {
        n = 1<<(32-__builtin_clz(k-1));
        fill_n(lz,n*2,0);
        fill_n(a+n,n,seq());
        fr(i,0,k) {
            a[i+n] = seq(tour[i]);
        }
        for (int i = n-1; i>0; i--) {
            a[i] = op(a[i<<1], a[i<<1|1]);
        }
    }

    void propagate(int u) {
        if (lz[u]==0) return;
        fr(v,u<<1,(u<<1)+2) {
            a[v] = f(lz[u],a[v]);
            lz[v] = c(lz[u],lz[v]);
        }
        lz[u] = 0;
    }

    void refresh(int u) {
        a[u] = op(a[u<<1],a[u<<1|1]);
    }

    //swap sequences in this subtree tour[l...r]
    int update(int l, int r) {
        l+=n; r+=n;
        int r_inc = r-1;
        // flip is commutative
        // for (int j = 31-__builtin_clz(r_inc); j>0; j--) {
        //     propagate(l>>j);
        //     propagate(r_inc>>j);
        // }
        
        //update subtrees
        for (int lb=l, rb=r; lb<rb; lb>>=1, rb>>=1) {
            if (lb&1) {
                a[lb] = f(1, a[lb]);
                lz[lb] = c(1, lz[lb]);
                lb++;
            }
            if (rb&1) {
                rb--;
                a[rb] = f(1, a[rb]);
                lz[rb] = c(1, lz[rb]);
            }
        }
        
        //prop to refresh
        for (int j = 31-__builtin_clz(r_inc); j>0; j--) {
            propagate(l>>j);
            propagate(r_inc>>j);
        }

        //refresh anc
        for (int lb=l>>1, rb=r_inc>>1; rb>0; lb>>=1, rb>>=1) {
            refresh(lb);
            refresh(rb);
        }
        return a[1].tw; //return longest subsequence of leaf 1's
    }
};

void solve(int testcase) {
    ii(n);
    fill_n(adj,n,vi());
    fr(i,0,n) {
        ii(x);
        vals[i] = x;
    }
    fr(i,0,n-1) {
        ii(u); ii(v);
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    //build tour/st
    stack<tuple<int,int,int>> stk;
    stk.emplace(0,0,1);
    int tour_idx{};
    while (!stk.empty()) {
        auto [u,p,d] = stk.top();
        stk.pop();
        if (d==0) {
            tour[tour_idx] = 1^(vals[u]<<1);
            lr[u] = {lr[u].first, tour_idx+1}; //r exclusive
            tour_idx++;
            continue;
        }
        stk.emplace(u,p,0);
        tour[tour_idx] = vals[u]<<1;
        lr[u] = {tour_idx, tour_idx};
        tour_idx++;
        for (int v : adj[u]) {
            if (v==p) continue;
            stk.emplace(v,u,1);
        }
    }
    segment_tree st(tour_idx);

    // int logn = 31-__builtin_clz(n);
    // logn+=logn&1;
    //process queries
    ii(q);
    res[0] = a[1].tw;
    fr(i,1,q+1) {
        ii(v);
        v--;
        auto [l,r] = lr[v];
        //make it O(nlogn + qlog^2n)
        // fr(log_factor,0,logn) st.update(l,r);
        res[i] = st.update(l,r);
    }
    fr(i,0,q+1) print(res[i]/2);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}