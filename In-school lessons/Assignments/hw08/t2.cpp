#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
using ll = long long;

struct DSU {
    vector<int> parent;
    vector<int> edge_idx;
    DSU(int n) : parent(n + 1), edge_idx(n + 1, -1) {
        for (int i = 0; i <= n; ++i)
            parent[i] = i;
    }
    pair<int, vector<int>> find(int u) {
        vector<int> path;
        while (parent[u] != u) {
            path.push_back(edge_idx[u]);
            u = parent[u];
        }
        return {u, path};
    }
    bool unite(int u, int v, int idx) {
        auto [root_u, path_u] = find(u);
        auto [root_v, path_v] = find(v);
        if (root_u == root_v)
            return false;
        parent[root_v] = root_u;
        edge_idx[root_v] = idx;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> edges(m + 1);
        for (int i = 1; i <= m; i++) {
            cin >> edges[i].first >> edges[i].second;
        }
        DSU dsu(n);
        vector<int> ans;
        bool found = false;
        for (int i = 1; i <= m; i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            auto [root_u, path_u] = dsu.find(u);
            auto [root_v, path_v] = dsu.find(v);
            if (root_u == root_v) {
                vector<int> ring = path_u;
                ring.insert(ring.end(), path_v.begin(), path_v.end());
                ring.push_back(i);
                sort(ring.begin(), ring.end());
                for (size_t j = 0; j < ring.size(); j++) {
                    if (j > 0) cout << ' ';
                    cout << ring[j];
                }
                cout << '\n';
                found = true;
                break;
            } else {
                dsu.unite(u, v, i);
            }
        }
        if (!found) {
            cout << "-1\n";
        }
    }
    return 0;
}