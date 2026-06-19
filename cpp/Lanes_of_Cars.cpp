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
ll a[200001];
ll b[200001];
ll pref[200001];
ll pref1[200001];

void solve(int testcase) {
    lli(n); lli(k);
    fr(i,0,n) {
        lli(x);
        a[i] = x;
    }
    // if (testcase!=2) return;
    if (n==1) {
        print(a[0]*(a[0]+1)/2ll);
        return;
    }
    sort(a,a+n);
    fr(i,0,n) b[i] = a[i]*(a[i]+1ll)/2ll;
    partial_sum(a,a+n,pref);
    partial_sum(b,b+n,pref1);
    // vll test1(a,a+n);
    // printv(test1);
    // vll test2(b,b+n);
    // printv(test2);
    // vll test3(pref,pref+n);
    // printv(test3);
    // vll test4(pref1,pref1+n);
    // printv(test4);
    // print("________");
    ll res = pref1[n-1];
    int l = 1, r = n-1;
    for (ll lim = a[n-1]; r>=l-1; lim--) {
        //lower everything above r to lim
        while (r>=0 && a[r]>lim) r--;
        ll rpop = (pref[n-1] - pref[r]) - lim*(n-1-r);
        //fill lowest elements up to a[l] (exc)
        ll lpop = l*a[l]-pref[l-1];
        while (l<n && lpop<rpop) {
            l++;
            lpop = l*a[l]-pref[l-1];
        }
        if (r<l-1) break;
        //how much left side is filled to
        ll fill = (pref[l-1]+rpop)/l;
        ll extra = (pref[l-1]+rpop)%l;
        //cost to move
        ll cost = rpop*k;
        cost += (l-extra)*fill*(fill+1)/2; //left cost (lower)
        cost += extra*(fill+1)*(fill+2)/2; //left cost (upper)
        cost += pref1[r] - pref1[l-1]; //mid cost (inc l, inc r)
        cost += (n-1-r)*lim*(lim+1)/2; //right cost (exc r)
        res = min(res, cost);
        if (fill>lim-k) { //filled too far
            //retrace all from r+1 to n
            fr (rb,r+1,n) {
                rpop--;
                extra--;
                cost -= k + fill+1;//no more move or on l
                if (extra<0) {
                    //took away fill, not fill+1 above
                    cost++;
                    fill--;
                    //dont fill up to l anymore
                    if (fill<a[l-1]) l--;
                    extra = l-1;
                }
                cost += lim+1;//put back that spot
                res = min(res, cost);
            }
            break;
        }
    }
    print(res);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    // USE_OUTPUT_FILE("_output.txt");
    // mt19937 rng(1);
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}