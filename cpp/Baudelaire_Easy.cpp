#ifdef DEBUG
#include <cstdio>
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#define USE_INPUT_FILE(file)
#endif

using namespace std;
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ll long long
#define ull unsigned ll
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define print(_) cout << _ << "\n";
#define printv(_) for (const auto& x : _) cout << x << ' '; cout << '\n';
#define printum(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
ll inf = 151515151515151;
ll mod = 998244353;
array<string,2> ny = {"No","Yes"};
array<int,1001> res;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    for (int test_case=0; test_case<t; ++test_case) {
        ii(n);
        for (int i=0; i<n-1; ++i) {
            ii(u);
            ii(v);
        }
        int root = 1;
        cout << "? 1 1 1" << "\n";
        cout.flush();
        ii(x);
        if (x%2==0) {
            int pop = 1;
            while (pop<n) pop<<=1;
            pop>>=1;
            while (pop!=0) {
                int cur_pop = min(pop, n+1-root);
                cout << "? 1 " << cur_pop;
                for (int i=root; i<root+cur_pop; ++i) {
                    cout << " " << i;
                }
                cout << "\n";
                cout.flush();
                ii(x);
                cout << "? 2 1" << "\n";
                cout.flush();
                cout << "? 1 " << cur_pop;
                for (int i=root; i<root+cur_pop; ++i) {
                    cout << " " << i;
                }
                cout << "\n";
                cout.flush();
                ii(y);
                int dx = abs(y-x);
                if (dx==cur_pop*2) root+=pop;
                pop>>=1;
            }
        }
        cout << "? 1 1 " << root << "\n";
        cout.flush();
        ii(y);
        res[root] = y;
        cout << "? 1 1 1 " << "\n";
        cout.flush();
        ii(pref);
        res[1] = root==1?pref:pref-y;
        for (int i=2; i<=n; ++i) {
            if (i==root) continue;
            cout << "? 1 1 " << i << "\n";
            cout.flush();
            ii(x);
            res[i]=x-pref;
        }
        cout << "!" << " ";
        vi v(res.begin()+1, res.begin()+n+1);
        printv(v);
        cout.flush();
    }
}