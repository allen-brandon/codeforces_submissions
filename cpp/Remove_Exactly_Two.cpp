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
ll mod = 998244353;
int ind[200001];
vi adj[200001];
int c[200001];

void testcase() {
    ii(n);
    fill_n(ind, n+1, 0);
    fr(i,1,n+1) adj[i].clear();
    fill_n(c, n+1, 0);
    fr(i,0,n-1) {
        ii(u); ii(v);
        ind[u]++;
        ind[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    fr(i,1,n+1) {
        c[ind[i]]++;
    }
    set<int> s(ind+1, ind+n+1);
    int res = 0;
    fr(u,1,n+1) {
        int msf = 0;
        c[ind[u]]--;
        if (c[ind[u]]==0) s.erase(ind[u]);
        for (int v : adj[u]) {
            c[ind[v]]--;
            if (c[ind[v]]==0) s.erase(ind[v]);
            msf = max(msf, ind[v]);
        }
        res = max(res, ind[u]+msf-2);
        if (!s.empty()) res = max(res, ind[u]-1+*s.rbegin());
        c[ind[u]]++;
        if (c[ind[u]]==1) s.insert(ind[u]);
        for (int v : adj[u]) {
            c[ind[v]]++;
            if (c[ind[v]]==1) s.insert(ind[v]);
        }
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}