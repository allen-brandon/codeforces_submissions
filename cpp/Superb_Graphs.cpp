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
vi adj[301];
vi adj1[602];
vi rev[602];
int sat[602]; // u<<1: independent, u<<1|1: clique
bitset<602> seen;
int vis[602];

void solve(int testcase) {
    ii(n); ii(k);
    int res = 1;
    fill_n(sat,n*2,-1);
    fill_n(adj1,n*2+1,vi());
    fill_n(rev,n*2+1,vi());
    fr(q,0,k) {
        ii(m);
        fill_n(adj,n+1,vi());
        fr(i,0,m) {
            ii(u); ii(v);
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        fr(u,0,n) sort(adj[u].begin(),adj[u].end());
        fr(u,0,n) {
            fr(v,u+1,n) {
                if (adj[u].size()!=adj[v].size()) continue;
                //same open nei
                if (adj[u]==adj[v]) {
                    adj1[u<<1].push_back(v<<1|1);
                    adj1[v<<1].push_back(u<<1|1);
                    rev[v<<1|1].push_back(u<<1);
                    rev[u<<1|1].push_back(v<<1);
                }
                if (find(adj[u].begin(),adj[u].end(),v) == adj[u].end()) continue;
                bool same = 1;
                for (int i=0, j=0; i<adj[u].size(); i++, j++) {
                    if (adj[u][i]==v) i++;
                    if (adj[v][j]==u) j++;
                    if (i!=adj[u].size() && adj[u][i]!=adj[v][j]) {
                        same = 0;
                        break;
                    }
                }
                if (same) {
                    adj1[u<<1|1].push_back(v<<1);
                    adj1[v<<1|1].push_back(u<<1);
                    rev[v<<1].push_back(u<<1|1);
                    rev[u<<1].push_back(v<<1|1);
                }
            }
        }
    }
    // if (testcase!=2) return;
    fr(u,0,n) {
        seen[u<<1] = 0;
        seen[u<<1|1] = 0;
    }
    int vis_idx = 0;
    fr(i,0,n<<1) {
        if (seen[i]) continue;
        stack<pair<int,int>> st;
        st.emplace(i,1);
        while (!st.empty()) {
            auto [u,d] = st.top();
            st.pop();
            if (d==0) {
                vis[vis_idx++] = u;
                continue;
            }
            if (seen[u]) continue;
            seen[u] = 1;
            st.emplace(u,0);
            for (const auto& v : adj1[u]) {
                if (seen[v]) continue;
                st.emplace(v,1);
            }
        }
    }
    reverse(vis,vis+vis_idx);
    fr(u,0,n) {
        seen[u<<1] = 0;
        seen[u<<1|1] = 0;
    }
    fr(i,0,n<<1) {
        int x = vis[i];
        if (seen[x]) continue;
        stack<int> st;
        st.push(x);
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            if (seen[u]) continue;
            sat[u] = x;
            seen[u] = 1;
            for (const auto& v : rev[u]) {
                if (seen[v]) continue;
                st.push(v);
            }
        }
    }
    // vi sat_test(sat,sat+n*2);
    // printv(sat_test);
    fr(i,0,n) {
        if (sat[i<<1]==sat[i<<1|1] && sat[i<<1]!=-1) {
            res = 0;
            break;
        }
    }
    print(ny[res]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}