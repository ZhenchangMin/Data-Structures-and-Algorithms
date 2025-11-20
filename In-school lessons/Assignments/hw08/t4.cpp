#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n+1), sz(n+1,1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        p[y] = x;
        sz[x] += sz[y];
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
        DSU dsu(n);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if (u != v) dsu.unite(u, v);
        }

        long long ans = 0;
        for (int i = 2; i <= n; i++) {
            if (dsu.find(i) != dsu.find(i - 1)) {
                ans++;
                dsu.unite(i, i - 1);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
