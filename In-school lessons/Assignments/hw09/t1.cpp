#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;

        vector<vector<int>> graph(n + 1);// 图的邻接表，表示 a < b：边 a → b
        vector<int> indeg(n + 1, 0);// 记录每个点的入度（多少个点必须在它之前）

        for(int i = 0; i < m; i++){
            int x, y;
            cin >> x >> y;   // x < y
            graph[x].push_back(y);
            indeg[y]++;
        }
        // 使用小根堆保证取出的始终是当前「可放置」的最小编号的点
        priority_queue<int, vector<int>, greater<int>> pq;
        // 所有没有前置约束的点（入度为 0）可以先加入堆
        for(int i = 1; i <= n; i++){
            if(indeg[i] == 0) pq.push(i);
        }

        vector<int> ans;// 用来存放结果排序
        while(!pq.empty()){
            int u = pq.top();
            pq.pop();
            ans.push_back(u);// 将此点加入输出结果
            // 遍历 u 指向的所有结点（u < v）
            for(int v : graph[u]){
                if(--indeg[v] == 0){// v 减少一个必须在它之前的点，然后如果是0那么现在v也可以加入pq
                    pq.push(v);
                }
            }
        }

        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << ' ';
        }
    }
    return 0;
}
