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
int a[200001];
int c1[200001]; //count of vals inside [l,r]
int c2[200001]; //count of vals outside [l,r]

void solve(int testcase) {
    lli(n); lli(k);
    int m = 0; //max val in a
    ll res = 0;
    fr(i,0,n) {
        ii(x);
        a[i] = x;
        m = max(m,x);
    }
    m++;
    fill_n(c1,m,0);
    fill_n(c2,m,0);
    fr(i,0,n) {
        c2[a[i]]++;
    }
    // if (testcase!=1) return;
    fr(x,0,m) {
        if (c2[x]%k!=0) {
            print(0);
            return;
        }
    }
    k--; //k is now the multiple of each c1[i] that needs to be in c2
    int l = 0;
    fr(r,0,n) {
        int x = a[r];
        c2[x]--; c1[x]++;
        while (c1[x]*k>c2[x] && l<=r) {
            int y = a[l];
            c2[y]++; c1[y]--;
            l++;
        }
        res += ll(r)+1ll-ll(l);
    }
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