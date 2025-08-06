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
int p[100001];
int s[100001];

void testcase() {
    ii(n);
    bool possible = true;
    fr(i,0,n) {
        ii(x);
        p[i] = x;
        if (i && (p[i-1]%x)!=0) {
            possible = false;
        }
    }
    fr(i,0,n) {
        ii(x);
        s[i] = x;
        if (i && (x%s[i-1])!=0) {
            possible = false;
        }
    }
    if (!possible) {
        print(ny[0]);
        return;
    }
    if (p[0]%s[0]!=0 || s[n-1]%p[n-1]!=0) {
        print(ny[0]);
        return;
    }
    fr(i,1,n) {
        if (gcd(s[i],p[i-1])!=gcd(s[i],p[i])) {
            print(ny[0]);
            return;
        }
    }
    fr(i,0,n-1) {
        if (gcd(p[i],s[i+1])!=gcd(p[i],s[i])) {
            print(ny[0]);
            return;
        }
    }
    print(ny[1]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}