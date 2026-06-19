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
ll a[100001];

void solve(int testcase) {
    //greedy formulation:
    //if x!=y, gcd(x,y) <= abs(x-y)
    //therefore when x<y, x + gcd(x,y) + gcd(gcd(x,y), z) <= y + gcd(y, z)
    //always greedily minimize gcd
    //extrapolates to first value as well (assume implicit 0th element, which is lcm of all elements)
    
    //complexity evaluation:
    //any x!=y will have gcd<=min(x,y)/2
    //therefore only logn distinct y can occur before gcd == 1
    //linearly find the minimum for each append until 1 or unchanging
    ii(n);
    pair<ll,int> msf = {mod,mod};
    fr(i,0,n) {
        lli(x);
        a[i] = x;
        msf = min(msf, {x,i});
    }
    auto [x,i] = msf; //start with smallest
    // a[i] = -1ll; //skip -1's
    ll pop = n; //track remaining population
    swap(a[i], a[--pop]);
    ll res = x;
    msf = {mod,mod}; //min next gcd
    while (x!=1ll && pop!=0) { //O(logn)
        msf = {mod,mod};
        fr(i,0,pop) { //O(n)
            // if (a[i]==-1ll) continue;
            msf = min(msf, {gcd(x,a[i]),i}); //O(logn)
        }
        auto [new_x, idx] = msf;
        // a[idx] = -1ll;
        res += new_x;
        // print(x << " " << new_x << " " << pop);
        swap(a[idx],a[--pop]);
        if (x==new_x) break;
        x = new_x;
    }
    res += pop*x;
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}