#ifdef LOCAL
#include "_pch.hpp"
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define USE_INPUT_FILE(file)
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
ll mod =  676767677;
ll a[100001];
int b[100001];


void solve(int testcase) {
    lli(n);
    bool same = 1;
    fr(i,0,n) {
        lli(x);
        a[i] = x;
        if (i!=0) same &= a[i] == a[i-1];
    }
    int inc = 1, dec = 1;
    b[0] = 1;
    fr(i,1,n) {
        ll l = a[i-1], r = a[i];
        if (abs(r-l)>1) {
            print(0);
            return;
        }
        if (r>l) {
            if (b[i-1]==0) {
                inc = 0;
                break;
            }
            b[i] = b[i-1];
        } else if (r<l) {
            if (b[i-1]==1) {
                inc = 0;
                break;
            }
            b[i] = b[i-1];
        } else {
            b[i] = b[i-1]^1;
        }
    }
    int cur = accumulate(b,b+n-1,1);
    for (int i = n-1; i>=0; i--) {
        if (a[i] != cur) {
            inc = 0;
            break;
        }
        cur -= b[i]==1;
        if (i!=0) cur += b[i-1]==0;
    }
    b[0] = 0;
    fr(i,1,n) {
        ll l = a[i-1], r = a[i];
        if (abs(r-l)>1) {
            print(0);
            return;
        }
        if (r>l) {
            if (b[i-1]==0) {
                dec = 0;
                break;
            }
            b[i] = b[i-1];
        } else if (r<l) {
            if (b[i-1]==1) {
                dec = 0;
                break;
            }
            b[i] = b[i-1];
        } else {
            b[i] = b[i-1]^1;
        }
    }
    cur = accumulate(b,b+n-1,1);
    for (int i = n-1; i>=0; i--) {
        if (a[i] != cur) {
            dec = 0;
            break;
        }
        cur -= b[i]==1;
        if (i!=0) cur += b[i-1]==0;
    }
    print(inc + dec);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}