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
pair<int,int> a[500005];
ll state[500005]; //# of valid subarrs extending to here

void solve(int testcase) {
    ii(n);
    fill_n(state,n+1,0ll);
    fr(i,0,n) {
        ii(x);
        a[i] = {x,x};
    }
    fr(i,0,n) {
        ii(x);
        a[i] = {a[i].first,x};
    }
    // if (testcase!=1) return;
    //total subarrs so far, total subarrs up to r bound
    ll res = 0, cur = 0;
    //[1,1,2,3]
    //[2,1,2,3]
    fr(i,0,n) {
        //could start an empty subarr here
        cur++;
        state[0]++;
        auto [x,y] = a[i];
        if (x==y) {
            state[x] += state[x-1];
            state[x-1] = 0ll;
        } else {
            cur -= state[x-1];
            cur -= state[y-1];
            state[x-1] = 0ll;
            state[y-1] = 0ll;
        }
        // vi to_print(state,state+n+1);
        // printv(to_print);
        // print(cur);
        // print("____");
        res += cur;
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