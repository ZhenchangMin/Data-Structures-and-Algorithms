// 算法思路（本实现的模拟）：
// - 用一个栈 s 维护 DFS 的搜索边界（前沿）：保存尚未展开的邻居顶点，且这些邻居
//   都严格大于当前已访问的最大顶点 current（因为伪代码按编号递增处理 w，若要
//   保证全局顺序递增，则只能向更大的编号扩展）。
// - 邻居按降序（greater<int>）插入，使栈顶代表真实 DFS 下一步会走到的顶点：
//   若栈顶 > 期望的 i，则 DFS 将先访问更大的点，破坏顺序；因此我们必须“加边”，
//   让 i 成为下一步；若栈顶 == i，则说明不需要加边，按 DFS 自然过程即可访问 i。
// - 每次推进 i 前，把已过期的边界（栈顶 < i）弹出，因为这些顶点编号比 i 小，
//   若存在它们，DFS 早就应该访问过，不会出现在“下一步”。
// - 统计在 2..n 的每一步中，因栈顶不是 i 而被迫“加边”的次数，即为最少加边数。

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        // 邻接集合：按降序存储，便于获取“下一步将访问的顶点”（栈顶）。
        vector< set<int, greater<int>> > edges(n + 1);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (a == b) continue; // 自环对“下一步是谁”无贡献，忽略
            edges[a].insert(b);
            edges[b].insert(a);
        }
        int ans = 0;             // 最少需要加边的次数
        stack<int> s;
        int current = 1;         // 当前已访问的最大编号（从 1 开始）
        for (int num : edges[1]) {
            if (num <= current) continue; // 只保留比 current 更大的候选邻居
            s.push(num);
        }
        for (int i = 2; i <= n; ++i) {
            // 移除过期的候选（比i小的），它们若存在早应被访问，不会成为下一步，这样就不需要判断是否visited
            while (!s.empty() && s.top() < i) s.pop();
            // 若栈顶恰好是 i，则按 DFS 自然顺序能访问到 i，不需要加边
            if (!s.empty() && s.top() == i) {
                s.pop();
                for (int num : edges[i]) {
                    if (num <= current) continue; // 只保留更大的新邻居，维持递增序
                    s.push(num);
                }
            } else {
                // 栈顶不是 i（可能为空或大于 i），说明 DFS 的下一步不是 i，会破坏顺序。
                // 为了让 i 成为下一步，最少需要加一条边把 i 接入当前边界。
                ++ans;
                current = i; // 逻辑上“把 i 接进来”，更新当前最大编号
                for (int num : edges[i]) {
                    if (num <= current) continue;
                    s.push(num);
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
// 整体思路就是用stack模拟DFS的过程，同时维护一个当前已经访问过的最大节点编号current
// 如果下一个要访问的节点i不是current，说明需要添加一条边才能访问i，从而保证DFS的顺序递增。
// 那我们就逻辑上加入这条边，并更新current为i，然后继续模拟DFS过程。