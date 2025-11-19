#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<unordered_set<int>> adj(n + 1);
        
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if (u == v) continue;
            adj[u].insert(v);
            adj[v].insert(u);
        }

        long long ans = 0;
        vector<int> stk;
        vector<char> seen(n + 1, 0);

        stk.push_back(1);
        seen[1] = 1;
        for (int t = 2; t <= n; ++t) {
            if (seen[t]) continue;

            bool found = false;
            while (true) {
                int top = stk.back();
                if (adj[top].find(t) != adj[top].end()) {
                    found = true;
                    break;
                }
                if (top == 1) break;
                stk.pop_back();
            }

            if (!found) {
                ans++;
                adj[stk.back()].insert(t);
                adj[t].insert(stk.back());
            }

            stk.push_back(t);
            seen[t] = 1;
        }

        cout << ans << '\n';
    }

    return 0;
}
