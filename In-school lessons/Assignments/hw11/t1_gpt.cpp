#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {                // 多组测试用例
        int n;                   // 人数
        long long m;             // 总房间数（用long long防溢出）
        cin >> n >> m;

        vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i]; // a[i]：边缘位置收益；b[i]：中间位置收益
        }

        long long base = 0;      // 基准收益：所有人都住中间位置（全选b[i]）
        vector<long long> delta(n); // delta[i] = a[i]-b[i]：第i个位置换成边缘的收益差
        for (int i = 0; i < n; i++) {
            base += b[i];
            delta[i] = a[i] - b[i];
        }

        // M：最多能空出的房间带来的“边缘位置扩展数” = 总房间数 - 人数 + 1
        long long M = m - n + 1;

        // 按收益差从大到小排序：优先选收益差大的位置当边缘
        sort(delta.begin(), delta.end(), greater<long long>());
        // 前缀和数组：pre[k] = 前k个最大delta的和（选k个边缘位置的总收益差）
        vector<long long> pre(n + 1, 0);
        for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + delta[i - 1];

        long long best = LLONG_MIN; // 初始化最大收益为最小值

        // 情况1：若人数n ≤ M → 所有位置都能当中间位置（无需选边缘），收益为基准值base
        if (n <= M) best = max(best, base);

        // 情况2：计算合法的最小边缘数kmin
        // 核心逻辑：kmin = max(2, n - M + 1) → 至少选2个边缘（首尾），且不小于2
        long long kmin = max(2LL, (long long)n - M + 1); 
        if (kmin < 2) kmin = 2; // 兜底：确保至少选2个边缘

        // 遍历所有合法的边缘数k（从kmin到n），计算总收益并更新最大值
        for (long long k = kmin; k <= n; k++) {
            best = max(best, base + pre[(int)k]);
        }

        cout << best << "\n"; // 输出每组的最大收益
    }
    return 0;
}