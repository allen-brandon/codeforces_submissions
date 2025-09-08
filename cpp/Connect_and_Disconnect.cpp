#ifdef LOCAL
#include "_pch.hpp"
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define USE_INPUT_FILE(file) do { \
    freopen("connect.in", "r", stdin); \
    freopen("connect.out", "w", stdout); \
} while (0)
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
int p[300001];
int id[300001];
int res[300001];
stack<pair<int,int>> history; //old child, old parent
vector<pair<int,int>> a[1048576]; //connect u,v

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
        l+=n;
        r+=n;
        while (l<r) {
            if (l&1) {
                a[l].push_back(x);
                l++;
            }
            if (r&1) {
                r--;
                a[r].push_back(x);
            }
            l>>=1;
            r>>=1;
        }
    }

    void printout() {
        print(n);
        fr(i,0,n<<1) {
            printm(a[i]);
        }
    }
};

int find(int u) {
    int v = p[u];
    while (v!=p[v]) v = p[v];
    return v;
}

int join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u==v) {
        history.emplace(-1,-1);
        return 0;
    }
    if (id[u]>id[v]) swap(u,v);
    history.emplace(u,p[u]);
    p[u] = v;
    return 1;
}

int undo() {
    auto [u,v] = history.top();
    history.pop();
    if (u==-1) return 0;
    p[u] = v;
    return 1;
}

void solve(int testcase) {
    ii(n); ii(q);
    int m = 1;
    while (m<q) m<<=1;
    history = stack<pair<int,int>>();
    fr(i,0,n) {
        p[i] = i;
        id[i] = rand();
    }
    map<pair<int,int>,vector<pair<int,int>>> edges;
    vi res_q;
    fr(i,0,q) {
        si(c);
        if (c=="?") {
            res_q.push_back(i);
        } else if (c=="+") {
            ii(u); ii(v);
            u--; v--;
            if (u<v) swap(u,v);
            edges[make_pair(u,v)].emplace_back(i,q);
        } else {
            ii(u); ii(v);
            u--; v--;
            if (u<v) swap(u,v);
            vector<pair<int,int>>& b = edges[make_pair(u,v)];
            int l = b.back().first;
            b.pop_back();
            b.emplace_back(l,i);
        }
    }
    SegmentTree seg_tree(q);
    for (auto& [x, b] : edges) {
        for (auto& [l,r] : b) {
            seg_tree.update(l,r,x);
        }
    }
    // vi test;
    // fr(i,0,m<<1) test.push_back(a[i].size());
    // printv(test);
    // printv(res_q);
    int res_idx = 0;
    int pop = n;
    stack<pair<int,int>> st;
    st.emplace(1,1);
    while (!st.empty() && res_idx<res_q.size()) {
        auto [i,d] = st.top();
        // print(i << " " << d << ": " << pop);
        st.pop();
        if (d==0) {
            fr(j,0,a[i].size()) {
                pop += undo();
            }
            continue;
        }
        st.emplace(i,0);
        for (auto [u,v] : a[i]) {
            pop -= join(u,v);
        }
        if (i<m) {
            st.emplace(i<<1|1,1);
            st.emplace(i<<1,1);
        } else if (i==res_q[res_idx]+m) {
            res[res_idx++] = pop;
        }
    }
    fr(i,0,res_q.size()) print(res[i]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}