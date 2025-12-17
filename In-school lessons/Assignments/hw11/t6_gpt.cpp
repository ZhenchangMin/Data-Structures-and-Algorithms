// 题意：给定一棵 n 个点的树（点从 0 到 n-1），
// 输出每个点到其它所有点的距离之和。
//
// 解法总览（换根 DP / Sum of Distances in Tree）：
// 1) 以 0 号点为根，先做一次自底向上的 DP：
//    - `sz[u]` 表示以 u 为根的子树大小（结点数）。
//    - `dp[u]` 表示 u 到其子树内所有点的距离和。
//    这一步对每条树边只处理常数次，O(n)。
// 2) 再做一次自顶向下的“换根”传递：
//    - 已知 `ans[u]` 是以 u 为根时，u 到整棵树所有点的距离和。
//    - 对于与 u 相连的子节点 v，把根从 u 换到 v：
//        以 v 子树中的点（共 sz[v] 个）到 v 距离都减 1；
//        其余点（共 n - sz[v] 个）到 v 距离都加 1。
//      因此有公式：`ans[v] = ans[u] + n - 2 * sz[v]`。
//    依次把答案推到所有结点，整体仍是 O(n)。
// 3) 本实现用显式栈模拟 DFS，避免深递归造成的栈溢出风险。
//
// 正确性要点：
// - 第一次遍历按树的父子关系聚合子树贡献，`dp[u] = Σ(dp[v] + sz[v])`（v 为 u 的孩子），
//   因为把子树中任一点到 u 的距离视为到 v 的距离再加 1，累加得到子树的距离和。
// - 第二次“换根”关系来自于对所有点距离的统一 ±1 调整，如上公式推得。
// - 两次遍历覆盖每条边的常数次处理，总复杂度 O(n)，满足大规模输入需求。

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    // parent[u] 记录父节点；order 记录从根出发的遍历序，随后反向用于后序处理
    vector<int> parent(n, -1), order;
    order.reserve(n);

    stack<int> st;
    st.push(0);
    parent[0] = -2; // 根的父亲打特殊标记，避免回到父边
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);
        for (int v : g[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            st.push(v);
        }
    }

    vector<long long> sz(n, 0), dp(n, 0), ans(n, 0);

    // 第一次：按 order 的逆序（等价后序）自底向上汇总子树规模与距离和
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == parent[u]) continue;
            sz[u] += sz[v];
            dp[u] += dp[v] + sz[v];
        }
    }

    // 根 0 的全局答案就是其子树 DP 值（此时子树即整棵树）
    ans[0] = dp[0];
    // 第二次：自顶向下按照换根公式传播答案到所有结点
    st.push(0);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (int v : g[u]) {
            if (v == parent[u]) continue;
            ans[v] = ans[u] + (long long)n - 2LL * sz[v];
            st.push(v);
        }
    }

    // 按题意输出：一行 n 个整数，空格分隔
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}