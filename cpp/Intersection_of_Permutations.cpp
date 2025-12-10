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
int a[200001];
int b[200001];
int c[200001];
int ev[200001][5];
int res[200001];
int arr[524288];

struct SegmentTree {
    private:
    int n;
    int m;
    public:
    SegmentTree(int m) {
        this -> m = m;
        n = 1;
        while (n<m) n<<=1;
        fill_n(arr,n<<1,0);
    }
    int query(int l, int r) {
        int res = 0;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) res+=arr[l++];
            if (r&1) res+=arr[--r];
        }
        return res;
    }
    void update(int i, int x) {
        i += n;
        arr[i] += x;
        while (i>1) {
            i>>=1;
            arr[i] = arr[i<<1] + arr[i<<1|1];
        }
    }
};

void solve(int testcase) {
    ii(n); ii(m);
    vector<tuple<int,int,int>> initial;
    vector<tuple<int,int,int>> updates;
    vector<tuple<int,int,int,int,int>> queries;
    fr(i,0,n) {
        ii(x);
        a[i] = x;
        c[x] = i;
    }
    fr(i,0,n) {
        ii(x);
        b[i] = x;
        initial.emplace_back(i,c[x],1);
    }
    fr(t,0,m) {
        ii(type);
        ev[t][0] = type;
        if (type==1) {
            ii(l1); ii(r1); ii(l2); ii(r2);
            l1--; l2--;
            ev[t][1] = l1;
            ev[t][2] = r1;
            ev[t][3] = l2;
            ev[t][4] = r2;
        } else {
            ii(x); ii(y);
            x--; y--;
            ev[t][1] = x;
            ev[t][2] = y;
        }
    }
    fill_n(res,m,0);
    auto cdq = [&](int l, int r, auto& updates, auto& queries, auto& st, auto& cdq) -> void {
        // print(" ______ " << l << ", " << r << " ______ ");
        //idx, val, delta
        vector<tuple<int,int,int>> l_update, r_update;
        // x, y_l, y_r, delta, query id
        vector<tuple<int,int,int,int,int>> l_query, r_query;
        if (r==l+1) {
            if (ev[l][0]==1) {
                int l1 = ev[l][1];
                int r1 = ev[l][2];
                int l2 = ev[l][3];
                int r2 = ev[l][4];
                queries.emplace_back(l2, l1, r1, -1, l);
                queries.emplace_back(r2, l1, r1, 1, l);
                vi test = {l2-1,l1,r1,-1,l};
                vi test1 = {r2,l1,r1,1,l};
            } else {
                int x = ev[l][1], y = ev[l][2];
                updates.emplace_back(x,c[b[x]],-1);
                updates.emplace_back(y,c[b[y]],-1);
                swap(b[x], b[y]);
                updates.emplace_back(x,c[b[x]],1);
                updates.emplace_back(y,c[b[y]],1);
            }
            return;
        }
        
        //recurse
        int m = l+(r-l)/2;
        cdq(l,m,l_update,l_query,st,cdq);
        cdq(m,r,r_update,r_query,st,cdq);
        
        //could take out O(logn) if needed vvvvv
        sort(l_update.begin(),l_update.end());
        sort(r_query.begin(),r_query.end());
        //update right queries w left updates
        int update_idx = 0;
        for (auto& [x, y_l, y_r, q_delta, q_id] : r_query) {
            while (update_idx < l_update.size() && get<0>(l_update[update_idx]) < x) {
                auto& [idx, val, u_delta] = l_update[update_idx];
                st.update(val,u_delta);
                update_idx++;
            }
            res[q_id] += st.query(y_l,y_r) * q_delta;
        }
        
        //rollback segtree
        fr(undo_idx,0,update_idx) {
            auto& [_, val, delta] = l_update[undo_idx];
            st.update(val,-delta);
        }
        
        //pass updates and queries up
        updates.insert(updates.end(),l_update.begin(),l_update.end());
        updates.insert(updates.end(),r_update.begin(),r_update.end());
        queries.insert(queries.end(),l_query.begin(),l_query.end());
        queries.insert(queries.end(),r_query.begin(),r_query.end());

    };
    SegmentTree st(n);
    cdq(0,m,updates,queries,st,cdq);
    sort(queries.begin(),queries.end());
    int update_idx = 0;
    for (auto& [x, y_l, y_r, q_delta, q_id] : queries) {
        while (update_idx < initial.size() && get<0>(initial[update_idx]) < x) {
            auto& [_, val, u_delta] = initial[update_idx];
            st.update(val,u_delta);
            update_idx++;
        }
        res[q_id] += st.query(y_l,y_r) * q_delta;
    }
    fr(i,0,m) {
        if (ev[i][0] == 1) {
            print(res[i]);
        }
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(testcases);
    int testcases = 1;
    fr(testcase,1,testcases+1) solve(testcase);
}