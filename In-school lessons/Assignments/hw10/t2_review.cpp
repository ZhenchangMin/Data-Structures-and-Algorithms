
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges;
    edges.reserve(m);
    vector<vector<int>> rev(n + 1); // reverse graph to see which nodes can reach negative cycles
    for (int i = 0; i < m; ++i) {
        int u, v; ll w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        rev[v].push_back(u); // reverse graph for later reachability
    }

    // Bellman-Ford with super source: initialize all dist = 0
    const ll INF = (1LL << 60);
    vector<ll> dist(n + 1, 0);
    vector<int> pre(n + 1, -1); // predecessor array for cycle detection
    vector<int> negDetect; negDetect.reserve(n);

    // Relax edges up to n times to detect negative cycles
    for (int i = 1; i <= n; ++i) {
        bool any = false;
        for (const auto &e : edges) {
            if (dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                pre[e.v] = e.u;
                any = true;
                if (i == n) negDetect.push_back(e.v);
            }
        }
        if (!any) break; // no updates, can stop early
    }

    if (negDetect.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    // Find actual nodes on negative cycles
    vector<int> in_cycle_nodes;
    vector<char> in_cycle(n + 1, 0);
    for (int v : negDetect) {
        int x = v;
        for (int i = 0; i < n; ++i) {
            if (pre[x] == -1) break; // safety
            x = pre[x];
        }
        if (!in_cycle[x]) {
            in_cycle[x] = 1;
            in_cycle_nodes.push_back(x);
        }
    }

    // Multi-source BFS/DFS on reverse graph from cycle nodes to find
    // all nodes that can reach any negative cycle in the original graph.
    queue<int> q;
    vector<char> vis(n + 1, 0);
    // Initialize queue with all nodes already in negative cycles
    for (int s : in_cycle_nodes) {
        if (!vis[s]) { vis[s] = 1; q.push(s); }
    }
    // BFS/DFS
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int p : rev[u]) {
            if (!vis[p]) { vis[p] = 1; q.push(p); }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) if (vis[i]) ++ans;
    cout << ans << '\n';
    return 0;
}