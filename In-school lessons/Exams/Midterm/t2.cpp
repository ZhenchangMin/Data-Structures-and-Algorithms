// 100 in exam
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int comp(vector<ll> a, vector<ll> b){
    return a[2] > b[2];
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        ll n;
        cin >> n;
        vector<vector<ll>> platforms;
        ll sx = 0, sy = 0;
        ll temp = n;
        while(temp--){
            vector<ll> tmp;
            for(int i = 0; i < 3; i++){
                ll x;
                cin >> x;
                tmp.push_back(x);
            }
            platforms.push_back(tmp);
        }
        cin >> sx >> sy;
        // input over
        ll cur_x = sx, cur_y = sy;
        sort(platforms.begin(), platforms.end(), comp);
        ll index = platforms.size();
        for (int i = 0; i < platforms.size(); i++){
            if (sy >= platforms[i][2]) {
                index = i;
                break;
            }
        }
        while (cur_y != 0 && index < platforms.size()){
            if (platforms[index][0] < cur_x){
                if (platforms[index][1] < cur_x){
                    index++;
                    continue;
                }
                cur_x = platforms[index][1];
                cur_y = platforms[index][2];
            }
            cur_y = platforms[index][2];
            index++;
            continue;
        }
        cout << cur_x << '\n';
    }
    return 0;
}