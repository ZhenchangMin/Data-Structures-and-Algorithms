#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> fa, sz;
    DSU(int n) : fa(n+1), sz(n+1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<array<int,3>> eq, neq;
        vector<int> vals;

        for(int i = 0; i < n; i++){
            int a, b, e;
            cin >> a >> b >> e;
            vals.push_back(a);
            vals.push_back(b);
            if(e == 1) eq.push_back({a, b, e});
            else neq.push_back({a, b, e});
        }

        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        auto getId = [&](int x){
            return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
        };

        DSU dsu(vals.size());
        bool ok = true;

        for(auto [a, b, e] : eq){
            dsu.unite(getId(a), getId(b));
        }

        for(auto [a, b, e] : neq){
            if(dsu.same(getId(a), getId(b))){
                ok = false;
                break;
            }
        }
        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
