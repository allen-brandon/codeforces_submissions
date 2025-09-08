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
ll fact[200001];
ll ind[200001];
ll ind1[200001];
int col[200001];
array<vi,200001> adj;

void testcase(int t) {
    ii(n); ii(m);
    fill_n(adj.begin(),n,vi());
    fill_n(ind,n,0);
    fill_n(ind1,n,0);
    fill_n(col,n,0);
    if (fact[n] == 0) {
        fact[0] = 1;
        fr(i,1,n+1) {
            fact[i] = (fact[i-1]*i)%mod;
        }
    }
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        ind[u]++;
        ind[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (n==2) {
        print(2);
        return;
    }
    queue<int> q;
    q.push(0);
    col[0] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (col[v]!=0) {
                if (col[v]==col[u]) {
                    print(0);
                    return;
                }
            } else {
                col[v] = col[u]^3;
                q.push(v);
            }
        }
    }
    ll res = 2;
    int special = 0;
    int ends = 0;
    fr(u,0,n) {
        if (ind[u]>1) {
            special++;
            for (auto v : adj[u]) {
                if (ind[v]>1) {
                    ind1[u]++;
                    if (ind1[u]>2) {
                        print(0);
                        return;
                    }
                }
            }
            if (ind1[u]==1) {
                ends = 1;
            }
            ll x = ind[u]-ind1[u];
            res*=fact[x];
            res%=mod;
        }
    }
    if (special>1) {
        if (ends==0) {
            print(0);
            return;
        }
        res<<=1;
        res%=mod;
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(t,1,testcases+1) testcase(t);
}