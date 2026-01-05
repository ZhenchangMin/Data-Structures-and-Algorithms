#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int getMinUnvisitedNeighbor(int u, const vector<vector<int>> &adj, const vector<bool> &discovered, int n) {
    int ans = n + 1;
    for (int x : adj[u]) {
        if (!discovered[x] && x < ans) {
            ans = x;
        }
    }
    return ans;
}

void removeDuplicates(vector<int>& v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

void readGraph(int m, vector<vector<int>>& adj) {
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        vector<bool> discovered(n + 1, false);
        vector<int> stk;
        int crt = 1;
        int ans = 0;

        readGraph(m, adj);
        // input over

        for (int i = 1; i <= n; i++) removeDuplicates(adj[i]);

        stk.push_back(1);
        discovered[1] = true;
        crt++;

        while (crt <= n) {
            if (stk.empty()) {
                ans++;
                discovered[crt] = true;
                stk.push_back(crt);
                crt++;
            }else{
                int u = stk.back();
                int minNeighbor = getMinUnvisitedNeighbor(u, adj, discovered, n);

                if (minNeighbor == n + 1) {
                    stk.pop_back();
                    continue;
                } else {
                    if (minNeighbor > crt) {
                        ans++;
                        discovered[crt] = true;
                        stk.push_back(crt);
                        crt++;
                    } else if (minNeighbor == crt) {
                        discovered[crt] = true;
                        stk.push_back(crt);
                        crt++;
                    } else if (minNeighbor < crt) {
                        int it = find(adj[u].begin(), adj[u].end(), minNeighbor) - adj[u].begin();
                        if (it != adj[u].size()) {
                            adj[u].erase(adj[u].begin() + it);
                        }
                    }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}