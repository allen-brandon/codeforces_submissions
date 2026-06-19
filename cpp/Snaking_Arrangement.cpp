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
// int a[5001][5001];
ll mfac[5001];
tuple<int,int,string> snakes[5001]; //{len, midpoint location, string}
int a[5001]; //taken locations (segtree unnecessary, O(n-k) new snakes * O(k) snakes == O(n^2) regardless)
//could do in O(nlogn) by sorting snakes, parsing new snakes small -> large, bsearch for smallest larger, querying/setting segtree
//because you only need to find smallest smake larger than new placed snake
//need additional functionality to set lowest 0 to 1 (not arbitary 0 to 1)

void solve(int testcase) {
    //lgst snake: 0,0...n,n
    //2nd: (0,1)...(n-1,n) or (1,0)...(n,n-1)
    //look at what group each snake needs to go into
    //res = modfac(x) for each group, where x is # of snakes
    //look at beginning spots
    //for each snake, R/D dictates next smaller snake's side on that partition
    //e.g. snake (1) partitions nothing, snake (2n-1) partitions all onto one side or another

    //approach:
    //for each new snake, find valid range it can exist (pass through midline r==-c)
    //look through each preset snake at its diag index to get l/r of valid range
    //i.e. "R" -> chmax(l), "D" -> chmin(r)
    //look at segtree for number of 1s in range. Set one of them to 0
    //place small -> large so that small snakes can be placed arbitrarily
    string URDL = "URDL";
    ii(n); ii(k);
    fill_n(a,n+1,0);
    fr(idx,0,k) {
        ii(m);
        ii(i); ii(j);
        i--; j--;
        string s = "";
        if (m>1) {
            cin >> s;
        }
        fr(jdx,0,m-1) {
            auto [di,dj] = didj[find(URDL.begin(),URDL.end(),s[jdx])-URDL.begin()];
            i += di;
            j += dj;
            if (i==n-1-j) break; //found midline
        }
        snakes[idx] = {m,j,s};
        a[j] = 1;
    }
    sort(snakes,snakes+k);
    //len of snake -> {l,r} valid bounds
    auto get_bounds = [&](int m) -> pair<int,int> {
        int l = 0, r = n;
        //parse snakes large -> small to break early
        for (int idx = k-1; idx>=0; idx--) {
            //len, midpoint idx, string
            auto [m1,i,s] = snakes[idx];
            if (m1==m) return {0,0}; //if snake preplaced just return default
            if (m1<m) break;
            int dm = m1-m;
            int jdx = dm/2-1;//point in s this cares about
            if (s[jdx]=='D') l = max(l,i+1); //l inc, r exc
            if (s[jdx]=='R') r = min(r,i);
        }
        // print(m << " " << l << " " << r);
        return {l,r};
    };
    // if (testcase!=5) return;
    //place all new snakes
    ll res = 1;
    for (int m = 1; m <= n*2-1; m += 2) {
        auto [l,r] = get_bounds(m);
        if (l==r) continue; //already placed
        ll cur = 0;
        fr(i,l,r) {
            cur += 1^a[i];
        }
        res = (res*cur) % mod;
        fr(i,l,r) {
            if (a[i]==0) {
                a[i]++; //place this arbitrarily at first empty spot
                break;
            }
        }
        // print("____");
        // print(m << " " << cur << " " << res);
        // print("(" << l << ", " << r << ")");
        // vi test(a,a+n);
        // printv(test);
        // print("____");
    }
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