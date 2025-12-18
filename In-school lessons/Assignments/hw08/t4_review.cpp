// 题意：给一个可能有重边和自环的无向图，要求通过最少加边，使从 1 开始的
// DFS 的遍历顺序恰好为 1,2,...,n。题目伪代码的关键点是：在 DFS(G,v) 中，
// “对所有顶点 w（按编号从小到大）若 v 与 w 有边且 w 未访问则递归”。
// 为了让整体访问序列严格递增，我们等价地模拟这一过程的“下一步将访问谁”。
// 如果在某一步，DFS 的“下一待访问顶点”不是当前期望的 i，那么就必须加一条边，
// 把 i 接到当前搜索边界上，使它成为 DFS 的下一步，从而维持 1..n 的顺序。

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
// 复杂度：O(n + m log deg)。使用 set 保证去重和按降序遍历；也可改用向量+排序。

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
            if (a < 1 || a > n || b < 1 || b > n) continue; // 越界输入忽略
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
            // 移除过期的候选（比 i 小的），它们若存在早应被访问，不会成为下一步
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