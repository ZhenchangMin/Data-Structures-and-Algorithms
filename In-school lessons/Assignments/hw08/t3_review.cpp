#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MOD = 998244353;
struct DSU{
    vector<ll> parent, rank;
    DSU(int n): parent(n+1), rank(n+1){
        iota(parent.begin(), parent.end(), 0);
        fill(rank.begin(), rank.end(), 0);
    }
    ll find(ll a){
        return parent[a] == a ? a : parent[a] = find(parent[a]);
    }
    bool unite(ll a, ll b){
        a = find(a);
        b = find(b);
        if (a == b) return true;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        rank[a] += rank[b];
        return false;
    }
    bool same(ll a, ll b){
        return find(a) == find(b);
    }
};

