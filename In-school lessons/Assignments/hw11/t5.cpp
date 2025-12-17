#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int total;
    cin >> total;
    vector<int> coins;
    int x = 0;
    while (cin >> x){
        coins.push_back(x);
    }

    vector<long long> dp(total + 1, 0);
    dp[0] = 1; // 凑成 0 的方式只有不取任何硬币
    for (int coin : coins) {// 遍历每种硬币面值
        for (int i = coin; i <= total; i++) {
            dp[i] += dp[i - coin];// 更新凑成金额 i 的组合数
        }
    }

    cout << dp[total] << "\n";
    return 0;
}