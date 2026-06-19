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
int a[100001]; //locations of packmen
int b[100001]; //location of asterisks


void solve(int testcase) {
    ii(k);
    si(s);
    int n{}, m{};
    fr(i,0,k) {
        if (s[i]=='P') a[n++] = i;
        if (s[i]=='*') b[m++] = i;
    }
    // vi test(a,a+n);
    // printv(test);
    // vi test1(b,b+m);
    // printv(test1);

    auto check = [&](int th) {
        queue<int> q(b,b+m);
        fr(i,0,n) {
            if (q.empty()) break;
            int x = a[i], dx = th;
            int y = q.front();
            if (y<x) {
                if (y<x-dx) break;
                while (!q.empty() && q.front()<=x) q.pop();
                //go to y then back of forward and back to y
                dx = max(th-(x-y)*2, (th-(x-y))/2);
            }
            while (!q.empty() && q.front()<=x+dx) q.pop();
        }
        return q.empty();
    };

    int l = 0, r = k*2;
    while (l<r-1) {
        int th = l+(r-l)/2;
        if (check(th)) {
            // if (th<10) print("th: " << th << " worked");
            r = th;
        } else {
            // if (th<10) print("th: " << th << " didn't work");
            l = th;
        }
    }
    print(r);
}

// struct segment_tree {
//     private:
//     int n;
//     public:
//     segment_tree(int n): n(n) {

//     }

//     void update(int u) {

//     }

//     void prop(int u) {

//     }

//     void chmin(int u, int lb, int rb, int l, int r, int x) {

//     }
// };
int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}