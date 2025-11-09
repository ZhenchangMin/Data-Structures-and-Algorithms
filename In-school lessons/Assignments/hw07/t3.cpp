#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> fa, sz, scenic_cnt;
    DSU(int n): fa(n), sz(n, 1), scenic_cnt(n, 0) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        scenic_cnt[x] += scenic_cnt[y];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> height(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> height[i][j];

    vector<vector<int>> spot(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> spot[i][j];

    auto id = [&](int x, int y) { return x * M + y; };

    vector<array<int,3>> edges;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M) {
                    int w = abs(height[i][j] - height[ni][nj]);
                    edges.push_back({w, id(i,j), id(ni,nj)});
                }
            }
        }
    }

    sort(edges.begin(), edges.end());
    DSU dsu(N*M);

    int total_scenic = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (spot[i][j] == 1) {
                total_scenic++;
                dsu.scenic_cnt[id(i,j)] = 1;
            }

    if (total_scenic <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    int ans = 0;
    for (auto [w, u, v] : edges) {
        int ru = dsu.find(u), rv = dsu.find(v);
        if (ru != rv) {
            dsu.unite(ru, rv);
            int root = dsu.find(ru);
            if (dsu.scenic_cnt[root] == total_scenic) {
                ans = w;
                break;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
