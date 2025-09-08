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
int dp[5001][5001][3];
int a[5001][5001];

void solve(int testcase) {
    si(s);
    int n = s.size();
    fr(i,0,n+1) {
        a[i][n] = 0;
        dp[i][n][0] = 1;
        dp[i][n][1] = n;
        dp[i][n][2] = n;
    }
    for (int i=n-1; i>=0; --i) {
        fr(j,i+1,n) {
            a[i][j] = s[i]==s[j] ? a[i+1][j+1]+1 : 0;
        }
    }
    //given i and j, is s[i:j]<=s[j:j+i]
    auto valid = [&](int i, int j) -> bool {
        int k = a[i][j];
        if (k>=j-i) return true;
        if (j+k==n) return false;
        return s[i+k]<=s[j+k];
    };

    for (int i=n-1; i>=0; i--) {
        for (int j=n-1; j>i; j--) {
            dp[i][j][0] = dp[i][j+1][0];
            dp[i][j][1] = dp[i][j+1][1];
            dp[i][j][2] = dp[i][j+1][2];
            if (!valid(i,j)) continue;
            int k = j+min(j+1-i, a[i][j]+1);
            if (dp[j][k][0] >= dp[i][j][0]) {
                dp[i][j][0] = dp[j][k][0]+1;
                dp[i][j][1] = j;
                dp[i][j][2] = k;
            }
        }
    }
    print(dp[0][1][0]);
    int l=dp[0][1][1], r=dp[0][1][2];
    fr(i,0,l) {
        cout << s[i];
    }
    cout << "\n";
    while (l<n) {
        int l1=dp[l][r][1];
        fr(i,l,l1) cout << s[i];
        cout << "\n";
        int r1=dp[l][r][2];
        l=l1;
        r=r1;
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}