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

    // parent[u] 记录父节点；order 记录从根出发的DFS遍历序，随后反向用于后序处理
    vector<int> parent(n, -1), order;
    order.reserve(n);

    stack<int> st;
    st.push(0);
    parent[0] = -2; // 根的父亲打特殊标记，避免回到父边
    // 用栈模拟 DFS，生成 parent 数组和 order 序列
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
    // sz[u] 记录以 u 为根的子树节点数
    // dp[u] 记录以 u 为根的u到子树中节点的距离和

    // 第一次：按 order 的逆序（等价后序）自底向上汇总子树规模与距离和
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == parent[u]) continue;
            sz[u] += sz[v];
            dp[u] += dp[v] + sz[v]; // 重要的公式！可以推导出来
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
            ans[v] = ans[u] + (long long)n - 2 * sz[v];
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