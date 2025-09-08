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

void testcase(int test_num) {
    ii(n); ii(x);
    x--;
    si(s);
    // print(n << " " << x);
    // print(s);
    int l = x, r = x;
    while (l>=0 && s[l]=='.') {
        l--;
    }
    while (r<n && s[r]=='.') {
        r++;
    }
    int l_mod = x+1;
    int r_mod = n-x;
    int l_move = l+2;
    int r_move = n+1-r;
    int res;
    if (x<n-1 && x>0) {
         res = max(min(l_mod,r_move),min(l_move,r_mod));
    } else {
        res = 1;
    }
    // print(l_move << " " << r_move);
    // print(l_mod << " " << r_mod);
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    fr(i,1,t+1) testcase(i);
}