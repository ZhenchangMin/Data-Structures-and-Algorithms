#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        parent[y] = x;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll l, r;
    cin >> l >> r;
    int n = r - l + 1;
    
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }
    
    vector<tuple<ll, int, int>> edges;
    
    for (ll d = 1; d <= r; d++) {
        ll start = ((l + d - 1) / d) * d;
        if (start > r) continue;
        
        ll u_val = start;
        ll u_idx = start - l;
        
        for (ll multiple = start + d; multiple <= r; multiple += d) {
            ll v_val = multiple;
            ll v_idx = multiple - l;
            edges.emplace_back(u_val * v_val / d, u_idx, v_idx);
        }
    }
    
    for (ll x = l + 1; x <= r; x++) {
        edges.emplace_back(l * x / __gcd(l, x), 0, x - l);
    }
    
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    ll ans = 0;
    int cnt = 0;
    
    for (auto &[w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            ans += w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    
    cout << ans << "\n";
    return 0;
}