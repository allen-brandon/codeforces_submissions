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
int a[100001];
vll d[100001]; //indices of pivots with diff of i

void solve(int testcase) {
    lli(n);
    fr(i,0,n) {
        ii(x);
        a[i] = x;
    }
    // if (testcase!=2) return;
    fill_n(d,n+1,vll());
    for (ll i = 0; i < n-1; i++) {
        int diff = abs(a[i+1]-a[i]);
        d[diff].push_back(i+1);
    }
    ordered_set os;
    os.insert(0);
    os.insert(n);
    ll cur = ll(n)*ll(n-1)/2;
    vll res;
    fr(x,1,n) {
        res.push_back(cur);
        //add pivots
        for (auto i : d[x]) {
            // print(i << " " << x);
            auto idx = os.order_of_key(i);
            ll l = *os.find_by_order(idx-1);
            ll r = *os.find_by_order(idx);
            // printv(os);
            // print(l << " " << r);
            ll m = i;
            cur -= ((r-l)*(r-1-l))/2;
            cur += ((m-l)*(m-1-l))/2;
            cur += ((r-m)*(r-1-m))/2;
            os.insert(m);
            // break;
        }
        // break;
    }
    // print("test");
    printv(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}