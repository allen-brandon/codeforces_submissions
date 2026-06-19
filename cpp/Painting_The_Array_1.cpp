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

void solve(int testcase) {
    ii(n);
    fr(i,0,n) {
        ii(x);
        a[i] = x;
    }
    if (n==1) {
        print(1);
        return;
    }
    // 1 1 2 3 2 2 -0
    // 1 1 2 2 1 2 2 -1
    // 2 2 1 2 1 2 1 2 2 -1
    // 2 2 1 3 1 2 1 2 2 -0
    
    // 2 2 2 -1
    // 2 2 1 2 2 -1
    // 2 2 1 2 1 2 2 -1
    // >= (x+3)/2
    // 2 2: must be (2,2) or detract
    // 2 2 1 2: must
    // 2 2 1 2 1 2: must
    // 2:2, 4:3, 6:4, 8:5, 
    //iterate, see if next val is mjamority element
    //greedily reset when chain is broken

    //first and second most recently seen
    tuple<int,int,int> p1 = {0,0,-1}, p2 = {0,0,-2};
    int res = 0; //# of redundancies
    fr(i,0,n) {
        int x = a[i];
        auto [f1,x1,i1] = p1;
        auto [f2,x2,i2] = p2;
        if (x==x1) {
            f1++;
            //check if p1 majority
            int th = (i+4-i1);
            if (f1*2>=th) {
                res++;
                // print("test" << " " << i);
            }
            //reset to greedily find majority
            p1 = {2,x1,i-1};
        } else if (x==x2) {
            p2 = {f2+1,x2,i2};
            swap(p1,p2); //p2 now more recently seen
        } else {
            //replace least recently seen
            p2 = {1,x,i};
            swap(p1,p2);
        }
        // print(get<0>(p1) << " " << get<1>(p1) << " " << get<2>(p1));
        // print(get<0>(p2) << " " << get<1>(p2) << " " << get<2>(p2));
        // print("______");
    }
    print(n-res);
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