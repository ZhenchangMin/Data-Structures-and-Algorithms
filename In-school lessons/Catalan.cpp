// 计算卡特兰数 Cn，即n个节点的二叉树形态数
#include <iostream>
using namespace std;

// 方法1：递归计算（效率低，n较大时会超时）
long long catalanRecursive(int n) {
    if (n <= 1) return 1;
    long long res = 0;
    for (int k = 0; k < n; k++) {
        res += catalanRecursive(k) * catalanRecursive(n - 1 - k);
    }
    return res;
}

// 方法2：动态规划（效率高，推荐）
long long catalanDP(int n) {
    long long dp[n + 1];
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = 0;
        for (int k = 0; k < i; k++) {
            dp[i] += dp[k] * dp[i - 1 - k];
        }
    }
    return dp[n];
}

int main() {
    int n = 5;
    cout << "n=" << n << " 时，二叉树形态数：" << catalanDP(n) << endl; // 输出42
    return 0;
}
