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
array<int,200001> a;
array<int,200001> mi;
array<int,200001> ma;
bitset<200001> b;
bitset<200001> res;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    fr(tc,0,t) {
        ii(n); ii(q);
        int rn = a.size()-n;
        fr(i,0,n) {
            ii(x);
            a[i]=x-1; //make 0-indexed
        }
        partial_sum(a.begin(), a.begin()+n, ma.begin(), [] (int x, int y) {return max(x,y); }); //prefix max (from left)
        partial_sum(a.rbegin()+rn, a.rbegin()+rn+n, mi.rbegin()+rn, [] (int x, int y) {return min(x,y); }); //prefix min (from right)
        // print("");
        // vi test(a.begin(), a.begin()+n);
        // vi test1(ma.begin(), ma.begin()+n);
        // vi test2(mi.begin(), mi.begin()+n);
        // printv(test);
        // printv(test1);
        // printv(test2);
        si(s);
        fr(i,0,n) b[i]=s[i]=='R';
        //idx of pivot, 0/1 whether pivot is bad
        // tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> pivots;
        int totalbad = 0;
        fr(i,0,n-1) {
            if (b[i]==0 && b[i+1]==1) {
                //something at or before i needs to go beyond pivot, or something after i needs to go before pivot
                int isbad = (ma[i]>i) || (mi[i+1]<=i);
                totalbad+=isbad;
                // pivots.insert({i,isbad});
            }
        }
        // printm(pivots);
        fr(query,0,q) {
            ii(i);
            --i;
            //remove this pivot
            if (b[i]==0 && b[i+1]==1) {
                int isbad = (ma[i]>i) || (mi[i+1]<=i);
                totalbad-=isbad;
                // pivots.erase({i,isbad});
            }
            if (b[i-1]==0 && b[i]==1) {
                int isbad = (ma[i-1]>=i) || (mi[i]<i);
                totalbad-=isbad;
                // pivots.erase({i-1,isbad});
            }
            //change s[i]
            b[i] = b[i]^1;
            //insert other pivots
            if (b[i]==0 && b[i+1]==1) {
                int isbad = (ma[i]>i) || (mi[i+1]<=i);
                totalbad+=isbad;
                // pivots.insert({i,isbad});
            }
            if (b[i-1]==0 && b[i]==1) {
                int isbad = (ma[i-1]>=i) || (mi[i]<i);
                totalbad+=isbad;
                // pivots.insert({i-1,isbad});
            }
            res[query] = totalbad==0;
            // printm(pivots);
        }
        fr(rs,0,q) print(ny[res[rs]]);
        // print("");
    }
}