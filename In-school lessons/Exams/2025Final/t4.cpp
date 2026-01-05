#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int T;
    cin >> T;
    while (T--){
        int n, m, c;
        cin >> n >> m >> c;
        vector<vector<int>> score(n, vector<int>(m));
        for(int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> score[i][j];
            }
        }
        int cur_col = 0;
        vector<int> max(m);
        int cur_row = 0;
        vector<int> max_row(m);
        int ans = 0;
        for (int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if (max[i] < score[j][i]){
                    max[i] = score[j][i];
                    max_row[i] = j;
                }
            }
        }
        cur_row = max_row[0];
        ans += max[0];
        for (int i = 1; i < m; i++){
            if (cur_row == max_row[i]){
                ans += max[i];
            }
            else if(max[i] >= c + score[cur_row][i]){
                cur_row = max_row[i];
                ans += max[i] - c;
            }
            else {
                ans += score[cur_row][i];
            }
            
        }
        cout << ans << '\n';
    }
    return 0;
}