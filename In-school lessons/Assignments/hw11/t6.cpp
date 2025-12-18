#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    vector<int> degreeIn(n, 0);
    for(int i = 0; i < n - 1; ++i){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degreeIn[v]++;
    }
    int root = 0;
    for (int i = 0; i < n; ++i) {
        if (degreeIn[i] == 0) {
            root = i;
            break;
        }
    }
    
}