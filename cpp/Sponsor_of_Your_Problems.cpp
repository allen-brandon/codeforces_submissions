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
int cache[20][2][2];

void solve(int testcase) {
    si(l); si(r);
    // if (testcase!=6) return;
    int n = l.size();
    fr(i,0,n) {
        fr(j,0,2) {
            fr(k,0,2) {
                cache[i][j][k] = -1;
            }
        }
    }
    auto dfs = [&](auto& dfs, int i, int eq1, int eq2) -> int {
        if (i==n) return 0;
        if (cache[i][eq1][eq2]!=-1) return cache[i][eq1][eq2];
        int lb = eq1 ? l[i]-'0' : (i==0? 1 : 0);
        int rb = (eq2 ? r[i]-'0' : 9) + 1;
        int res = 20;
        fr(x,lb,rb) {
            int score = (x==l[i]-'0') + (x==r[i]-'0');
            score += dfs(dfs, i+1, eq1&(x==l[i]-'0'), eq2&(x==r[i]-'0'));
            res = min(res, score);
        }
        cache[i][eq1][eq2] = res;
        return res;
    };
    int res = dfs(dfs, 0, 1, 1);
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}