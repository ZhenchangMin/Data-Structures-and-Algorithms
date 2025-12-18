#include <bits/stdc++.h>
using namespace std;
struct Edge{
    int u, v;
    long long w;
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    // Bellman-Ford algorithm to detect negative weight cycle
    vector<long long> dist(n + 1, 0);
    bool hasNegativeCycle = false;
    for (int i = 1; i <= n; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.v] > dist[edge.u] + edge.w) {
                dist[edge.v] = dist[edge.u] + edge.w;
                if (i == n) {
                    hasNegativeCycle = true;
                }
            }
        }
    }
    cout << (hasNegativeCycle ? 1 : 0) << "\n";

    return 0;
}