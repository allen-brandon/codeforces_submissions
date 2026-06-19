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
int mod = 1000000007;
const int nlim = 524288;
//{earlist 0, earliest 1, latest 0, latest 1}
int a[nlim];

struct segment_tree {
    private:
    int n;
    public:
    int curmin;
    int ans;
    segment_tree(int n): n(n) {
        for (int i = n-1; i >= 0; i--) {
            a[i] = min(a[i<<1],a[i<<1|1]);
        }
    }

    void update(int i, int x) {
        i += n;
        a[i] = x;
        for (i>>=1; i>0; i>>=1) {
            a[i] = min(a[i<<1],a[i<<1|1]);
        }
    }
    void search(int u, int lb, int rb, int l, int r) {
        if (ans!=mod) return;
        if (lb>=r || rb<=l) return;
        if (lb>=l && rb<=r && min(curmin,a[u]) > rb-l-1) {
            curmin=min(curmin,a[u]);
            return;
        }
        if (u>=n) {
            ans = lb;
            return;
        }
        int m = lb+(rb-lb)/2;
        search(u<<1,lb,m,l,r);
        search(u<<1|1,m,rb,l,r);
    }

    int query(int l, int r) {
        int res = mod;
        for (l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if (l&1) res = min(res, a[l++]);
            if (r&1) res = min(res, a[--r]);
        }
        return res;
    }
};

void solve(int testcase) {
    ii(k); ii(q);
    int n = 1<<(32-__builtin_clz(k-1));
    fill_n(a,n*2,mod);
    fr(i,0,k) {
        ii(x);
        a[i+n] = x;
    }
    segment_tree st(n);
    vi res;
    fr(i,0,q) {
        ii(t);
        if (t==1) {
            ii(idx); ii(x);
            st.update(--idx,x);
        } else {
            ii(l); ii(r);
            st.curmin = st.ans = mod;
            st.search(1,0,n,--l,r);
            int idx = st.ans;
            int cur = idx!=mod && st.query(l,idx+1)==idx-l;
            res.emplace_back(cur);
        }
        // vi test(a+n,a+n+k);
        // printv(test);
    }
    for (int x : res) print(x);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}