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
// using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
// typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order(), order_of_key()
// typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
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
    ii(n); si(s);
    vector<pair<char,int>> a;
    fr(i,0,n) {
        char c = s[i];
        if (!a.empty() && c==a.back().first) {
            int x = a.back().second;
            a.pop_back();
            a.emplace_back(c,x+1);
        } else {
            a.emplace_back(c,1);
        }
    }
    // printm(a);
    int l = 0, r = 0;
    int odd = 0;
    fr(i,0,a.size()) {
        auto [c,x] = a[i];
        if (c=='F') {
            int par;
            if ((i>0) && (i<a.size()-1)) {
                char c1 = a[i-1].first;
                char c2 = a[i+1].first;
                if (c1==c2) {
                    r+=x+1;
                    l+=((x&1)==0);
                } else {
                    r+=x;
                    l+=(x&1);
                }
            } else if ((i==0) && (i==a.size()-1)) {
                l = 0;
                r = x-1;
                odd = 1;
                break;
            } else {
                odd = 1;
                r += x;
            }
        } else {
            l += x-1;
            r += x-1;
        }
    }
    vi res;
    for (int i = l; i<=r; i+=2-odd) {
        res.push_back(i);
    }
    print(res.size());
    for (int x : res) print(x);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}