#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
using ll = long long;
struct DSU{
    vector<int> parent, descendent;
    DSU(int n) : parent(n+1), descendent(n+1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find_parent(int a){
        if (parent[a] == a) return a;
        else{
            parent[a] = find_parent(parent[a]);
            return parent[a];
        }
    }
    bool unite(int a, int b){
        int A = find_parent(a);
        int B = find_parent(b);
        if (A == B) return true;
        else{
            if (descendent[A] <= descendent[B]){
                parent[A] = B;
                descendent[B] += descendent[A];
            }
            else{
                parent[B] = A;
                descendent[A] += descendent[B];
            }
            return false;
        }
    }
    bool same(int a, int b){
        return find_parent(a) == find_parent(b);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--){
        int n;
        cin >> n;
        vector<int> vals;
        bool same = false;
        vector<pair<int, int>> pos, neg;
        for (int x = 0; x < n; x++){
            int i, j, e;
            cin >> i >> j >> e;
            vals.push_back(i);
            vals.push_back(j);
            e == 1 ? pos.push_back({i, j}) : neg.push_back({i, j});
        }
        auto getId = [&](int x){
            return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
        };
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        DSU dsu(vals.size());
        for (auto a : pos){
            dsu.unite(getId(a.first), getId(a.second));
        }
        for (auto n : neg){
            same = dsu.same(getId(n.first),getId(n.second));
            if (same) break;
        }
        cout << (same ? "NO" : "YES") << '\n';
    }
    return 0;
}