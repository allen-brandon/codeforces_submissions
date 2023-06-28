#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Edge {
    int weight;
    int node;

    Edge(int w, int n) : weight(w), node(n) {}
};

struct Compare {
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};

vector<int> root;
vector<int> sze;
unordered_map<int, priority_queue<Edge, vector<Edge>, Compare> > heaps;

int find(int a) {
    while (root[root[a]] != root[a]) {
        root[a] = root[root[a]];
    }
    return root[a];
}

void unionSet(int a, int b) {
    sze[a] += sze[b];
    root[b] = a;
}

void merge(int a, int b, vector<int>& vals, vector<vector<int> >& adj, priority_queue<Edge, vector<Edge>, Compare>& larger) {
    priority_queue<Edge, vector<Edge>, Compare> smaller;
    if (heaps.count(a)) {
        smaller = heaps[a];
    } else {
        for (int x : adj[a]) {
            smaller.push(Edge(vals[x], x));
        }
    }
    while (!smaller.empty()) {
        if (find(smaller.top().node) != find(b)) {
            larger.push(smaller.top());
        }
        smaller.pop();
    }
}

void solve(int n, int m, vector<int>& vals, vector<vector<int> >& adj) {
    root.resize(n);
    sze.resize(n);
    heaps.clear();
    for (int i = 0; i < n; i++) {
        root[i] = i;
        sze[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (vals[i] || root[i] != i) continue;
        priority_queue<Edge, vector<Edge>, Compare> h;
        for (int v : adj[i]) {
            h.push(Edge(vals[v], v));
        }
        heaps[i] = h;
        while (!h.empty() && h.top().weight <= sze[i]) {
            int node = find(h.top().node);
            h.pop();
            if (node == i) continue;
            merge(node, i, vals, adj, h);
            unionSet(i, node);
        }
    }
    auto maxElement = max_element(sze.begin(), sze.end());
    std::cout << (*maxElement == n ? "Yes" : "No") << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> vals(n);
        for (int i = 0; i < n; i++) {
            cin >> vals[i];
        }
        vector<vector<int> > adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }
        solve(n, m, vals, adj);
    }
    return 0;
}