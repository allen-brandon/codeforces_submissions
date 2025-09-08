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
ll mod = 1000000007;
vi adj[200001];
int outd[200001];
int dp[200001][2];

void solve(int testcase) {
    ii(n); ii(m); ii(q);
    fill(adj,adj+n, vi());
    fill(outd,outd+n, 0);
    fr(i,0,n) {
        dp[i][0] = 1;
        dp[i][1] = 1;
    }
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        adj[v].push_back(u);
        outd[u]++;
    }
    auto red = [](int u, int j, auto self) -> void {
        if (dp[u][j] == 0) return;
        dp[u][j] = 0;
        for (auto v : adj[u]) {
            if (j==0) {
                self(v, 1, self);
            } else {
                outd[v]--;
                if (outd[v]==0) {
                    self(v, 0, self);
                }
            }
        }
    };
    vi res;
    fr(query,0,q) {
        ii(x); ii(u); u--;
        if (x==2) {
            // if (testcase==2) print("querying " << u+1 << ": " << dp[u][0]);
            res.push_back(dp[u][0]);
        } else {
            // if (testcase==2) print("setting " << u+1 << " to red");
            red(u, 0, red);
            red(u, 1, red);
        }
    }
    // if (testcase!=2) return;
    for (auto x : res) {
        print(ny[x]);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}