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
int rt[1000001];
int sz[1000001];
int a[1001][1001];

int find(int u) {
    int v = rt[u];
    while (rt[rt[v]]!=rt[v]) rt[v] = rt[rt[v]];
    rt[u] = v;
    return v;
}

void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u==v) return;
    if (sz[u]>sz[v]) swap(u,v);
    rt[u] = v;
    sz[v] += sz[u];
}

void solve(int testcase) {
    ii(n); ii(q);
    int m = n*n;
    auto enc = [n](int i, int j) {
        if (i<0 || i==n) return n*n;
        if (j<0 || j==n) return n*n;
        return i*n + j;
    };
    iota(rt,rt+m+1,0);
    fill_n(sz,m+1,1);
    fr(i,0,n) fill_n(a[i],n,-1);
    stack<pair<int,int>> ops;
    fr(idx,0,q) {
        ii(i); ii(j); si(c);
        i--; j--;
        int par = c=="U" || c=="D";
        a[i][j] = par;
        auto [di,dj] = didj[par];
        ops.emplace(enc(i,j),enc(i+di,j+dj));
        tie(di,dj) = didj[2^par];
        ops.emplace(enc(i,j),enc(i+di,j+dj));
    }
    fr(i,0,n) {
        fr(j,0,n) {
            int u = enc(i,j);
            if (a[i][j]==-1) {
                for (auto [di,dj] : didj) {
                    int v = enc(i+di,j+dj);
                    join(u,v);
                }
            } else {
                int par = a[i][j];
                auto [di,dj] = didj[1^par];
                join(u, enc(i+di,j+dj));
                tie(di,dj) = didj[3^par];
                join(u, enc(i+di,j+dj));
            }
        }
    }
    print(find(m));
    vi res;
    while (!ops.empty()) {
        int x = sz[find(m)];
        // print(x);
        res.push_back(n*n+1-x);
        auto [u,v] = ops.top();
        ops.pop();
        join(u,v);
        tie(u,v) = ops.top();
        ops.pop();
        join(u,v);
    }
    reverse(res.begin(),res.end());
    // fr(i,0,q) {
    //     print(res[i]);
    // }
    print("test");
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