#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define fi first
#define se second

const int MAXN = 5e5 + 5;

int n,m;
vector<int> adj[MAXN];

string s;

vector<pair<int,int>> query[MAXN];

int pref[MAXN];
int b[MAXN];
bool ans[MAXN];

void dfs(int u,int depth)
{
    for(auto x : query[u])
    {
        int h = x.fi;
        int id = x.se;
        b[id] = pref[h];
    }
    pref[depth] ^= (1 << (s[u-1]-'a'));
    for(auto v : adj[u])
    {
        dfs(v,depth+1);
    }
    for(auto x : query[u])
    {
        int h = x.fi;
        int id = x.se;
        int mask = pref[h] ^ b[id];
        ans[id] = ((mask & (mask-1)) == 0);
    }
}

void read()
{
    cin >> n >> m;
    for(int i=2;i<=n;i++)
    {
        int p;
        cin >> p;

        adj[p].pb(i);
    }
    cin >> s;
    for(int i=0;i<m;i++)
    {
        int v,h;
        cin >> v >> h;

        query[v].pb({h,i});
    }
}

void solve()
{
    dfs(1,1);

    for(int i=0;i<m;i++)
    {
        if(ans[i]) cout << "Yes\n";
        else cout << "No\n";
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read();
    solve();
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <bits/stdc++.h>
// using namespace std;

// #define int long long
// #define pb push_back
// #define fi first
// #define se second

// const int MAXN = 5e5 + 5;

// int n,m;

// vector<int> adj[MAXN];

// string s;

// int tin[MAXN],tout[MAXN];
// int depth[MAXN];
// int timer = 0;

// vector<int> pos[MAXN];
// vector<int> pref[MAXN];

// void dfs(int u,int d)
// {
//     depth[u] = d;

//     tin[u] = ++timer;

//     pos[d].pb(tin[u]);

//     int mask = (1LL << (s[u-1]-'a'));

//     if(pref[d].empty())
//         pref[d].pb(mask);
//     else
//         pref[d].pb(pref[d].back() ^ mask);

//     for(auto v : adj[u])
//     {
//         dfs(v,d+1);
//     }

//     tout[u] = timer;
// }

// int getxor(int d,int l,int r)
// {
//     if(l > r) return 0;

//     int res = pref[d][r];

//     if(l) res ^= pref[d][l-1];

//     return res;
// }

// void read()
// {
//     cin >> n >> m;

//     for(int i=2;i<=n;i++)
//     {
//         int p;
//         cin >> p;

//         adj[p].pb(i);
//     }

//     cin >> s;
// }

// void solve()
// {
//     dfs(1,1);

//     for(int i=0;i<m;i++)
//     {
//         int v,h;
//         cin >> v >> h;

//         int L = lower_bound(pos[h].begin(),pos[h].end(),tin[v]) - pos[h].begin();

//         int R = upper_bound(pos[h].begin(),pos[h].end(),tout[v]) - pos[h].begin() - 1;

//         int mask = getxor(h,L,R);

//         if((mask & (mask-1)) == 0)
//             cout << "Yes\n";
//         else
//             cout << "No\n";
//     }
// }

// signed main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     read();
//     solve();
// }