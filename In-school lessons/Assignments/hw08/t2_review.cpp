// 因为每次输入的边的权值都是前一个的2倍，由等比数列求和公式可知
// 第一次出现环的时候，环上的边权值和为最小值。
// 因此只需找到第一条成环边以及该边在当前森林中连接的两个端点间的唯一路径即可。
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n=0){init(n);}
    void init(int n){
        p.resize(n+1);
        r.assign(n+1,0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return true;
    }
    bool same(int a,int b){ return find(a)==find(b); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    if(!(cin>>T)) return 0;
    while(T--){
        int n,m; cin>>n>>m;
        vector<pair<int,int>> edges(m+1);
        for(int i=1;i<=m;i++){
            int u,v; cin>>u>>v;
            edges[i]={u,v};
        }

        DSU dsu(n);
        vector<vector<pair<int,int>>> g(n+1); // (to, edge_id)
        bool found=false;
        vector<int> answer;

        for(int i=1;i<=m;i++){
            int u=edges[i].first, v=edges[i].second;
            if(!found){
                if(!dsu.same(u,v)){
                    dsu.unite(u,v);
                    g[u].push_back({v,i});
                    g[v].push_back({u,i}); // 这里把边存进图，如果没成环的话，说明第一条成环边不在里面
                }else{
                    // 第一条成环边 -> 在当前森林中找唯一路径，从u到v
                    vector<int> parent(n+1,-1), pedge(n+1,-1);
                    queue<int> q; // 用一个队列做 bfs
                    q.push(u);
                    parent[u]=u;
                    // bfs 来找路径
                    while(!q.empty() && parent[v]==-1){
                        int x=q.front(); q.pop();
                        for(auto [y,eid]: g[x]){// 注意：g里面并没有成环边{u,v}
                            if(parent[y]==-1){
                                parent[y]=x;
                                pedge[y]=eid;
                                q.push(y);
                            }
                        }
                    }
                    vector<int> seq;
                    // 路径边号
                    int cur=v;
                    while(cur!=u){
                        seq.push_back(pedge[cur]);
                        cur=parent[cur];
                    }
                    seq.push_back(i); // 成环边本身
                    sort(seq.begin(), seq.end()); // 升序输出指数
                    answer=move(seq);
                    found=true;
                    // 后续边只读不处理
                }
            }
        }

        if(!found){
            cout << -1 << "\n";
        }else{
            for(size_t k=0;k<answer.size();k++){
                if(k) cout << ' ';
                cout << answer[k];
            }
            cout << "\n";
        }
    }
    return 0;
}