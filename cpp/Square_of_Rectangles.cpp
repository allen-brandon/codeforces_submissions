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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_by_key()
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
ll mod = 998244353;

bool solve(int x1, int y1, int x2, int y2, int x3, int y3) {
    if (x1+x2+x3 == y1 && y1==y2 && y2==y3) return true; //horizontal stack
    if (y1+y2+y3 == x1 && x1==x2 && x2==x3) return true; //vertical stack
    vector<pair<int,int>> a = {{x1,y1},{x2,y2},{x3,y3}};
    fr(i,0,3) {
        fr(j,0,3) {
            if (i==j) continue;
            fr(k,0,3) {
                if (i==k || j==k) continue;
                auto [h1,w1] = a[i];
                auto [h2,w2] = a[j];
                auto [h3,w3] = a[k];
                if (h1 == h2+h3 && w2==w3 && h1==w1+w2) return true;
                if (w1 == w2+w3 && h2==h3 && w1==h1+h2) return true;
            }
        }
    }
    return false;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    vi res;
    fr(testcase,0,t) {
        ii(x1); ii(y1); ii(x2); ii(y2); ii(x3); ii(y3);
        res.push_back(solve(x1,y1,x2,y2,x3,y3));
    }
    for (auto x : res) {
        print(ny[x]);
    }
}