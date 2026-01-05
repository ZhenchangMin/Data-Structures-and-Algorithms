#include <iostream>
#include <vector>
#include <climits>
using namespace std;
using ll = long long;

const ll MAX_DIST = 9e18;

struct Edge {
    int from, to;
    ll profit;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    edges.reserve(m);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll val;
        cin >> u >> v >> val;
        edges.push_back({u - 1, v - 1, val});
    }
    // 统计“有破产风险的初始卡牌数”（能到达负环的起点数）
    int risky_starts = 0;
    for (int start = 0; start < n; ++start) {
        // distance[i]：从start出发到i的距离（等价于最短路）
        // 初始化为MAX_DIST，表示“从start出发无法到达i”
        vector<ll> distance(n, MAX_DIST);
        distance[start] = 0;
        bool updated;

        // 执行n-1轮Bellman-Ford
        for (int step = 0; step < n - 1; ++step) {
            updated = false;
            for (const auto& e : edges) {
                if (distance[e.from] != MAX_DIST && distance[e.from] + e.profit < distance[e.to]) {
                    distance[e.to] = distance[e.from] + e.profit;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        // 若在第n轮更新了distance，则说明存在负环
        bool has_infinite_loss = false;
        for (const auto& e : edges) {
            if (distance[e.from] != MAX_DIST && distance[e.from] + e.profit < distance[e.to]) {
                has_infinite_loss = true;
                break;
            }
        }

        // 存在负环，说明从start出发可以无限次“获得更多”（相对收益为负），risky_starts++
        if (has_infinite_loss) {
            risky_starts++;
        }
    }

    cout << risky_starts << '\n';
    return 0;
}