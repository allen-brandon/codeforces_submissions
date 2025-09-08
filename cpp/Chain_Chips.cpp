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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_of_key()
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
ll mod = 1000000007;
ll a[524289][4]; //0: w/o both, 1: w left, 2: w right, 3: w all
ll arr[200001];
ll res[200001];

struct SegmentTree {
    int n;
    int m;
    SegmentTree(int m) {
        this -> m = m;
        n = 1;
        while (n<m) n<<=1;
        fr(i,1,n<<1) fill_n(a[i],4,0);
        fr(i,n,n+m) {
            a[i][1] = arr[i-n];
            a[i][2] = arr[i-n];
            a[i][3] = arr[i-n];
        }
        a[n][0] = inf;
        a[n][2] = inf;
        a[n+m-1][0] = inf;
        a[n+m-1][1] = inf;
        for (int i=n-1; i>0; i--) {
            modify(i);
        }
        // vll test;
        // fr(i,0,n<<1) test.push_back(a[i][3]);
        // printv(test);
        // test = {a[3][0], a[3][1], a[3][2], a[3][3]};
        // printv(test);
    }

    void modify(int i) {
        int l = i<<1, r = i<<1|1;
        // leave both
        a[i][0] = min(a[l][0] + a[r][1], a[l][2] + a[r][0]);
        //include both
        a[i][3] = min(a[l][1] + a[r][3], a[l][3] + a[r][2]);
        //include left
        a[i][1] = min(a[l][3] + a[r][0], a[l][1] + a[r][1]);
        a[i][1] = min(a[i][1], a[i][3]);
        //include right
        a[i][2] = min(a[l][0] + a[r][3], a[l][2] + a[r][2]);
        a[i][2] = min(a[i][2], a[i][3]);
    }

    void update(int i, ll x) {
        // print("updating " << i << " from " << a[i+n][3] << " to " << x);
        i+=n;
        a[i][1] = i==n+m-1? inf : x;
        a[i][2] = i==n? inf : x;
        a[i][3] = x;
        i>>=1;
        while (i!=0) {
            modify(i);
            i>>=1;
        }
        // vll test;
        // fr(i,0,n<<1) test.push_back(a[i][3]);
        // printv(test);
    }

    ll query(int l, int r) {
        // l+=n; r+=n;
        // vll lres = {0,inf,inf,inf};
        // vll rres = {0,inf,inf,inf};
        // while (l<r) {
        //     if (l&1) {
        //         lres[0] = min(lres[0] + a[l][1], lres[2] + a[l][0]);
        //         lres[1] = min(lres[3] + a[l][0], lres[1] + a[l][1]);
        //         lres[2] = min(lres[0] + a[l][3], lres[2] + a[l][2]);
        //         lres[3] = min(lres[3] + a[l][2], lres[1] + a[l][3]);
        //         l++;
        //     }
        //     if (r&1) {
        //         r--;
        //         rres[0] = min(a[r][0] + rres[1], a[r][2] + rres[0]);
        //         rres[1] = min(a[r][3] + rres[0], a[r][1] + rres[1]);
        //         rres[2] = min(a[r][0] + rres[3], a[r][2] + rres[2]);
        //         rres[3] = min(a[r][3] + rres[2], a[r][1] + rres[3]);
        //     }
        //     l>>=1;
        //     r>>=1;
        // }
        // return rres[3];
        return a[1][3];
        // return min(lres[3]+rres[2], lres[1]+rres[3]);
    }
};

void solve(int testcase) {
    ii(n);
    n--;
    fr(i,0,n) {
        lli(x);
        arr[i] = x<<1;
    }
    SegmentTree st(n);
    ii(q);
    int m = 1;
    while (m<n) m<<=1;
    fr(i,0,q) {  
        ii(k); lli(x);
        k--;
        x<<=1;
        st.update(k,x);
        res[i] = st.query(0,n);
    }
    // vll test = {a[4][3], a[5][3], a[6][3]};
    // printv(test);
    // test = {a[2][3], a[3][3]};
    // printv(test);
    // print(a[1][3]);
    fr(i,0,q) print(res[i]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}