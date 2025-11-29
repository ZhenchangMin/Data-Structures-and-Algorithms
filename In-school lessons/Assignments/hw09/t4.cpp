#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent;
    UnionFind(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        parent[y] = x;
        return true;
    }
};

__int128 lcm128(__int128 a, __int128 b) {
    return a / gcd((long long)a, (long long)b) * b;
}

void print128(__int128 x) {
    if (x == 0) { cout << 0; return; }
    string s;
    while (x) {
        s.push_back('0' + x % 10);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long l, r;
    cin >> l >> r;

    int n = r - l + 1;
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }

    vector<tuple<__int128,int,int>> edges;
    for (int i = 0; i < n-1; ++i) {
        __int128 a = l + i;
        __int128 b = l + i + 1;
        edges.push_back({lcm128(a,b), i, i+1});
    }

    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    __int128 ans = 0;
    int cnt = 0;
    for (auto &e : edges) {
        __int128 w; int u,v;
        tie(w,u,v) = e;
        if (uf.unite(u,v)) {
            ans += w;
            cnt++;
            if (cnt == n-1) break;
        }
    }

    print128(ans);
    cout << "\n";
}
