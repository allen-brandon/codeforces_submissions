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
int arr[200001];
array<vi,400001> a; //vector for this section
int b[400001]; //score for this section

void testcase() {
    ii(m);
    fr(i,0,m) {
        ii(x);
        arr[i] = x;
    }
    int n = 1;
    while (n<m) n<<=1;
    fr(i,0,m) {
        a[i+n] = {arr[i]};
        b[i+n] = 0;
    }
    fr(i,m,n) {
        a[i+n] = {};
        b[i+n] = 0;
    }
    for (int i = n-1; i>0; --i) {
        a[i].clear();
        vi l = a[i<<1],r = a[i<<1|1]; //might cause probems w order of operations <<
        a[i].reserve(l.size()<<1);
        int l_idx = 0, r_idx = 0;
        while (l_idx<l.size() || r_idx<r.size()) {
            if (l_idx==l.size()) {
                a[i].push_back(r[r_idx++]);
            } else if (r_idx==r.size()) {
                a[i].push_back(l[l_idx++]);
            } else if (r[r_idx]<l[l_idx]) {
                a[i].push_back(r[r_idx++]);
            } else {
                a[i].push_back(l[l_idx++]);
            }
        }
        b[i] = max(b[i<<1],b[i<<1|1]);
        if (!a[i].empty()) b[i] = max(b[i],a[i][(a[i].size()+1)/2]-a[i][0]);
        // print(i << " " << a[i][(a[i].size()+1)/2]-a[i][0]);
    }
    print("");
    print(b[1]);
    print("_________________");
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}