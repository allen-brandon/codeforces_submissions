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
ll f[3001]; //firerate i
ll a[2001]; // counter of firerates
ll d[3001]; //damage i
ll p[3001]; //prooduct i
int sweep1[6002]; //change to product pop for each sweepline
int sweep2[6002]; //change to overall pop for each sweepline

void solve(int testcase) {
    ii(n); lli(k);
    fr(i,0,n) {
        lli(x);
        f[i] = x;
    }
    //all distinct firerates
    set<ll> s(f,f+n);
    //counter of firerates
    fill_n(a,(*s.rbegin())+1,0);
    fr(i,0,n) {
        lli(x);
        d[i] = x;
        p[i] = f[i]*d[i];
        a[f[i]]++;
    }
    // if (testcase!=2) return;
    // printv(s);

    //max # of firerates that don't need to be changed
    int msf = 0;
    fr(i,0,n) {
        bool valid = true; //could this window ever work
        ll start = p[i]-k; //first place in sliding window
        ll end = p[i]+k+1; //last place in sliding window
        int pop1 = 0; //pop of products
        int pop2 = 0; //pop of all
        fill_n(sweep1,(k<<2)+2,0);
        fill_n(sweep2,(k<<2)+2,0);
        //put all relevant products into sweep1
        fr(j,0,n) {
            ll x = p[j];
            if (x>=start) {
                if (x==p[i]) {
                    pop1++; //always included
                } else if (x<p[i]) {
                    pop1++; //included at first, then taken out
                    sweep1[x-start]--;
                } else if (x<end) {
                    sweep1[x-start]++; //added at some point
                }
            }
        }
        //put all possible firerates into sweep2
        for (int x : s) {
            //first mul of x >= start
            ll y = x*(((start-1)/x)+1);
            if (x<=k || y==p[i]) {
                pop2+=a[x]; //always included
                continue;
            }
            if (y<p[i]) {
                pop2+=a[x]; //included at first, then taken out
                sweep2[y-start]-=a[x];
                if (y+x<end) {
                    sweep2[y+x-start]+=a[x]; //possibly added back in after
                }
            } else if (y<end) {
                sweep2[y-start]+=a[x]; //added at some point
            } else {
                valid = false; //won't ever be included
                break;
            }
        }
        if (!valid) continue;
        fr(l,0,k+1) { //left bound (final time these elements are included)
            int r = l+k+1; //right bound (final time these elements aren't included)
            if (pop2==n) msf = max(msf, pop1);
            pop1+=sweep1[l];
            pop1+=sweep1[r];
            pop2+=sweep2[l];
            pop2+=sweep2[r];
        }
    }
    print(n-msf);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(testcase,1,testcases+1) solve(testcase);
}