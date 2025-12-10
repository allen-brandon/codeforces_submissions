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
int a[1001][1001];
int table[10][1001][10][1001];
struct SparseTable {
    SparseTable(int n, int m) {
        fr(i,0,n) {
            for (int l2 = 1; (1<<l2) <= m; l2++) {
                fr(j,0,m+1-(1<<l2)) {
                    int l = table[0][i][l2-1][j];
                    int r = table[0][i][l2-1][j+(1<<(l2-1))];
                    table[0][i][l2][j] = l > r ? l : r;
                }
            }
        }
        for (int l1 = 1; (1<<l1) <= n; l1++) {
            fr(i,0,n+1-(1<<l1)) {
                for (int l2 = 0; (1<<l2) <= m; l2++) {
                    fr(j,0,m+1-(1<<l2)) {
                        int l = table[l1-1][i][l2][j];
                        int r = table[l1-1][i+(1<<(l1-1))][l2][j];
                        table[l1][i][l2][j] = l > r ? l : r;
                    }
                }
            }
        }
    }

    int query(int x1, int y1, int x2, int y2) {
        int sz1 = x2-x1;
        int l1 = 0;
        while ((1<<l1) <= sz1) l1++;
        l1--;
        int sz2 = y2-y1;
        int l2 = 0;
        while ((1<<l2) <= sz2) l2++;
        l2--;
        int row1 = x1;
        int row2 = x2 - (1<<l1);
        int col1 = y1;
        int col2 = y2 - (1<<l2);
        // print(l1 << " __ " << l2);
        // print(row1 << " " << row2 << " " << col1 << " " << col2);
        int res1 = table[l1][row1][l2][col1];
        int res2 = table[l1][row1][l2][col2];
        int res3 = table[l1][row2][l2][col1];
        int res4 = table[l1][row2][l2][col2];
        // print(res1 << " " << res2 << " " << res3 << " " << res4);
        int res = max({res1,res2,res3,res4});
        // print(res);
        return res;
    }
};

void solve(int testcase) {
    ii(n); ii(m);
    fr(i,0,n) {
        fr(j,0,m) {
            ii(x);
            a[i][j] = x;
            table[0][i][0][j] = x;
        }
    }
    for (int i = n-2; i>=0; i--) {
        for (int j = m-2; j>=0; j--) {
            if (a[i][j]==0) continue;
            a[i][j] = min({a[i+1][j], a[i][j+1], a[i+1][j+1]})+1;
            table[0][i][0][j] = a[i][j];
        }
    }
    // fr(i,0,n) {
    //     vi row(a[i],a[i]+m);
    //     printv(row);
    // }
    // print("");
    SparseTable st(n, m);
    ii(t);
    vi res;
    res.reserve(t);
    auto search = [](int x1, int y1, int x2, int y2, auto& st) -> int {
        int l = 0, r = min(x2-x1, y2-y1)+1;
        while (r-l>1) {
            int th = l+(r-l)/2;
            // print("_____ " << th << " ______");
            // print(x1 << " " << y1 << " " << x2+1-th << " " << y2+1-th);
            int check = st.query(x1,y1,x2+1-th,y2+1-th);
            if (check>=th) {
                l = th;
            } else {
                r = th;
            }
        }
        return l;
    };
    fr(query,0,t) {
        ii(x1); ii(y1); ii(x2); ii(y2);
        x1--; y1--;
        // if (query != 1) continue;
        int ans = search(x1,y1,x2,y2, st);
        res.push_back(ans);
    }
    for (int& x : res) {
        print(x);
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}