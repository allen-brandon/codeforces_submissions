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
const int nlim = 524288;
set<ll> pwrs = {42,1764,74088,3111696,130691232,5489031744,230539333248,9682651996416,406671383849472};
ll a[nlim]; //offset in each segment
map<ll,int> b[nlim]; //{distinct element : count} in each segment (prior to offset)
pair<ll,ll> lz[nlim]; //pending {set, add}
int sz[nlim]; //size of each segment

struct segment_tree {
    private:
    int n;
    public:
    segment_tree(int n) : n(n) {
        return;
    }

    //compose lazy update f into vertex u
    void comp(pair<ll,ll> f, int u) {
        auto [x,dx] = f;
        ll os = a[u];
        auto& c = b[u];
        auto [y,dy] = lz[u];
        if (x!=-1ll) {
            //reset this segment to just be x
            a[u] = 0;
            b[u] = {pair<int,int>(x,sz[u])};
            lz[u] = {x,-1ll};
        }
        if (dx!=-1ll) {
            a[u] += dx;
            if (y!=-1ll) {
                lz[u] = {y+dx,-1ll};
            } else if (dy!=-1ll) {
                lz[u] = {-1ll,dy+dx};
            } else {
                lz[u] = {-1ll, dx};
            }
        }
    }

    void prop(int u) {
        auto [x,dx] = lz[u];
        fr(v,u<<1,u<<1+2) {
            comp(lz[u], v);
        }
        lz[u] = {-1ll,-1ll};
    }

    // void update(int u) {
    //     auto los = a[u<<1];
    //     auto ros = a[u<<1|1];
    //     a[u] = los+ros;
    // }

    //set a[l:r] to x
    void set1(int u, int lb, int rb, int l, int r, ll x) {
        if (lb>=r || rb<=l) return;
        if (lb>=l && rb<=r) {
            comp({x,-1ll},u);
            return;
        }
        int m = (l+r)>>1;
        prop(u);
        set1(u<<1,lb,m,l,r,x);
        set1(u<<1|1,m,rb,l,r,x);
        // update(u);
    }
    
    //add dx to a[l:r] until none are powers of 42
    void set2(int u, int lb, int rb, int l, int r, ll dx) {
        auto [mi,ma] = a[u];
        if (lb>=r || rb<=l) return;
        //add if only happens once
        if (lb>=l && rb<=r && pwrs.lower_bound(mi+dx)==pwrs.lower_bound(ma+dx) && !pwrs.contains(mi+dx)) {
            comp({-1ll,dx},u);
            return;
        }
        //add if all one segment
        if (lb>=l && rb<=r && mi==ma) {
            if (pwrs.contains(mi+dx)) dx<<=1;
            comp({-1ll,dx},u);
            return;
        }
        int m = (l+r)>>1;
        prop(u);
        set1(u<<1,lb,m,l,r,dx);
        set1(u<<1|1,m,rb,l,r,dx);
        // update(u);
    }

    ll query(int u) {
        u+=n;
        for (int j = 31-__builtin_clz(u); j>=0; j--) {
            prop(u>>j);
        }
        return a[u]+(*b[u].begin()).first;
    }
};


void solve(int testcase) {
    
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}