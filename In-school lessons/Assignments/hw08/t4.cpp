#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, sz;
    DSU(int n=0){ init(n); }
    void init(int N){
        n = N;
        p.resize(n+1);
        sz.assign(n+1,1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return false;
        if(sz[a] < sz[b]) swap(a,b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin >> T)) return 0;
    while(T--){
        int n, m;
        cin >> n >> m;
        DSU dsu(n);
        for(int i=0;i<m;i++){
            int u,v;
            cin >> u >> v;
            if(u==v) continue;
            dsu.unite(u,v);
        }
        long long ans = 0;
        for(int i=2;i<=n;i++){
            if(dsu.find(i) != dsu.find(i-1)){
                ans++;
                dsu.unite(i, i-1);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
