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
pair<int,int> a[200001];

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        ii(x);
        a[i] = make_pair(x,x);
    }
    fr(i,0,n) {
        ii(x);
        int y = a[i].first;
        // if (y>x) swap(x,y);
        a[i] = make_pair(x,y);
    }
    // if (testcase!=3) return;
    sort(a,a+n);
    // vector<pair<int,int>> test(a,a+n);
    // printm(test);
    int swaps = 0;
    int valid = 1;
    fr(i,0,n-1) {
        auto [x,y] = a[i];
        auto [x1,y1] = a[i+1];
        if (x>x1 || y>y1) {
            swaps^=1;
            swap(x,y);
        }
        if (x>x1 || y>y1) valid = 0;
    }
    valid &= (swaps==0);
    print(swaps);
    print(ny[valid]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}