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
vi adj[200001];
int par[200001];
int dp[200001][3];

void solve(int testcase) {
    ii(n);
    fill_n(adj,n,vi());
    fr(i,0,n-1) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // if (testcase!=1) return;
    stack<tuple<int,int,int>> st;
    st.emplace(0,0,1);
    while (!st.empty()) {
        auto [u,p,d] = st.top();
        st.pop();
        if (d==0) {
            //leaf node
            if (adj[u].size()==1 && u!=0) {
                dp[u][0] = 0;
                dp[u][1] = 1;
                dp[u][2] = 0;
                // print(u);
                // printv(dp[u]);
                continue;
            }
            dp[u][0] = 1;
            dp[u][1] = 0;
            dp[u][2] = 0;
            for (int v : adj[u]) {
                if (v==p) continue;
                vi tmp = {0,0,0};
                //try using i operations on v
                fr(i,0,3) {
                    if (dp[u][i]==0) continue;
                    fr(j,0,3) {
                        if (dp[v][j]==0) continue;
                        tmp[(i+j)%3] = 1;
                    }
                }
                fr(i,0,3) dp[u][i] = tmp[i];
            }
            
            //try setting this subtree
            dp[u][1] = 1;
            continue;
        }
        st.emplace(u,p,0);
        for (int v : adj[u]) {
            if (v==p) continue;
            st.emplace(v,u,1);
        }
    }
    // printv(dp[0]);
    print(ny[dp[0][0]]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}