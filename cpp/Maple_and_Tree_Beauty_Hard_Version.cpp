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
vi adj[200001];
int a[200001];
bitset<200001> dp;
bitset<200001> tmp;
int pref[200001];

void solve(int testcase) {
    ii(n); ii(k);
    fill_n(adj,n,vi());
    fill_n(a,n,0);
    dp[0] = 1;
    fr(v,1,n) {
        dp[v] = 0;
        ii(u); u--;
        adj[u].push_back(v);
    }
    dp[n] = 0;
    int msf = n; //min leaf depth
    stack<pair<int,int>> st;
    st.push({0,0});
    while (!st.empty()) {
        auto [u,d] = st.top();
        st.pop();
        a[d]++;
        if (adj[u].size()==0) {
            msf = min(msf,d+1);
        }
        for (auto v : adj[u]) {
            st.push({v,d+1});
        }
    }
    partial_sum(a,a+msf,pref+1);
    int m = pref[msf];
    map<int,int> c;
    fr(i,0,msf) {
        c[a[i]]++;
    }
    for (auto [x,f] : c) {
        int lim = x*(f+1);
        fr(o,0,x) {
            int cur = 0;
            for (int i=o; i<=n; i+=x) {
                cur+=dp[i];
                if (i>=lim+o) {
                    cur-=dp[i-lim];
                }
                dp[i] = dp[i] | int(cur>0);
            }
        }
    }
    int z = k, o = n-k;
    int lb = max(0,m-o), rb = min(m,z);
    bool valid = false;
    fr(i,lb,rb+1) {
        if (dp[i]==1) {
            valid = true;
            break;
        }
    }
    int res = valid? msf : msf-1;
    print(res);
    // print("");
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}