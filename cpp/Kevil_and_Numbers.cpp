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
ll mod = 998244353;
int b[200001];

void testcase(int t) {
    ii(n); ii(m);
    ll a_p = 0;
    ll b_p = 0;
    multiset<int> a;
    fr(i,0,n) {
        ii(x);
        a.insert(x);
        a_p+=x;
    }
    fr(i,0,m) {
        ii(x);
        b[i] = x;
        b_p+=x;
    }
    if (a_p!=b_p) {
        print("No");
        return;
    }
    sort(b,b+m,greater<int>());
    // vi test(b,b+m);
    // printv(test);
    auto check = [](auto& check, multiset<int>& a, int x) -> bool {
        if (a.contains(x)) {
            a.erase(a.find(x));
            return true;
        }
        if (x<=*a.begin()) {
            return false;
        }
        int y = x>>1;
        int z = y+(x&1);
        return check(check,a,y) && check(check,a,z);
    };
    fr(i,0,m) {
        if (!check(check, a, b[i])) {
            print("No");
            return;
        }
    }
    print(ny[a.empty()]);
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(testcases);
    fr(i,0,testcases) {
        testcase(i);
    }
}