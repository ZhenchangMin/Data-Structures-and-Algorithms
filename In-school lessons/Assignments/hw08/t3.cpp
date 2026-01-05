#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;
using ll = long long;


const int MAXN = 300001;

int n, m;

vector<int> Graph[MAXN];
int dfn[MAXN], low[MAXN], timer;
int U[MAXN*2], V[MAXN*2];
stack<int> edgeStack;

ll modpow(ll a, ll b, int mod = 998244353) {
    if (b == 0) return 1;
    ll r = modpow(a, b / 2);
    r = r * r % mod;
    if (b % 2) r = r * a % mod;
    return r;
}


void execute(int u, int pe, vector<vector<int>>& edgeComps) {
    dfn[u] = low[u] = timer++;

    for (int eid : Graph[u]) {
        int v = U[eid] ^ V[eid] ^ u;

        if (!dfn[v]) {
            edgeStack.push(eid);
            execute(v, eid, edgeComps);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                vector<int> compEdges;
                int cur;
                do {
                    cur = edgeStack.top();
                    edgeStack.pop();
                    compEdges.push_back(cur);
                } while (cur != eid);
                edgeComps.emplace_back(move(compEdges));
            }
        } 
        else if (eid != pe && dfn[v] < dfn[u]) {
            edgeStack.push(eid);
            low[u] = min(low[u], dfn[v]);
        }
    }
}


inline void readIn(int i){
    int u, v;
    cin >> u >> v;
    U[i] = u; V[i] = v;
    Graph[u].push_back(i);
    Graph[v].push_back(i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MOD = 998244353;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        readIn(i);
    }

    vector<vector<int>> c_edge;

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            execute(i, -1, c_edge);
        }
    }

    ll ans = 1;

    for (size_t i = 0; i < c_edge.size(); i++) {
        const auto &c = c_edge[i];
        int edges = c.size();

        vector<int> nodes;
        nodes.reserve(edges * 2);
        for (int e : c) {
            nodes.push_back(U[e]);
            nodes.push_back(V[e]);
        }
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        int verts = nodes.size();

        ll add = modpow(2, edges);
        if (edges == verts) add = (add - 1 + MOD) % MOD;
        ans = ans * add % MOD;
    }

    cout << ans % MOD << "\n";

    return 0;
}