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
int a[200001][2];
int cycle[500][500];
array<vector<pair<int,int>>,200001> intervals; 
//for each large num, {start,end} for all intervals
int res[200001];
int prv[200001];
int c[200001];

void testcase() {
    ii(n); ii(m);
    int srt = sqrt(m)+1;
    int ma = 0;

    fill_n(res,m+1,0);
    fill_n(c,n+1,0);
    fill_n(intervals.begin(),n+1,vector<pair<int,int>>());
    fr(i,1,srt) fill_n(cycle[i],i,0);

    fr(i,1,n+1) {
        ii(x); ii(y);
        a[i][0]=x;
        a[i][1]=y;
    }
    vi touched_small;
    vi touched_large;
    fr(i,0,m) {
        fr(j,1,srt) {
            res[i]+=cycle[j][i%j];
        }
        ii(op); ii(k);
        auto [x,y] = a[k];
        int sz = x+y;
        if (op==1) {
            if (sz<srt) {
                ++cycle[sz][(i+x)%sz];
                --cycle[sz][i%sz];
                prv[k] = i;
            } else {
                if (intervals[k].empty()) touched_large.push_back(k);
                intervals[k].emplace_back(i,m);
            }
        } else {
            if (sz<srt) {
                int j = prv[k];
                --cycle[sz][(j+x)%sz];
                ++cycle[sz][j%sz];
                res[i]-=((i-j)%sz)>=x;
            } else {
                auto [l,r] = intervals[k].back();
                intervals[k].back() = {l,i};
            }
        }
    }
    for (auto k : touched_large) {
        for (auto [l,r] : intervals[k]) {
            auto [x,y] = a[k];
            int i = l+x;
            while (i<r) {
                ++res[i];
                i+=y;
                if (i>=r) {
                    --res[r];
                    break;
                }
                --res[i];
                i+=x;
                if (i>=r) break;
            }
        }
        intervals[k].clear();
    }
    // vi test(res,res+m);
    // printv(test);
    int cur = 0;
    fr(i,0,m) {
        cur+=res[i];
        print(cur);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    int t = 1;
    while (t--) testcase();
}