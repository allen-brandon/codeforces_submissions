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
const int nlim = 524288;
vi a[nlim]; //initial left bound
pair<ll,ll> b[nlim]; //modulus buffer when segtree is flushed (sum, count)
ll res[nlim];
pair<int,int> queries[nlim];

struct segtree {
    private:
    int n; //size of tree
    int k; //size of bucket
    public:
    segtree(int m, int k) : k(k) {
        n = 1<<(32-__builtin_clz(m-1));
        fill_n(a,n*2,vi());
        n /= k; //can probably put above fill_n
    }
    
    //add to range l,r
    void update(int l, int r) {
        int i = l, j = r;
        // print("l: " << l << ", r: " << r);
        l /= k;
        //include right bound only if extends past i in that bucket
        // print(((i+k-1)%k)+k*(r/k));
        if (((i+k-1)%k)+k*(r/k)<r) {
            // print("rounding up");
            r = (r+k-1)/k;
        } else {
            // print("rounding down");
            // print((i%k)+(r/k) << " " << r);
            r /= k;
        }
        // print("l: " << l << ", r: " << r);
        for (l+=n,r+=n; l<r; l>>=1,r>>=1) {
            // print(l << " " << r);
            if (l&1) {
                a[l++].push_back(i);
                // print("attached l: " << l);
            }
            if (r&1) {
                a[--r].push_back(i);
                // print("attached r: " << r);
            }
        }
    }

    //dfs and add to result 
    void parse() {
        fill_n(b,k,pair<ll,ll>({0,0}));
        //vertex, subtree size, subtree offset, direction
        stack<tuple<int,int,int,int>> st;
        st.emplace(1,n,0,1);
        while (!st.empty()) {
            auto [u,sz,os,d] = st.top();
            st.pop();
            if (d==0) {
                //remove interval tags
                for (int i : a[u]) {
                    b[(i+k-1)%k] = {b[(i+k-1)%k].first-(os-i), b[(i+k-1)%k].second-1};
                }
                //remove previous offset
                if (u&1) {
                    fr(i,0,k) b[i] = {b[i].first-b[i].second*sz*k, b[i].second};
                }
                continue;
            }
            st.emplace(u,sz,os,0);
            //add previous offset
            if (u&1) {
                fr(i,0,k) b[i] = {b[i].first+b[i].second*sz*k, b[i].second};
            }
            //add interval tags
            for (int i : a[u]) {
                b[(i+k-1)%k] = {b[(i+k-1)%k].first+(os-i), b[(i+k-1)%k].second+1};
            }
            //add values if leaf node (bucket of indices)
            if (u>=n) {
                int bucket = (u-n)*k;
                fr(i,0,k) {
                    res[bucket+i] += max(1,k>>1) * (b[i].first+b[i].second*(i+1));
                }
                continue;
            }
            st.emplace(u<<1|1,sz>>1,os+(sz>>1)*k,1); //offset corrected inside r function
            st.emplace(u<<1,sz>>1,os,1);
        }
    }
};

void solve(int testcase) {
    ii(n); ii(q);
    fill_n(res,n,0);
    //input/sort queries
    fr(i,0,q) {
        ii(l); ii(r);
        queries[i] = {--l,r};
    }
    sort(queries,queries+q,[](auto lr1, auto lr2) { return lr1.second-lr1.first > lr2.second-lr2.first; });
    queries[q] = {0,0};
    int qlim = queries[0].second-queries[0].first;
    // if (testcase!=2) return;
    //input each lsb
    fr(j,0,20) {
        // if (j!=0) continue;
        int k = 1<<j;
        auto st = segtree(n,k);
        if (qlim<k) break;
        for (auto [l,r] : queries) {
            // if (l!=0 || r!=3) continue;
            int sz = r-l;
            if (sz<k) break;
            // continue;
            st.update(l,r);
            // break;
        }
        st.parse();
        // print("");
        // print("k: " << k);
        // vll to_print(res,res+n);
        // printv(to_print);
        // print("____________");
        // fill_n(res,n,0);
        // break;
    }
    vll to_print(res,res+n);
    printv(to_print);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}