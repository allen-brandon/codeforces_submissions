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
#define print(_) cout << _ << "\n";
#define printv(_) for (const auto& x : _) cout << x << ' '; cout << '\n';
#define printm(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
array<pair<int,int>,4> didj = {{{-1,0},{0,1},{1,0},{0,-1}}};
array<string,2> ny = {"No","Yes"};
int inf = 1000000001;
ll mod = 998244353;
array<pair<int,int>,300001> b;
array<tuple<int,int,int>,300001> queries;
array<map<int,set<int>>,300001> e; //for i, for requirement x, what others required this?

bool set_to(int i, int x) {
    auto [is,iv] = b[i];
    if (is==0) return iv==x; //it's already something (possibly x)
    if (iv>x) return false; //it needed to be greater than x
    b[i] = {0,x};
    auto m = e[i];
    //all that needed i to be x are relieved
    for (auto j : e[i][x]) {
        e[j][x].erase(i);
    }
    m.erase(x);
    //all that needed i to be something else must be set
    for (auto [y,y_set] : m) {
        for (auto j : y_set) {
            if (set_to(j,y)==0) return false;
        }
    }
    e[i] = map<int,set<int>>();
    return true;
}

bool set_greater(int i, int x) {
    auto [is,iv] = b[i];
    if (is==0) return iv>=x;
    if (is==1 && iv>=x) return true;
    b[i] = {1,x};
    auto m = e[i];
    while (m.size() != 0) {
        auto [y,y_set] = *m.begin();
        if (y>=x) break;
        for (auto j : y_set) {
            if (set_to(j,y)==0) return false;
        }
        m.erase(y);
    }
    return true;
}

void solve(int n, int q) {
    for (int i=0; i<q; ++i) {
        auto [x,y,z] = queries[i];
        print(x << " " << y << " " << z);
        for (int i=0; i<n; ++i) {
            auto [xs,xv] = b[i];
            cout << xs << (xs==1? max(xv,0) : xv) << " ";
        }
        cout << "\n";
        print("");
        // INCOMPLETE
        auto [xs,xv] = b[x];
        auto [ys,yv] = b[y];
        auto [zs,zv] = b[z];
        //if separate, z can be anything now
        if (z!=x && z!=y) b[z] = {1,0};
        
        //one must be exactly zv
        //one of them already needed to be something
        if (xs==0) {
            if (xv==zv) {
                if (set_greater(y,zv)==0) {
                    print("-1");
                    return;
                }
                continue;
            } else if (set_to(y,zv)==0) {
                print("-1");
                return;
            }
            continue;
        }
        if (ys==0) {
            if (yv==zv) {
                if (set_greater(x,zv)==0) {
                    print("-1");
                    return;
                }
                continue;
            } else if (set_to(x,zv)==0) {
                print("-1");
                return;
            }
            continue;
        }
        
        // one of them needed to be greater than zv
        if (xv>zv) {
            if (set_to(y,zv)==0) {
                print("-1");
                return;
            }
            continue;
        }
        if (yv>zv) {
            if (set_to(x,zv)==0) {
                print("-1");
                return;
            }
            continue;
        }

        //both must be >=zv, one must be zv
        if (set_greater(x,zv)==0) {
            print("-1");
            return;
        }
        if (set_greater(y,zv)==0) {
            print("-1");
            return;
        }
        e[y][zv].insert(x);
        e[x][zv].insert(y);
    }
    print("");
    for (int i=0; i<n; ++i) {
        auto [xs,xv] = b[i];
        cout << (xs==1? max(xv,0) : xv) << " ";
    }
    cout << "\n";
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    for (int t=0; t<testcases; ++t) {
        ii(n); ii(q);
        for (int i=0; i<n; ++i) {
            ii(x);
            b[i] = {0,x};
        }
        for (int i=0; i<q; ++i) {
            ii(x); ii(y); ii(z);
            queries[i] = {x-1,y-1,z-1};
        }
        reverse(queries.begin(), queries.begin()+q);
        solve(n,q);
    }
}