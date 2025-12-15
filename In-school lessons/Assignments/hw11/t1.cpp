#include <bits/stdc++.h>
using namespace std;
struct Resident{
    int a, b;
    int type
}resident;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> people(n);
        for (int i = 0; i < n; i++){
            cin >> people[i].first >> people[i].second;
        }
        
    }
    return 0;
}