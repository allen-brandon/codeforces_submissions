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
array<string,2> ny = {"NO","YES"};
ll inf = 151515151515151;
ll mod = 1000000007;

void check(int n, int l, int r, vector<tuple<int,int,int>> res) {
    vector<int> tp; //to print
    map<int,vector<pair<int,int>>> adj;
    for (auto [u,v,w] : res) {
        if (u<=0) u = n+u;
        if (v<=0) v = n+v;
        adj[u].emplace_back(v,w);
    }
    auto dfs = [&](int u, int x, auto& dfs) {
        if (u==n) {
            tp.push_back(x);
            return;
        }
        for (auto [v,w] : adj[u]) {
            dfs(v,x+w,dfs);
        }
    };
    dfs(1,0,dfs);
    sort(tp.begin(),tp.end());
    vi compare(r+1-l);
    iota(compare.begin(),compare.end(), l);
    // print("___");
    // string ans = tp==compare && compare.back()==r? "right" : "wrong";
    // print(ans);
    // printv(tp);
    // printv(compare);
}

void solve(int testcase) {
    ii(l); ii(r);
    vector<tuple<int,int,int>> res;
    //1,5
    //2,5
    //2,3,4,5
    //1,2,3,4
    //construct hsb==1
    //1,o,w2,w1,n
    //1->all (1,2,3,4)
    //o->w1(3) (5)
    //w2->w1,n(2)
    //w1->n
    auto construct = [&](int hsb, int n) {
        fr(i,0,hsb+1) {
            int w = 1<<i;
            int u = -1-i;
            res.emplace_back(1,u,l);
            //connect to later vertices
            fr(v,u+1,1) {
                res.emplace_back(u,v,w);
            }
        }
        //return new n
        return n+hsb;
    };

    //cornercase to give enough buffer if l==1
    int n = 2;
    res.emplace_back(1,0,l);
    if (l==r) {
        print(ny[1]);
        print(n << " " << res.size());
        for (auto [u,v,w] : res) {
            //x<=0 means back indexed
            if (u<=0) u = n+u;
            if (v<=0) v = n+v;
            print(u << " " << v << " " << w);
        }
        return;
    }
    int dx = r-l; //already accounted for l itself
    int hsb = 31-__builtin_clz(dx+1)-1; //highest usable set bit (<=dx)
    int x = 1<<hsb;
    //offset vertex
    res.emplace_back(1,2,l);
    n++;
    n += construct(hsb,n);
    // connect offset to grid
    //return to initial dx for offset purposes
    dx++;
    hsb = 31-__builtin_clz(dx);
    int offs = (1<<hsb);
    for (int i = hsb-1; i>=0; i--) {
        if ((1<<i)&dx) {
            //e.g. (4,5,6,7) -> (0,1,2,3)
            int w = offs-(1<<i);
            res.emplace_back(2,-1-i,w);
            offs+=1<<i;
        }
    }
    if (n>32) {
        print(ny[0]);
        return;
    }
    print(ny[1]);
    print(n << " " << res.size());
    for (auto [u,v,w] : res) {
        //down from n if neg
        if (u<=0) u = n+u;
        if (v<=0) v = n+v;
        print(u << " " << v << " " << w);
    }
    // check(n,l,r,res);
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

//100101
//1-100000... from construct
//100 (1,2,3,4,5) + b(100000)
//connect 2->n-3
//n-3->n,n-3->n-2->n,n-3->n-2->n-1->n,n-3->n-1->n
//4 paths total
//n-1->n
//1 path total
//go backwards largest set bit -> smallest