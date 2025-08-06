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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_by_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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
array<array<int,5001>,5001> dp;
array<array<int,5001>,5001> gcda;
array<int,5001> a;

void solve(int n) {
    int g = a[0];
    for (int i=0; i<n; ++i) {
        g = gcda[g][a[i]];
    }
    int not_g = 0;
    for (int i=0; i<n; ++i) {
        not_g+=(a[i]!=g);
    }
    if (not_g != n) {
        print(not_g);
        return;
    }
    vector<pair<int,int>> touched;
    auto dfs = [](auto& dfs, int i, int x, int g, auto& t, int n) {
        if (x==g) return 0;
        if (i==n) return 998244353;
        if (dp[i][x] == -1) {
            t.emplace_back(i,x);
            int not_inc = dfs(dfs,i+1,x,g,t,n);
            int inc = x==0? dfs(dfs,i+1,a[i],g,t,n): dfs(dfs,i+1,gcda[x][a[i]],g,t,n)+1;
            dp[i][x] = min(inc,not_inc);
        }
        return dp[i][x];
    };
    int to_obtain = dfs(dfs, 0, 0, g, touched, n);
    for (auto [i,x] : touched) {
        dp[i][x] = -1;
    }
    print(to_obtain+not_g-1);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    fill_n(dp[0].begin(), 5001, -1);
    for (int i=1; i<=5000; ++i) {
        fill_n(dp[i].begin(), 5001, -1);
        for (int j=1; j<=5000; ++j) {
            gcda[i][j] = gcd(i,j);
            gcda[j][i] = gcd(i,j);
        }
    }
    ii(testcases);
    for (int t=0; t<testcases; ++t) {
        ii(n);
        for (int i=0; i<n; ++i) {
            ii(x);
            a[i] = x;
        }
        solve(n);
    }
}