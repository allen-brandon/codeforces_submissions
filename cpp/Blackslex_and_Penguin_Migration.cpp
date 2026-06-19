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

int a[101][101];
pair<int,int> ring[101]; //ordering for each next ring
vi levels[256]; // each id as dist from 1

void solve(int testcase) {
    ii(n);
    int m = n*n;
    fill_n(levels,n*2,vi());

    //find corner
    pair<int,int> msf = {0,2};
    fr(i,2,m+1) {
        print("? " << 1 << " " << i);
        cout.flush();
        ii(d);
        msf = max(msf, pair<int,int>({d,i}));
    }
    int s = msf.second;
    //bulid level order graph from corner
    fr(i,1,m+1) {
        if (i==s) continue;
        print("? " << s << " " << i);
        cout.flush();
        ii(d);
        levels[d].push_back(i);
    }
    //build placement/orientation
    a[0][0] = s;
    a[0][1] = levels[1][0];
    a[1][0] = levels[1][1];
    //parse each ring
    fr(depth,2,n*2) {
        if (levels[depth].empty()) break;
        vi& row = levels[depth];
        //get prev endpoint
        int i, j;
        if (depth<n) {
            i = depth-1;
            j = 0;
        } else {
            i = n-1;
            j = depth-n;
        }
        int x = a[i][j];
        fr(idx,0,row.size()) {
            print("? " << x << " " << row[idx]);
            cout.flush();
            ii(d);
            ring[idx] = {d,row[idx]};
        }
        sort(ring,ring+row.size());
        //account for first and second of row being equidistant to x
        if (row.size()>2 && j==0) {
            int y1 = ring[0].second, y3 = ring[2].second;
            print("? " << y1 << " " << y3);
            cout.flush();
            ii(d);
            if (d==2) swap(ring[0],ring[1]);
        }
        if (depth<n) {
            i = depth;
            j = 0;
        } else {
            i = n-1;
            j = depth+1-n;
        }
        fr(idx,0,row.size()) {
            auto [_,x] = ring[idx];
            a[i][j] = x;
            i--;
            j++;
        }
    }

    print("!");
    fr(i,0,n) {
        vi to_print(a[i],a[i]+n);
        printv(to_print);
    }
    cout.flush();
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}