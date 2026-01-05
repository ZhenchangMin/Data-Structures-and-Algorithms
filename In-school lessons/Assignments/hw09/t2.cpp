// 也就是说，对于这n+m个点，我们要把他们连成一棵树，并且需要所用线段长度总和最小，也就是最小生成树问题。
// 但对本题直接枚举所有两点对为边会导致O(n*m)条边，数据范围下无法接受。
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n=0): n(n), p(n), r(n,0) { for(int i=0;i<n;i++) p[i]=i; }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;//这一行一定会执行，把b的根连到a的根下面，也就是合并了这两个集合
        if(r[a]==r[b]) r[a]++;//只有在秩相等时才增加秩
        return true;
    }
};// 并查集的树实现，用秩优化

struct Edge {
    int u,v;
    double width;
    bool operator<(Edge const& o) const { return width < o.width; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    vector<long long> A(n), B(m);
    for(int i=0;i<n;i++) cin>>A[i];
    for(int j=0;j<m;j++) cin>>B[j];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    // 必加的线内相邻边
    // 若把每条直线上点排序（按横坐标），显然在一条直线上相邻的两点之间的边很可能是 MST 的候选。
    vector<Edge> edges;
    for(int i=0;i+1<n;i++){
        edges.push_back({i, i+1, double(llabs(A[i+1]-A[i]))});
    }
    const double SQ2 = sqrt(2.0);
    for(int j=0;j+1<m;j++){
        edges.push_back({n+j, n+j+1, SQ2 * double(llabs(B[j+1]-B[j]))});
    }

    // 跨线边（两条直线之间的边）太多，如何剪枝？
    // 算出(a,0) 到 (0,b) 的距离为 sqrt((a-b)^2 + b^2)
    // 设 f(b) = sqrt((a-b)^2 + b^2)，对b求导，知道 f(b) 在 b=a/2 处取得最小值
    // 所以最接近 a/2 的那一个或两个 b 值是最有希望成为最短跨边的点
    // 同理，对于每个 b，也找最接近 2*b 的 a 值
    // 这样每个点只会产生两条跨边，最多 2*(n+m) 条跨边，完全可以接受

    for(int i=0;i<n;i++){
        double target = A[i] / 2.0;// 理想的 b 值使距离最小
        int idx = lower_bound(B.begin(), B.end(), target) - B.begin();
        // idx 若在范围内，则把 A[i] 与 B[idx] 连接
        if(idx < m){
            double dx = double(A[i] - B[idx]);
            double dy = double(B[idx]);
            double dist = sqrt(dx*dx + dy*dy);
            edges.push_back({i, n+idx, dist});
        }
         // 同样考虑 idx-1（前一个候选）
        if(idx-1 >= 0){
            int t = idx-1;
            double dx = double(A[i] - B[t]);
            double dy = double(B[t]);
            double dist = sqrt(dx*dx + dy*dy);
            edges.push_back({i, n+t, dist});
        }
    }

    // 4) 对每个 B[j]，把它与 A 中最接近 2*b 的位置连接（最多两条）
    //    这一步是对称上的补充
    for(int j=0;j<m;j++){
        double target = 2.0 * B[j];
        int idx = lower_bound(A.begin(), A.end(), target) - A.begin();
        if(idx < n){
            double dx = double(A[idx] - B[j]);
            double dy = double(B[j]);
            double dist = sqrt(dx*dx + dy*dy);
            edges.push_back({idx, n+j, dist});
        }
        if(idx-1 >= 0){
            int t = idx-1;
            double dx = double(A[t] - B[j]);
            double dy = double(B[j]);
            double dist = sqrt(dx*dx + dy*dy);
            edges.push_back({t, n+j, dist});
        }
    }

    // 现在我们已经收集了所有候选边：相邻线内边 + 每点对另一条直线的 2 个候选跨边

    //Kruskal：按边权排序并用并查集合并

    sort(edges.begin(), edges.end());
    DSU dsu(n + m);// 总共有 n+m 个点
    double ans = 0.0;
    int cnt = 0;
    for(auto &e : edges){
        if(dsu.unite(e.u, e.v)){
            ans += e.width;
            cnt++;
            if(cnt == n + m - 1) break;
        }
    }

    cout << fixed << setprecision(12) << ans << "\n";
    return 0;
}
// Kruskal 生成树如何用“并查集”判断环？
// 当我们要添加一条边 (u,v) 时，若 u,v 已经在同一棵树中，也就是unite返回false，说明这会形成环，不能添加。
// 否则，合并这两棵树。