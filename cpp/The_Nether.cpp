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
vi a[501];

void solve(int testcase) {
    ii(n);
    vi v;
    v.reserve(n);
    fr(i,1,n+1) {
        vi().swap(a[i]);
        v.push_back(i);
    }
    pair<int,int> msf = {0,0};
    fr(i,1,n+1) {
        cout << "? " << i << " " << n << " ";
        printv(v);
        cout.flush();
        ii(m);
        a[m].push_back(i);
        msf = max(msf,make_pair(m,i));
    }
    auto [m,u] = msf;
    if (m==1) {
        cout << "! " << m << " " << u << "\n";
        cout.flush();
        return;
    }
    vi res, cur;
    int rem = n-a[m].size();
    res.reserve(m);
    res.push_back(u);
    for (int j=m-1; j>0; j--) {
        cur.swap(a[j]);
        rem-=cur.size();
        while (cur.size()>1) {
            int k = cur.size()>>1;
            vi l(cur.begin(),cur.begin()+k);
            cout << "? " << u << " " << rem+res.size()+l.size() << " ";
            fr(i,1,j) {
                for (int x : a[i]) {
                    cout << x << " ";
                }
            }
            for (int x : l) {
                cout << x << " ";
            }
            printv(res);
            cout.flush();
            ii(m1);
            if (m1==m) {
                cur.swap(l);
            } else {
                vi r(cur.begin()+k,cur.end());
                cur.swap(r);
            }
        }
        res.push_back(cur.back());
    }
    cout << "! " << res.size() << " ";
    printv(res);
    cout.flush();
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}