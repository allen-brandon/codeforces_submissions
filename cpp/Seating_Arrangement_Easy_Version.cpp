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

void solve(int testcase) {
    ii(n); ii(x); ii(s);
    si(u);
    // if (testcase!=1) return;
    // m: # of 2 assigned to own table
    // {res1: # of ppl seated, res2: whether tables were sufficient}
    auto check = [&](int th) -> pair<int,bool> {
        int m = th;
        int res1{};
        bool res2 = true;
        ll seats{}, tables = x; //remaining open seats/tables
        fr(i,0,n) {
            if (u[i]=='I') {
                if (tables) {
                    tables--;
                    seats+=s-1;
                    res1++;
                }
            } else if (u[i]=='E') {
                if (seats>0) {
                    res1++;
                    seats--;
                } else if (m==0) {
                    res2 = false;
                }
            } else {
                if (m>0 && tables>0) {
                    m--;
                    res1++;
                    seats+=s-1;
                    tables--;
                } else if (seats>0) {
                    res1++;
                    seats--;
                } else {
                    res2 = false;
                }
            }
        }
        // print(th << " _ " << res1 << " " << res2);
        return {res1, res2};
    };
    int l = 0, r = count(u.begin(),u.end(),'A');
    while (r-l>1) {
        int m = l+(r-l)/2;
        // print(l << " " << m << " " << r);
        if (check(m).second) r = m;
        else l = m;
    }
    // print(l << " " << r);
    print(max(check(l).first, check(r).first));
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}