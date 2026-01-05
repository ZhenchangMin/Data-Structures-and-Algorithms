#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 100005;

int n, m;
vector<pair<int, int>> adj[MAXN];
int parent[MAXN];
int dist[MAXN];
bool vis[MAXN];

int dsu[MAXN];
int find(int x) {
    return dsu[x] == x ? x : (dsu[x] = find(dsu[x]));
}
bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    dsu[x] = y;
    return true;
}

vector<int> bfs_path(int start, int end) {
    queue<int> q;
    q.push(start);
    memset(vis, 0, sizeof(vis));
    memset(parent, -1, sizeof(parent));
    vis[start] = true;
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == end) break;
        for (auto& e : adj[u]) {
            int v = e.first, idx = e.second;
            if (!vis[v]) {
                vis[v] = true;
                parent[v] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    vector<int> edges;
    int cur = end;
    while (parent[cur] != -1) {
        int p = parent[cur];
        for (auto& e : adj[cur]) {
            if (e.first == p) {
                edges.push_back(e.second);
                break;
            }
        }
        cur = p;
    }
    return edges;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        dsu[i] = i;
    }
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }

    int best_max_idx = m + 1;
    vector<int> best_cycle;
    bool found = false;

    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        if (find(u) == find(v)) {
            vector<int> cycle_edges = bfs_path(u, v);
            cycle_edges.push_back(i + 1);
            best_max_idx = i + 1;
            best_cycle = cycle_edges;
            found = true;
            break;
        } else {
            unite(u, v);
            adj[u].push_back({v, i + 1});
            adj[v].push_back({u, i + 1});
        }
    }

    if (!found) {
        cout << -1 << "\n";
    } else {
        sort(best_cycle.begin(), best_cycle.end());
        for (size_t i = 0; i < best_cycle.size(); i++) {
            if (i > 0) cout << " ";
            cout << best_cycle[i];
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}