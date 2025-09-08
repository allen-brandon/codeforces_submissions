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
vi adj[200001];
ll d_o[200001];
ll d_e[200001];

void solve(int testcase) {
    ii(n); ii(m); ii(l);
    fill_n(adj,n,vi());
    ll total = 0, msf = inf;
    int odd = 0;
    fr(i,0,l) {
        lli(x);
        total+=x;
        if (x&1) {
            odd+=1;
            msf = min(msf, x);
        }
    }
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    fill_n(d_o,n,inf);
    fill_n(d_e,n,inf);
    d_e[0] = 0;
    vector<pair<int,ll>> cur = {make_pair(0,0)};
    while (!cur.empty()) {
        vector<pair<int,ll>> tmp;
        for (auto [u,d] : cur) {
            for (int v : adj[u]) {
                if (d&1) {
                    if (d_e[v]!=inf) continue;
                    d_e[v] = d+1;
                    tmp.emplace_back(v,d_e[v]);
                } else {
                    if (d_o[v]!=inf) continue;
                    d_o[v] = d+1;
                    tmp.emplace_back(v,d_o[v]);
                }
            }
        }
        cur.swap(tmp);
    }
    vi res;
    res.reserve(n);
    // vll test(d_e,d_e+n);
    // printv(test);
    // vll test1(d_o,d_o+n);
    // printv(test1);
    fr(i,0,n) {
        ll d = d_e[i];
        if (d!=inf) {
            if (odd&1) d+=msf;
            if (d<=total) {
                res.push_back(1);
                continue;
            }
        }
        d = d_o[i];
        if (d==inf) {
            res.push_back(0);
            continue;
        }
        if ((odd&1)==0) {
            if (odd==0) {
                res.push_back(0);
                continue;
            } else {
                d+=msf;
            }
        }
        res.push_back(int(d<=total));

    }
    for (int x : res) {
        cout << x;
    }
    cout << "\n";
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}