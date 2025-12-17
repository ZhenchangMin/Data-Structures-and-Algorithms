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
    if (total < 0 || coins.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    vector<long long> dp(total + 1, 0);
    dp[0] = 1;
    for (int coin : coins) {
        if (coin <= 0) continue;
        for (int i = coin; i <= total; i++) {
            dp[i] += dp[i - coin];
        }
    }

    cout << dp[total] << "\n";
    return 0;
}