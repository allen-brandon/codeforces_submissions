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

ll a[200001];
//from idx on, starting at i
ll dp[200001][3];

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        lli(x);
        a[i] = x;
    }
    // if (testcase!=2) return;

    //set next block to same
    auto f = [&](int l, int r) -> ll {
        vll res;
        for (int i = l; i != r; i = (i+1)%n) {
            res.push_back(a[i]);
        }
        res.push_back(a[r]);
        sort(res.begin(),res.end());
        ll x = 0;
        for (const auto& y : res) {
            x += abs(res[res.size()/2]-y);
        }
        return x;
    };
    dp[n-1][0] = inf;
    dp[n-1][1] = f(n-1,0);
    dp[n-1][2] = f(n-1,1);
    dp[n-2][0] = f(n-2,n-1);
    dp[n-2][1] = f(n-2,0);
    dp[n-2][2] = inf;
    dp[n-3][0] = f(n-3,n-1);
    dp[n-3][1] = f(n-3,n-2) + dp[n-1][1];
    dp[n-3][2] = f(n-3,n-2) + dp[n-1][2];
    for (int i = n-4; i>=0; i--) {
        fr(j,0,3) {
            if (i<j) {
                dp[i][j] = dp[i+1][j];
                continue;
            }
            dp[i][j] = min(dp[i+2][j]+f(i,i+1), dp[i+3][j]+f(i,i+2));
        }
    }
    ll res = min(dp[0][0],dp[0][1]);
    res = min(res, dp[0][2]);
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}