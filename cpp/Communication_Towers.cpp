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
ll mod = 1000000007;
int bounds[200001][2];
int p[200001];
int id[200001];
stack<tuple<int,int,int>> history;
vector<pair<int,int>> a[524288];
int b[200001];
int t;

struct SegmentTree {
    private:
    int n;
    int m;
    public:
    SegmentTree(int m) {
        this -> m = m;
        n = 1;
        while (n<m) n<<=1;
        fr(i,0,n<<1) {
            a[i].clear();
        }
    }
    void update(int l, int r, pair<int,int> x) {
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) a[l++].push_back(x);
            if (r&1) a[--r].push_back(x);
        }
    }
};

int find(int u) {
    int v = p[u];
    while (p[v]!=v) v = p[v];
    return v;
}

void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (id[u]>id[v]) swap(u,v);
    history.emplace(u,p[u],t++);
    if (u==v) return;
    p[u] = v;
}

void undo() {
    auto [u,v,t] = history.top();
    history.pop();
    if (b[p[u]]>=t) b[u] = max(b[u],b[p[u]]);
    p[u] = v;
}

void solve(int testcase) {
    ii(n); ii(m);
    int msf = 0;
    t = 0;
    fr(i,0,n) {
        ii(l); ii(r);
        bounds[i][0] = l;
        bounds[i][1] = r+1;
        b[i] = -1;
        p[i] = i;
        id[i] = rand();
        msf = max(msf,r);
    }
    msf++;
    SegmentTree seg_tree(msf);
    int n1 = 1;
    while (n1<msf) n1<<=1;
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        if (v<u) swap(u,v);
        int l=max(bounds[u][0],bounds[v][0]), r=min(bounds[u][1],bounds[v][1]);
        if (l<r) seg_tree.update(l,r,make_pair(u,v));
    }
    history = stack<tuple<int,int,int>>();
    stack<pair<int,int>> st;
    st.emplace(1,1);
    while (!st.empty()) {
        auto [i,d] = st.top();
        st.pop();
        if (d==0) {
            fr(j,0,a[i].size()) undo();
            continue;
        }
        for (auto [u,v] : a[i]) join(u,v);
        st.emplace(i,0);
        if (i<n1) {
            st.emplace(i<<1|1,1);
            st.emplace(i<<1,1);
        } else {
            b[find(0)] = t++;
        }
    }
    vi res;
    fr(i,0,n) {
        if (b[i]>-1) res.push_back(i+1);
    }
    printv(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}