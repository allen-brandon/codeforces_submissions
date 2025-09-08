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
int b[500001]; // next highest element
int rt[500001]; // next highest element
int id[500001]; // next highest element

int find(int u) {
    int v = rt[u];
    while (rt[v]!=v) {
        v = rt[v];
    }
    rt[u] = v;
    return v;
}

int join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u==v) return 0;
    if (id[v]>id[u]) {
        rt[u] = v;
    } else {
        rt[v] = u;
    }
    return 1;
}

void solve(int testcase) {
    ii(n);
    set<int> s;
    fr(i,0,n) {
        ii(x);
        s.insert(x);
    }
    // if (testcase!=1) return;
    n = s.size();
    int lim = (*s.rbegin())+1;
    fr(i,0,lim) b[i] = 0;
    fr(i,0,lim) rt[i] = i;
    fr(i,0,lim) id[i] = rand();
    int i = lim-1;
    int x = lim-1;
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> pq;
    for (auto iter = s.rbegin(); iter!=s.rend(); iter++) {
        int u = *iter;
        while (i>=u) {
            b[i--] = x;
        }
        for (int j = u; j<lim; j+=u) {
            int v = b[j];
            pq.emplace(v-j, u, v);
        }
        x = u;
        b[u] = u;
    }
    ll res = 0;
    int pop = n;
    while (!pq.empty()) {
        auto [d,u,v] = pq.top();
        pq.pop();
        if (join(u,v)==1) {
            res += ll(d);
            pop--;
            if (pop==1) break;
        }
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}