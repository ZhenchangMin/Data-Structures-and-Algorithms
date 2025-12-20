#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct DSU{
    vector<int> parent, rank;
    DSU(int n): parent(n+1), rank(n+1){
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int a){
        return parent[a] == a ? a : parent[a] = find(parent[a]);
    }
    void unite(int a, int b){
        a = find(a); b = find(b);
        if (a == b) return;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        else rank[a] += rank[b];
    }
    bool same(int a, int b){
        return find(a) == find(b);
    }
};
struct Edge{
    int u, v;
    int w;
};
int ccOrVal(vector<vector<int>> g, vector<Edge> edges, DSU dsu, int c, map<pair<int, int>, int> weights){
    vector<Edge> ccEdges;
    vector<int> ccVertices;
    stack<int> q;
    int n = g.size();
    vector<bool> vis(n);
    q.push(c);
    ccVertices.push_back(c);
    int ans = 0;
    if (g[c].empty()) return 0;
    while(!q.empty()){
        int c = q.top();
        q.pop();
        if (g[c].empty()) continue;
        for(int v : g[c]){
            if (vis[v]) continue;
            if (v != c){
                ccVertices.push_back(v);
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (auto x : ccVertices){
        for (int v : g[x]){
            ans |= weights[{x, v}];
        }
    }
    return ans;
}
int query(vector<vector<int>> g, vector<Edge> edges, DSU dsu, map<pair<int, int>, int> weights){
    unordered_set<int> cc;
    for (Edge e : edges){
        dsu.unite(e.u, e.v);
    }
    for (int i = 1; i < g.size(); i++){
        cc.insert(dsu.find(i));
    }
    int ans = ccOrVal(g, edges, dsu, *cc.begin(), weights);
    for (int c : cc){
        ans ^= ccOrVal(g, edges, dsu, c, weights);
    }
    return ans;
}
void addEdge(int u, int v, int w, vector<vector<int>> &g, vector<Edge> &edges, DSU dsu, map<pair<int, int>, int> &weights){
    g[u].push_back(v);
    g[v].push_back(u);
    edges.push_back({u, v, w});
    weights.insert_or_assign({u, v}, w);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    vector<vector<int>> g(n+1);
    vector<Edge> edges;
    map<pair<int, int>, int> weights;
    while(q--){
        char op;
        cin >> op;
        if (op == '?'){
            cout << query(g, edges, dsu, weights) << '\n';
        }
        else{
            int u, v, w;
            cin >> u >> v >> w;
            addEdge(u, v, w, g, edges, dsu, weights);
        }
    }
    return 0;
}