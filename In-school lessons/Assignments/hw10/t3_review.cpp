// 修正：用“节点索引 + 邻接表”的Dijkstra，避免用坐标匹配与指针偏移求下标的问题。
#include <bits/stdc++.h>
using namespace std;

struct Point { long double x, y; };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    if(!(cin >> n)) return 0;
    vector<Point> pts(n + 2);
    for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;

    long double sx, sy, tx, ty; 
    long double V1, V2; 
    cin >> sx >> sy >> tx >> ty >> V1 >> V2;
    pts[n] = {sx, sy};
    pts[n+1] = {tx, ty};

    auto dist = [&](int i, int j){
        long double dx = pts[i].x - pts[j].x;
        long double dy = pts[i].y - pts[j].y;
        return sqrtl(dx*dx + dy*dy);
    };

    auto time_with_boost = [&](long double d){
        long double boostLen = 3.0L * V2;
        if (d <= boostLen) return d / V2; 
        return 3.0L + (d - boostLen) / V1;
    };

    int S = n, T = n+1; // 节点编号
    vector<vector<pair<int, long double>>> g(n+2);

    // 从任意“冲刺点/中间点”出发：拥有新的3秒V2；从S出发：无加速
    for (int u = 0; u < n+2; ++u){
        for (int v = 0; v < n+2; ++v){
            if (u == v) continue;
            long double d = dist(u, v);
            long double w;
            if (u == S) w = d / V1;            // 起点没有加速
            else w = time_with_boost(d); // 经过冲刺点后3秒加速
            g[u].push_back({v, w});
        }
    }

    // Dijkstra
    const long double INF = 1e100L;
    vector<long double> distance(n+2, INF); // clock time
    priority_queue<pair<long double,int>, vector<pair<long double,int>>, greater<pair<long double,int>>> pq;
    distance[S] = 0; pq.push({0, S});
    while(!pq.empty()){
        auto [t, u] = pq.top(); pq.pop();
        if (u == T) break; // already reached target, stop early
        for (auto [v, w] : g[u]){ // traverse neighbors
            if (distance[v] > t + w){
                distance[v] = t + w;
                pq.push({distance[v], v});
            }
        }
    }

    cout.setf(ios::fixed);
    cout << setprecision(10) << (double)distance[T] << "\n";
    return 0;
}