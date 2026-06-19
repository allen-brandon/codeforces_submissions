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
int nxt[200001]; //nxt[i] == next occurrence of a[i]

void solve(int testcase) {
    ii(n);
    fill_n(nxt,n,n);
    map<int,int> prv;
    fr(i,0,n) {
        ii(x);
        a[i] = x;
        if (prv.contains(x)) {
            nxt[prv[x]] = i;
        }
        prv[x] = i;
    }
    int x = -1, y = -1;
    int j = -1, k = -1;
    int res{};
    fr(i,0,n) {
        // print("___");
        // vi test(a,a+i+1);
        // printv(test);
        // print(x << " " << y);
        int z = a[i];
        if (x==z || y==z) {
            if (x==z) j = i;
            if (y==z) k = i;
            continue;
        }
        res++;
        if (j == -1) {
            // print(1);
            x = z;
            j = i;
        } else if (k == -1) {
            // print(2);
            y = z;
            k = i;
        } else if (nxt[k]>nxt[j]) {
            // print(3);
            y = z;
            k = i;
        } else {
            // print(4);
            x = z;
            j = i;
        }
        // print("new: " << x << " " << y);
    }
    print(res);
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