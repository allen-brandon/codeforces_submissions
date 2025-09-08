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

void solve(int testcase) {
    ii(n);
    ll msf1 = -inf;
    ll msf2 = -inf;
    fr(i,0,n) {
        lli(x); lli(y);
        msf1 = max(msf1,x+y);
        msf2 = max(msf2,x-y);
    }
    ll d1,d2;
    fr(i,0,3) {
        cout << "? " << "R " << 1000000000 << "\n";
        cout.flush();
        lli(z);
    }
    fr(i,0,2) {
        cout << "? " << "D " << 1000000000 << "\n";
        cout.flush();
        lli(z);
        d2 = z;
    }
    fr(i,0,5) {
        cout << "? " << "U " << 1000000000 << "\n";
        cout.flush();
        lli(z);
        d1 = z;
    }
    ll x_plus_y = msf1 + d1 - 6000000000;
    ll x_minus_y = msf2 + d2 - 5000000000;
    ll x = (x_plus_y + x_minus_y)>>1;
    ll y = x_plus_y - x;
    cout << "! " << x << " " << y << "\n";
    cout.flush();
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}