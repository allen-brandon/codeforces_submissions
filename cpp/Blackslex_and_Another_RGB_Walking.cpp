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
map<char,char> nxt = {{'r','g'},{'g','b'},{'b','r'}};
map<char,char> prv = {{'r','b'},{'b','g'},{'g','r'}};
ll inf = 151515151515151;
int mod = 1000000007;

vi adj[100001];
char res[100001];
bitset<100001> seen;

void query_1(int testcase) {
    ii(n); ii(m);
    fill_n(adj,n+1,vi());
    fr(i,0,n) seen[i] = 0;
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    seen[0] = 1;
    queue<pair<int,char>> q;
    q.emplace(0,'r');
    while (!q.empty()) {
        auto [u,c] = q.front();
        q.pop();
        res[u] = c;
        for (int v : adj[u]) {
            if (seen[v]) continue;
            q.emplace(v,nxt[c]);
            seen[v] = 1;
        }
    }
    string s(res,res+n);
    print(s);
};

void query_2(int testcase) {
    ii(q);
    vi res1;
    res1.reserve(q);
    fr(i,0,q) {
        ii(n);
        si(s);
        int r=0, g=0, b=0;
        fr(j,0,n) {
            if (s[j]=='r') r=1;
            if (s[j]=='g') g=1;
            if (s[j]=='b') b=1;
        }
        if (r+g+b<2) {
            if (r==1) {
                res1.push_back(1);
                continue;
            }
        }
        char slf = r==0? 'r' : (b==0? 'b' : 'g');
        char bst = prv[slf];
        int works = 0;
        fr(j,0,n) {
            if (s[j]==bst) {
                res1.push_back(j+1);
                works = 1;
                break;
            }
        }
        if (works==0) {
            res1.push_back(1);
        }
    }
    for (int x : res1) {
        print(x);
    }
};

void solve(int testcase) {
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    si(type);
    if (type=="first") {
        ii(testcases);
        fr(testcase,1,testcases+1) query_1(testcase);
    } else {
        ii(testcases);
        fr(testcase,1,testcases+1) query_2(testcase);
    }
}