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
ll a[200001];
ll min_pref[200001];
ll sum_pref[200001];

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        lli(x);
        a[i] = x;
    }
    partial_sum(a,a+n,min_pref,[](ll x, ll y) {return min(x,y);});
    partial_sum(min_pref,min_pref+n,sum_pref);
    // vll test(a,a+n);
    // printv(test);
    // vll test1(min_pref,min_pref+n);
    // printv(test1);
    ll res = sum_pref[n-1];
    //a[i-1] - a[i]
    pair<ll,int> msf = make_pair(inf,0);
    fr(j,1,n) {
        ll cur = sum_pref[j-1];
        cur += min(msf.first, a[j]);
        msf = min(msf, make_pair(max(0ll,a[j-1]-a[j]),j));
        res = min(res,cur);
        // if (msf.first<=0) break;
        // print(j << " " << cur << " " << msf.first);
    }   
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}