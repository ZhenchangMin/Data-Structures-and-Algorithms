#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
    ll x, y;
};
struct Edge {
    ll u, v;
    double cost;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<Point> dashPoints(n);
    for (int i = 0; i < n; ++i) {
        cin >> dashPoints[i].x >> dashPoints[i].y;
    }
    Point start, terminal;
    cin >> start.x >> start.y >> terminal.x >> terminal.y;
    double v1, v2;
    cin >> v1 >> v2;
    //input over
    
    int N = n + 2;
    int idxS = n, idxT = n + 1;
    vector<Point> all(N);
    for (int i = 0; i < n; ++i) all[i] = dashPoints[i];
    all[idxS] = start;
    all[idxT] = terminal;

    auto dist = [&](int a, int b) -> double {
        double dx = all[a].x - all[b].x;
        double dy = all[a].y - all[b].y;
        return hypot(dx, dy);
    };

    vector<vector<pair<int,double>>> adj(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            double d = dist(i, j);
            double time;
            if (i >= 0 && i < n) {
                double maxDashDist = v2 * 3.0;
                if (d <= maxDashDist) time = d / v2;
                else time = 3.0 + (d - maxDashDist) / v1;
            } else {
                time = d / v1;
            }
            adj[i].push_back({j, time}); // i -> j, cost = time
        }
    }

    // Dijkstra
    const double INF = 1e15;
    vector<double> distTo(N, INF);
    distTo[idxS] = 0.0;
    using P = pair<double,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0.0, idxS});
    while (!pq.empty()) {
        auto [dcur, u] = pq.top();
        pq.pop();
        if (dcur > distTo[u] + 1e-12) continue;
        if (u == idxT) break;
        for (auto &pr : adj[u]) {
            int v = pr.first;
            double w = pr.second;
            if (distTo[v] > dcur + w + 1e-12) {
                distTo[v] = dcur + w;
                pq.push({distTo[v], v});
            }
        }
    }

    cout.setf(std::ios::fixed); 
    cout << setprecision(10) << distTo[idxT] << "\n";
    return 0;
}