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
ll mod = 1000000007;
int a[10][200001];

void solve(int testcase) {
    ii(n); ii(k);
    vi cur;
    map<int,int> c;
    cur.reserve(n);
    fr(i,0,n) {
        ii(x);
        cur.push_back(x);
    }
    fr(op,1,k+1) {
        c.clear();
        fr(i,0,n) {
            c[cur[i]]++;
            a[op-1][i] = cur[i];
        }
        int mx = 0;
        for (auto [x,f] : c) {
            if (x==mx) mx++;
        }
        fr(i,0,n) {
            cur[i] = c[cur[i]]==1 && cur[i]<mx? cur[i] : mx;
        }
        // print(mx);
        // printv(cur);
        //eq to one before
        bool eq = true;
        fr(i,0,n) {
            if (a[op-1][i]!=cur[i]) {
                eq = false;
                break;
            }
        }
        if (eq) {
            ll res = accumulate(cur.begin(),cur.end(),0ll);
            print(res);
            return;
        }
        if (op>1) {
            eq = true;
            fr(i,0,n) {
                if (a[op-2][i]!=cur[i]) {
                    eq = false;
                    break;
                }
            }
            if (eq) {
                ll res = 0;
                fr(i,0,n) {
                    res+=((k-op)&1)?  a[op-1][i] : cur[i];
                }
                print(res);
                return;
            }
        }
    }
    ll res = accumulate(cur.begin(),cur.end(),0ll);
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}