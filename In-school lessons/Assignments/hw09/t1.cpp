#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;

int main(){
    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for(int i = 0; i < m; i++){
            int x = 0, y = 0;
            cin >> x >> y;
            a[y] = x; //x < y
        }

    }
    return 0;
}