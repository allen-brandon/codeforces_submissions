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
int a[101][101];
ll cache[101][101][101];

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        fr(j,0,n-i) {
            ii(x);
            a[i][i+j] = x;
        }
        fr(j,0,n) {
            fill_n(cache[i][j],n,-1);
        }
    }
    auto dp = [](auto& dp, int i, int z, int o, int n) -> ll {
        if (i==n) return 1;
        if (cache[i][z][o]!=-1) return cache[i][z][o];
        //try placing a 0 or 1
        ll res = 0;
        bool valid = true;
        fr(j,0,i+1) {
            if (a[j][i]==0) continue;
            int placed = (z>j) + (o>j);
            if (a[j][i]==1) {
                if (placed==2) { //you need to have placed 1 here but you've placed 2
                    cache[i][z][o] = 0;
                    return 0;
                } else if (placed==1 && o>j) { //need to place another o
                    valid = false;
                }
            } else {
                if (placed==1 && z>j) { //need to place an initial o
                    valid = false;
                } else if (placed==0) { //you need to have placed 2 here but you've placed 0
                    cache[i][z][o] = 0;
                    return 0;
                }
            }
        }
        if (valid) res = (res + dp(dp,i+1,i+1,o,n)) % mod;
        valid = true;
        fr(j,0,i+1) {
            if (a[j][i]==0) continue;
            int placed = (z>j) + (o>j);
            if (a[j][i]==1) {
                if (placed==2) { //you need to have placed 1 here but you've placed 2
                    cache[i][z][o] = 0;
                    return 0;
                } else if (placed==1 && z>j) { //need to place another z
                    valid = false;
                }
            } else {
                if (placed==1 && o>j) { //need to place an initial z
                    valid = false;
                } else if (placed==0) { //you need to have placed 2 here but you've placed 0
                    cache[i][z][o] = 0;
                    return 0;
                }
            }
        }
        if (valid) res = (res + dp(dp,i+1,z,i+1,n)) % mod;
        cache[i][z][o] = res;
        return res;
    };
    ll res = dp(dp,0,0,0,n);
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}