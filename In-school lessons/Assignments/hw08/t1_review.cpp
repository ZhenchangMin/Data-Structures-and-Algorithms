#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int n;
    cin >> n;
    vector<int> degrees(n + 1);
    ll degreeSum = 0;
    for (int i = 1; i <= n; i++){
        cin >> degrees[i];
        degreeSum += degrees[i];
    }
    if (degreeSum % 2 != 0){
        cout << -1 << '\n';
        return 0;
    }
    vector<pair<int, int>> edges;
    vector<int> left_vertices;
    for (int i = 1; i <= n; i++){
        ll circles = degrees[i] / 2;
        int left = degrees[i] % 2;
        while (circles--){
            edges.push_back({i, i});
        }
        if (left) left_vertices.push_back(i);
    }
    for (int i = 0; i < left_vertices.size(); i += 2){
        edges.push_back({left_vertices[i], left_vertices[i+1]});
    }
    cout << edges.size() << '\n';
    for (int i = 0; i < edges.size(); i++){
        cout << edges[i].first << ' ' << edges[i].second << '\n';
    }
    return 0;
}