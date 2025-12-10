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
ll mod = 1000000007;
ll inf = mod<<1;
int a[100001];
//idx, prev, first. 0: backwards, 1: forwards
int dp[100001][2][2];

void solve(int testcase) {
    ii(m); ii(n);
    fr(i,0,n) {
        ii(x);
        a[i] = x;
        dp[i][0][0] = -1;
        dp[i][0][1] = -1;
        dp[i][1][0] = -1;
        dp[i][1][1] = -1;
    }
    a[n] = m+a[0];
    auto dfs = [m,n](int i, int j, int k, auto& dfs) {
        if (dp[i][j][k]!=-1) return dp[i][j][k];
        int r = inf;
        int l = a[i]-1-a[i-1];
        if (j==1) {
            l -= l>>1;
            r = 
        }
        int r = a[i+1]-1-a[i];
        if (i==n-1 && k==1) {
            r -= r>>1;
        }
        print(m);
        int res = 0;
        dp[i][j][k] = res;
        return res;
    };
    int res = dfs(0,0,0,dfs)-1;
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}