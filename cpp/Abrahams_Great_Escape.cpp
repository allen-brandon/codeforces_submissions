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
    ii(n); ii(k);
    int x = k, y = n*n-k;
    if (y==1) {
        print(ny[0]);
        return;
    }
    vector<string> res;
    while (x>=n) {
        res.emplace_back(n,'U');
        x-=n;
    }
    if (res.size()==n) {
        print(ny[1]);
        for (string& row : res) {
            print(row);
        }
        return;
    }
    if (x==n-1) {
        res.push_back('D' + string(n-1,'U'));
    } else {
        res.push_back('R' + string(n-1-x,'L') + string(x,'U'));
    }
    while (res.size()<n) {
        string row = 'R' + string(n-1,'L');
        res.push_back(row);
    }
    print(ny[1]);
    for (string& row : res) {
        print(row);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}