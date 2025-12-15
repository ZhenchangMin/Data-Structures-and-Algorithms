#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
using ll = long long;
ll MAX = 1e9+1;
struct DSU{
    vector<ll> parent, descendent;
    DSU(ll n) : parent(n+1), descendent(n+1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    ll find_parent(ll a){
        if (parent[a] == a) return a;
        else{
            parent[a] = find_parent(parent[a]);
            descendent[parent[a]]++;
            return parent[a];
        }
    }
    bool unite(ll a, ll b){
        ll A = find_parent(a);
        ll B = find_parent(b);
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
};
int main(){
    int T;
    cin >> T;
    while (T--){
        ll n;
        cin >> n;
        DSU dsu(MAX);
        bool same = false;
        for (ll x = 0; x < n; x++){
            ll i, j, e;
            cin >> i >> j >> e;
            
        }
        cout << (same ? "NO" : "YES") << '\n';
    }
    return 0;
}