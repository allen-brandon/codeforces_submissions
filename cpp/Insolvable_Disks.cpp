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
int mod = 1000000007;
int a[2000001];
int d[2000001]; //distance from a[i] to a[i+1]

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        ii(x);
        a[i] = x;
        if (i>0) {
            d[i-1] = x-a[i-1];
        }
    }
    d[n-1] = mod;
    // if (testcase!=2) return;
    int gaps = 0; //number of gaps
    int p = 0; //prefix difference
    int l = 0, r = d[0], new_p;
    int par = 1; //parity of segment length
    fr(i,0,n) {
        par^=1;
        //greedily add to prefix
        if (par&1) {
            new_p = p-d[i];
            l = max(l, new_p);
        } else {
            new_p = p+d[i];
            r = min(r, new_p);
        }
        if (l<r) {
            p = new_p;
        } else {
            par = 1;
            p = 0;
            l = 0;
            r = d[i];
            gaps++;
        }
    }
    print(n-1-gaps);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}