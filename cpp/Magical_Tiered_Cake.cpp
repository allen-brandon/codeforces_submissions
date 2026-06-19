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
int a[21];

void solve(int testcase) {
    //layers move out from under, don't take above with
    //greedily move bottom to 3
    //assume above tower is lined up, as required anyway
    ii(n);
    fr(i,1,n+1) {
        ii(x);
        a[i] = x;
    }
    //f(i,x,y): generate steps to get ith layer from place x to place y
    auto f = [&](int i, int x, int y, int z, auto& f) -> vector<tuple<int,int,int>> {
        int j = i-a[i]-1; //prev layer needed to move
        if (j>=i || j<0) return {}; //i not possible to resolve
        vector<tuple<int,int,int>> res{};
        if (j>0) {
            //move j to y so i can move to z
            res = f(j,x,z,y,f);
            if (res.empty()) return {}; //j not possible to resolve
        }
        res.emplace_back(i,x,z); //move x to z
        if (i>1) {
            //move j back to x if not i-1
            if (j<i-1) {
                if (j>0) {
                    //move j back
                    auto after = f(j,y,z,x,f);
                    res.insert(res.end(),after.begin(),after.end());
                }
                //move next layer from x to z
                auto nxt = f(i-1,x,y,z,f);
                if (nxt.empty()) return {};
                res.insert(res.end(),nxt.begin(),nxt.end()); //move next layer up    
            } else {
                //move next layer from y to z
                auto nxt = f(i-1,y,x,z,f);
                if (nxt.empty()) return {};
                res.insert(res.end(),nxt.begin(),nxt.end()); //move next layer up    
            }
        }
        return res;
    };
    vector<tuple<int,int,int>> res = f(n,1,2,3,f);
    if (res.empty()) {
        print(ny[0]);
        return;
    }
    print(ny[1]);
    print(res.size());
    for (auto [x,y,z] : res) {
        print(x << " " << y << " " << z);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}