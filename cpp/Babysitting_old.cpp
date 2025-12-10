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
vi adj[400001]; //implication graph
vi rev[400001]; //reverse implication
int order[400001]; //order of dfs
int cycle[400001]; //scc group for u
bitset<400001> seen;

void kosaraju(int n, int m, int th) {
    int order_idx = 0;
    //forward dfs
    fr(i,0,n*2) seen[i] = 0;
    fr(i,0,n*2) { //all positive cnf
        if (seen[i]) continue;
        seen[i] = 1;
        stack<tuple<int,int>> st;
        st.emplace(i,1);
        while (!st.empty()) {
            auto [u,d] = st.top();
            st.pop();
            if (d==0) {
                order[order_idx++] = u;
                continue;
            }
            st.emplace(u,0);
            if (u<n) { //truthood implies range of falsehoods
                for (int v = u+n+1; v < min(u+n+th, n*2); v++) {
                    if (seen[v]) continue;
                    seen[v] = 1;
                    st.emplace(v,1);
                }
                for (int v = min(u+n+th, n*2)-1; v > u+n; v--) {
                    if (seen[v]) continue;
                    seen[v] = 1;
                    st.emplace(v,1);
                }
                for (int v = u+n-1; v > max(u+n-th, n-1); v--) {
                    if (seen[v]) continue;
                    seen[v] = 1;
                    st.emplace(v,1);
                }
                for (int v = max(u+n-th, n-1)+1; v < u+n; v++) {
                    if (seen[v]) continue;
                    seen[v] = 1;
                    st.emplace(v,1);
                }
            } else { //falsehood implies select discrete truthoods
                for (int v : adj[u]) {
                    if (seen[v]) continue;
                    seen[v] = 1;
                    st.emplace(v,1);
                }
            }
        }
    }
    //backward dfs
    reverse(order,order+n*2);
    fr(i,0,n*2) seen[i] = 0;
    int scc = 0;
    fr(idx,0,n*2) {
        int i = order[idx];
        if (seen[i]) continue;
        seen[i] = 1;
        stack<int> st;
        st.push(i);
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            cycle[u] = scc;
            if (u>=n) { //falsehood implied by range of truthoods
                for (int v = u-n+1; v < min(u-n+th, n); v++) {
                    if (seen[v]==1) continue;
                    seen[v] = 1;
                    st.push(v); 
                }
                for (int v = min(u-n+th, n)-1; v > u-n; v--) {
                    if (seen[v]==1) continue;
                    seen[v] = 1;
                    st.push(v);     
                }
                for (int v = u-n-1; v > max(u-n-th, -1); v--) {
                    if (seen[v]==1) continue;
                    seen[v] = 1;
                    st.push(v);     
                }
                for (int v = max(u-n-th,-1)+1; v<u-n; v++) {
                    if (seen[v]==1) continue;
                    seen[v] = 1;
                    st.push(v);     
                }
            } else { //truthood implied by discrete falsehoods
                for (int v : rev[u]) {
                    if (seen[v]==1) continue;
                    seen[v] = 1;
                    st.push(v); 
                }
            }
        }
        scc++;
    }
}

bool sat(int n, int m) {
    fr(i,0,n) {
        if (cycle[i]==cycle[i+n]) return false;
    }
    return true;
}

void solve(int testcase) {
    ii(n); ii(m);
    fill_n(adj,n*2,vi());
    fill_n(rev,n*2,vi());
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        adj[u+n].push_back(v);
        rev[v].push_back(u+n);
        adj[v+n].push_back(u);
        rev[u].push_back(v+n);
    }
    auto check = [n,m](int th) -> bool {
        kosaraju(n,m,th);
        return sat(n,m);
    };
    int l = 0, r = n+1;
    while (r-l>1) {
        int th = l+(r-l)/2;
        if (check(th)) {
            l = th;
        } else {
            r = th;
        }
        if (th==3) {
            vi test(cycle,cycle+n*2);
            printv(test);
        }
    }
    print(l);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}