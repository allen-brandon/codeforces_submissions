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
pair<int,int> a[100001];

void solve(int testcase) {
    //bisect for ans
    //each step, check if reachable
    //combine all elements containing only < th, then all elements containing >= th
    //check if res >= th
    ii(n);
    int msf = 1;
    fr(i,0,n) {
        ii(x);
        msf = max(msf,x);
        a[i] = {x,x};
    }
    fr(i,0,n) {
        ii(y);
        msf = max(msf,y);
        a[i] = {a[i].first,y};
    }

    //00: both below, 10: one above, 11: both above
    auto f = [&](int x, int y) -> int {
        if (x==2) return y;
        if (y==2) return x;
        if (x==y) return x;
        return 2;
    };

    auto check = [&] (int m) {
        //elim all 00 w 00/10
        //elim all 10 together
        //count 10 vs. 11
        vi st;
        // vi tp;
        //combine all 00/10, partitioned by 11
        fr(i,0,n) {
            auto [p1,p2] = a[i];
            if (p2<p1) swap(p1,p2);
            int x = (p1>=m)^((p2>=m)<<1);
            // tp.push_back(x);
            if (st.empty()) {
                st.push_back(x);
                continue;
            }
            int y = st.back();
            if (x!=3 && y!=3) {
                st.pop_back();
                st.push_back(f(x,y));
            } else {
                st.push_back(x);
            }
        }
        // printv(tp);
        // printv(st);
        //need at least as many 11 as 00; 10 is nonfactor
        int zz{}, oo{};
        fr(i,0,st.size()) {
            zz+=st[i]==0;
            oo+=st[i]==3;
        }
        return oo>zz;
    };
    int l = 1, r = msf+1;
    while (r-l>1) {
        int m = l+(r-l)/2;
        // print(m << "--");
        if (check(m)) l = m;
        else r = m;
    }
    // print("");
    print(l);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}