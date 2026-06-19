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
bitset<5001> bs;
bitset<5001> res;

void solve(int testcase) {
    ii(n); ii(k);
    si(s);
    fr(i,0,n) {
        bs[i] = s[i] == '(';
        res[i] = 0;
    }
    // print(s);
    vector<stack<int>> zo(2);
    int cur = 0; // '(' - ')'
    fr(i,0,n) {
        cur += bs[i] - (bs[i]^1);
        zo[bs[i]].push(i);
        if (cur<0) {
            while (k!=0 && !zo[1].empty()) {
                int j = zo[1].top();
                zo[1].pop();
                res[j] = 1;
                k--;
            }
            if (k==0) break;
            while (!zo[0].empty()) zo[0].pop();
            while (!zo[1].empty()) zo[1].pop();
            cur = 0;
        }
    }
    while (k!=0 && !zo[0].empty()) {
        int j = zo[0].top();
        zo[0].pop();
        res[j] = 1;
        k--;
    }
    fr(i,0,n) cout << res[i];
    cout << '\n';
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}