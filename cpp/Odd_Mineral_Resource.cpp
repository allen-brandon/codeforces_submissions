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
vi adj[300001]; //base tree
int a[300001]; //arr for vals
int bin[300001][20]; //bin lifting
vi vals[300001]; //vertices w given val
vi tags[1048577]; //query tags on segtree (vals are implicit)
pair<int,int> lr[300001]; //l/r in base et
pair<int,int> tour[1048577]; //tour in seg: {idx in base et, val} (filled/sorted each seg)
tuple<int,int,int> queries[300001];
vector<tuple<int,int,int,int,int>> buckets[2001]; //mo's {tour idx, l, r, res idx} (clear each time)
int res[300001]; //!=-1: solved
bitset<300001> par; //for mo's

class segment_tree {
    private:
    public:
    int n;
    segment_tree(int m) {
        if (m==1) {
            n = 1;
        } else {
            n = 1<<(32-__builtin_clz(m-1));
        }
        fill_n(tags,n*2,vi());
    }

    vi get_range(int l, int r) {
        vi res;
        for (l += n, r += n; l<r; l>>=1, r>>=1) {
            if (l&1) res.push_back(l++);
            if (r&1) res.push_back(--r);
        }
        return res;
    }

    //reconcile all vals w all queries at this seg
    void solve(int idx, int lb, int rb) {
        //no relevant queries, just return
        if (tags[idx].empty()) return;
        int m = 0; //len of sub-tour
        fr(val,lb,rb) {
            for (auto& i : vals[val]) {
                //get where val begins/ends in tour
                auto [s,e] = lr[i];
                tour[m++] = {s,val};
                tour[m++] = {e,val};
            }
        }
        //no relevant vals, just return
        if (m==0) return;
        //construct new euler subtree of relevant vals
        sort(tour,tour+m);
        //translate and bucket queries
        int t_count = 0;
        int b_size = lrint(sqrt(m)); //maybe just 500 idk
        fill_n(buckets,m/b_size+10,vector<tuple<int,int,int,int,int>>());
        for (auto& t : tags[idx]) {
            if (res[t]!=-1) continue;
            t_count++;
            auto [u,lca,v] = queries[t];
            int u_idx = lr[u].second; //go up from u
            int v_idx = lr[v].first; //go down to v
            //if u!=lca: u...lca, lca+1...v counted, lca inserted below
            //if u==lca: start at u...v, then don't insert lca (u) again below
            //v can't be lca since u!=v, lr[u][0]<lr[v][0]
            if (u==lca) {
                u_idx = lr[u].first;  //go down not up
                lca = -1; //dont ins later
             } else if (a[lca]<lb || a[lca]>=rb) {
                lca = -1; //not relevant
             }

            //conv to tour idx for bucket
            //val on u/v matters but not here
            int l_idx = lower_bound(tour,tour+m,pair<int,int>({u_idx,0})) - tour;
            int r_idx = upper_bound(tour,tour+m,pair<int,int>({v_idx,n+1})) - tour;
            if (l_idx==r_idx) {
                //lca only thing in range (not seen)
                if (lca!=-1) {
                    res[t] = a[lca];
                }
                continue; //no relevant vals in range
            }
            //b by l
            buckets[l_idx/b_size].emplace_back(l_idx,u_idx,v_idx,lca,t);
        }
        //all queries here solved
        if (t_count==0) return;
        //p sure # of b <= m/b_size + 5
        fr(b_idx,0,m/b_size+5) {
            auto& bucket = buckets[b_idx];
            if (bucket.empty()) continue;
            //sort by r
            sort(bucket.begin(),bucket.end(), [](const auto& a, const auto& b) {
                return get<2>(a) < get<2>(b);
            });
            //brute reset all par (O(m))
            fr(i,0,m) {
                par[tour[i].second] = 0;
            }
            //stack to know which are cur odd (O(1) per idx)
            stack<int> stk;
            int l = get<0>(bucket[0]); //inc
            int r = l; //inc
            int x = tour[l].second;
            par[x] = 1;
            stk.push(x);
            for (auto& [_, u_idx, v_idx, lca, res_idx] : bucket) {
                //dec l if needed (include u)
                while (l>0 && tour[l-1].first>=u_idx) {
                    int x = tour[l-1].second;
                    par[x] = par[x]^1;
                    if (par[x]==1) stk.push(x);
                    l--;
                }
                //inc r (include v)
                while (r<m-1 && tour[r+1].first<=v_idx) {
                    int x = tour[r+1].second;
                    par[x] = par[x]^1;
                    if (par[x]==1) stk.push(x);
                    r++;
                }
                //inc l if needed (keep u)
                while (l<m && tour[l].first<u_idx) {
                    int x = tour[l].second;
                    par[x] = par[x]^1;
                    if (par[x]==1) stk.push(x);
                    l++;
                }
                //dec r if needed (keep v)
                while (r>-1 && tour[r].first>v_idx) {
                    int x = tour[r].second;
                    par[x] = par[x]^1;
                    if (par[x]==1) stk.push(x);
                    r--;
                }
                //look for odd par
                //account for lca value being uncounted
                //only if u!=lca (lca!=-1)
                if (lca!=-1 && par[a[lca]]==0) {
                    res[res_idx] = a[lca];
                    continue;
                }
                if (lca!=-1) {
                    par[a[lca]] = par[a[lca]] ^ 1;
                    if (par[a[lca]]==1) stk.push(a[lca]);
                }
                while (!stk.empty() && par[stk.top()]==0) stk.pop();
                if (!stk.empty()) {
                    res[res_idx] = stk.top();
                }
                if (lca!=-1) {
                    par[a[lca]] = par[a[lca]] ^ 1;
                    if (par[a[lca]]==1) stk.push(a[lca]);
                }
            }
        }
    }

    //exclusive of r, {idx in tags, val bounds, current population}
    void dfs(int idx, int l, int r, int q) {
        if (idx>=n*2) return;
        int m = l+(r-l)/2;
        // print(idx << " (" << l << ", " << r << ")");
        solve(idx,l,r);
        // vi test(res,res+q);
        // printv(test);
        // print("______________");
        dfs(idx<<1,l,m,q);
        dfs(idx<<1|1,m,r,q);
    }
};


void solve(int testcase) {
    ii(n); ii(q);
    fill_n(adj,n,vi());
    fill_n(res,q+1,-1);
    fill_n(vals,n+1,vi());
    fr(i,0,n) {
        ii(x);
        a[i] = x;
    }
    fr(i,0,n-1) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int tour_idx = 0;
    //ver, par, dir
    stack<tuple<int,int,int>> stk;
    stk.emplace(0,0,1);
    fill_n(bin[0],20,0); //root
    while (!stk.empty()) {
        auto [u,p,d] = stk.top();
        stk.pop();
        if (d==0) {
            lr[u] = {lr[u].first,tour_idx++};
            continue;
        }
        stk.emplace(u,p,0);
        bin[u][0] = p;
        fr(j,1,20) {
            bin[u][j] = bin[bin[u][j-1]][j-1];
        }
        lr[u] = {tour_idx++,0};
        vals[a[u]].push_back(u);
        for (auto& v : adj[u]) {
            if (v==p) continue;
            stk.emplace(v,u,1);
        }
    }
    auto lca = [&](int u, int v) {
        const auto& [ul,ur] = lr[u];
        const auto& [vl,vr] = lr[v];
        if (ul<=vl && vr<=ur) return u;
        if (vl<=ul && ur<=vr) return v;
        int p = u;
        for (int j = 19; j >= 0; j--) {
            int new_p = bin[p][j];
            const auto& [pl,pr] = lr[new_p];
            if (pl<=vl && vr<=pr) continue;
            p = new_p;
        }
        return bin[p][0];
    };

    //st over vals
    segment_tree st(n+1);
    fr(i,0,q) {
        ii(u); ii(v);
        u--; v--;
        ii(l); ii(r);
        if (u==v) {
            if (a[u]>=l && a[u]<=r) {
                res[i] = a[u];
            }
            continue;
        }
        if (lr[u].first>lr[v].first) swap(u,v);
        int p = lca(u,v);
        r++;
        queries[i] = {u,p,v};
        for (auto& idx : st.get_range(l,r)) {
            tags[idx].push_back(i);
        }
    }
    st.dfs(1,0,st.n,q);
    fr(i,0,q) {
        print(res[i]);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}
//sol: d&q over lr
//vals apply to points, queries apply to ranges
//for each seg, reconcile queries with relevant vals
// how to in < O(q*v)?
//buil et over only relevant vertices, each v marked at start/end
//odd iff odd marked between vertices in et
//mo's over et, keep explicit track of freq, bucket of odd freq (stack w exists/not)
//O(n*sqrtn) per layer (n == vert per layer)
//O(n*sqrtn*logn) total