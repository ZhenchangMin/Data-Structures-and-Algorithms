#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> gates(n);
    int total = 0;
    for(int i = 0; i < n; i++){
        cin >> gates[i];
        total += gates[i];
    }
    int max_distribution = total / n;
    cout << max_distribution << '\n';
    return 0;
}