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
int a[500001];
int b[500001][2];
int c[500001];


//g(x)!=f(x) when two swap saves time
//two swap saves time iff something needs to move more than 2
void solve(int testcase) {
    ii(n); ii(q);
    fr(i,0,n) {
        b[i][0] = -1;
        b[i][1] = n;
        c[i] = n;
    }
    fr(i,0,n) {
        ii(x);
        a[i] = x;
    }
    stack<pair<int,int>> st;
    fr(i,0,n) {
        int x = a[i];
        while (!st.empty() && st.top().first > x) {
            auto [y,j] = st.top();
            st.pop();
            b[j][1] = i;
        }
        st.emplace(x,i);
    }
    st = stack<pair<int,int>>();
    for (int i = n-1; i>=0; i--) {
        int x = a[i];
        while (!st.empty() && st.top().first < x) {
            auto [y,j] = st.top();
            st.pop();
            b[j][0] = i;
        }
        st.emplace(x,i);
    }
    fr(i,1,n-1) {
        auto [l,r] = b[i];
        if (l!=-1) {
            c[l] = min(c[l],r);
        }
    }
    for (int i = n-2; i>=0; i--) {
        c[i] = min(c[i],c[i+1]);
    }
    vi res;
    res.reserve(q);
    fr(i,0,q) {
        ii(l); ii(r);
        l--; r--;
        res.emplace_back(c[l]>r);
    }
    for (int x : res) {
        print(ny[x]);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}