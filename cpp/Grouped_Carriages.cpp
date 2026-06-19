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
int a[200001]; //pop of i
vector<pair<int,int>> b[200001]; //pop added at i
int d[200001]; //max dist from i

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        ii(x);
        a[i] = x;
    }
    fill_n(b,n,vector<pair<int,int>>());
    fr(i,0,n) {
        ii(x);
        d[i] = x;
        int l = max(0,i-d[i]);
        int r = min(n-1,i+d[i]);
        b[l].emplace_back(r,a[i]);
    }
    d[n] = 0;
    auto check = [&](ll m) {
        //heap: {earliest required dest, pop}
        priority_queue<pair<int,ll>,vector<pair<int,ll>>,greater<pair<int,ll>>> h;
        fr(i,0,n) {
            ll x = 0; //amt in this car
            for (auto [r,x] : b[i]) {
                h.emplace(r,x);
            }
            //fill x
            while (!h.empty() && x<m) {
                auto [j, y] = h.top();
                h.pop();
                ll dx = min(m-x,y);
                x+=dx;
                // if (m==6) print("popping: (" << j << ", " << y << "): x: " << x);
                y-=dx;
                if (y>0ll) {
                    h.emplace(j,y);
                }
            }
            //fill x
            while (!h.empty() && h.top().first==i) {
                auto [j,y] = h.top();
                h.pop();
                x+=y;
            }
            // if (m==6) print("i,x: (" << i << " " << x << ")");
            if (x>m) return 0;
        }
        return 1;
    };
    ll l = -1, r = accumulate(a,a+n,0ll);
    while (r-l>1) {
        ll m = l+(r-l)/2;
        // print(m << "_______");
        if (check(m)) {
            // print("worked");
            r = m;
        } else {
            // print("didn't work");
            l = m;
        }
    }
    print(r);
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