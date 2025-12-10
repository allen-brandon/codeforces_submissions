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
int mod = 1000000007;


int rt[400001]; //root for vertex i
int id[400001]; //link id for group i
tuple<int,int,int> updates[400001]; //at time t, (r,c) = x
bitset<400001> mn; //is group i a local minimum

int find(int u) {
    while (rt[rt[u]] != rt[u]) {
        rt[u] = rt[rt[u]];
    }
    return rt[u];
}

//returns 1 if groups are local mins, 0 if not
bool join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u==v) return 0;
    if (id[v]>id[u]) swap(u,v);
    rt[u] = v;
    mn[v] = mn[v] & mn[u];
    return 1;
}

void solve(int testcase) {
    ii(n); ii(m);
    auto enc = [m](int i, int j) {return i*m+j; };
    auto dec = [m](int idx) {return pair<int,int>({idx/m, idx%m}); };
    
    vector<vi> a(n+2); //cur val at [i,j]
    vector<vi> touched(n+2); //last vertex that was at [i,j] (idx = i*m+j)
    fr(i,0,n+2) {
        a[i] = vi(m+2,mod);
        touched[i] = vi(m+2,0);
    }
    mn[0] = 0;
    rt[0] = 0;
    int t = 1;
    fr(i,1,n+1) {
        fr(j,1,m+1) {
            ii(x);
            updates[t++] = {i,j,mod-x};
        }
    }
    ii(q);
    int lim = n*m+q;
    while (t<=lim) {
        ii(i); ii(j); ii(x);
        updates[t++] = {i,j,x};
    }
    // if (testcase!=3) return;
    vi res;
    res.reserve(q+1);
    int cur = 0;
    fr(idx,1,n*m+1) {
        auto [i,j,dx] = updates[idx];
        a[i][j] -= dx;
        rt[idx] = idx;
        mn[idx] = 1;
        for (auto [di,dj] : didj) {
            int i1=i+di, j1=j+dj;
            int idx1 = find(touched[i1][j1]);
            if (a[i1][j1]<a[i][j] || (a[i1][j1]==a[i][j] && mn[idx1] == 0)) mn[idx] = 0;
            if (a[i1][j1]>a[i][j]) {
                cur -= mn[idx1];
                mn[idx1] = 0;
            }
        }
        for (auto [di,dj] : didj) {
            int i1=i+di, j1=j+dj;
            int idx1 = find(touched[i1][j1]);
            if (a[i1][j1] == a[i][j]) {
                int tmp = mn[idx1];
                if (join(idx,idx1)) cur -= tmp;
            }
        }
        int old_idx = touched[i][j];
        cur -= mn[find(old_idx)];
        cur += mn[find(idx)];
        touched[i][j] = idx;
    }
    res.push_back(cur); //initial state
    //each query
    fr(idx,n*m+1,lim+1) {
        auto [i,j,dx] = updates[idx];
        a[i][j] -= dx;
        rt[idx] = idx;
        mn[idx] = 1;
        for (auto [di,dj] : didj) {
            int i1=i+di, j1=j+dj;
            int idx1 = find(touched[i1][j1]);
            if (a[i1][j1]<a[i][j] || (a[i1][j1]==a[i][j] && mn[idx1] == 0)) mn[idx] = 0;
            if (a[i1][j1]>a[i][j]) {
                cur -= mn[idx1];
                mn[idx1] = 0;
            }
        }
        for (auto [di,dj] : didj) {
            int i1=i+di, j1=j+dj;
            int idx1 = find(touched[i1][j1]);
            if (a[i1][j1] == a[i][j]) {
                int tmp = mn[idx1];
                if (join(idx,idx1)) cur -= tmp;
            }
        }
        int old_idx = touched[i][j];
        cur -= mn[find(old_idx)];
        cur += mn[find(idx)];
        touched[i][j] = idx;
        res.push_back(cur);
    }
    for (int x : res) print(x);
    // print("");
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    mt19937 rng(1);
    fr(i,0,400001) id[i] = rng();
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}