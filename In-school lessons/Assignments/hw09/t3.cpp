#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T;
    cin >> T;
    ll ans = 0;
    for (ll t = 1; t <= T; t++) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> board(n, vector<ll>(m));
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                cin >> board[i][j];
            }
        }

        int N = n + m;
        bool possible = true;
        vector<char> seen;
        seen.assign((size_t)N * (size_t)N, 0);

        vector<vector<int>> adj(N);
        vector<int> indeg(N, 0);

        for (int i = 0; i < n && possible; ++i) {
            for (int j = 0; j < m; ++j) {
                int val = board[i][j];
                int ri = i + 1;
                int cj = n + j + 1;

                if (val != ri && val != cj) {
                    possible = false;
                    break;
                }
                if (val == ri) {
                    int u = n + j;
                    int v = i;
                    size_t key = (size_t)u * N + v;
                    if (!seen[key]) {
                        seen[key] = 1;
                        adj[u].push_back(v);
                        indeg[v] += 1;
                    }
                } else {
                    int u = i;
                    int v = n + j;
                    size_t key = (size_t)u * N + v;
                    if (!seen[key]) {
                        seen[key] = 1;
                        adj[u].push_back(v);
                        indeg[v] += 1;
                    }
                }
            }
        }

        if (!possible) continue;
        deque<int> dq;
        for (int v = 0; v < N; ++v) {
            if (indeg[v] == 0) dq.push_back(v);
        }
        int visited = 0;
        while (!dq.empty()) {
            int u = dq.front(); dq.pop_front();
            ++visited;
            for (int v : adj[u]) {
                --indeg[v];
                if (indeg[v] == 0) dq.push_back(v);
            }
        }

        if (visited == N) {
            ans += t;
        }
    }
    cout << ans << "\n";
    return 0;
}