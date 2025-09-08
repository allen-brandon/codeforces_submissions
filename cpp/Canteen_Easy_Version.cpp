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
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_of_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
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
int b[200001];

void solve(int testcase) {
    ii(n); ii(k);
    fr(i,0,n) {
        ii(x);
        a[i] = x;
    }
    ordered_set s;
    fr(i,0,n) {
        ii(x);
        b[i] = x;
        s.insert(i);
    }
    // if (testcase!=4) return;
    // t, i
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    fr(i,0,n) {
        pq.emplace(1,i);
    }
    int res = 0;
    while (!pq.empty()) {
        auto [t,i] = pq.top();
        pq.pop();
        res = t;
        int next_t;
        int s_idx = s.order_of_key((i+t-1)%n);
        if (s_idx==s.size()) s_idx = s.order_of_key(0);
        //next b[j] that isn't 0
        int j = *s.find_by_order(s_idx);
        // print(t << " " << i << " " << j);
        // print(t << " " << i << " " << s_idx << " " << j);
        if (j!=(i+t-1)%n) {
            next_t = j+1-i;
            if (j<i) next_t+=n;
            pq.emplace(next_t,i);
            continue;
        }
        int x = min(a[i],b[j]);
        a[i]-=x;
        b[j]-=x;
        if (b[j]==0) s.erase(j);
        if (a[i]!=0) {
            s_idx = s.order_of_key((j+1)%n);
            if (s_idx==s.size()) s_idx = s.order_of_key(0);
            j = *s.find_by_order(s_idx);
            next_t = j+1-i;
            if (j<i) next_t+=n;
            pq.emplace(next_t,i);
        }
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}