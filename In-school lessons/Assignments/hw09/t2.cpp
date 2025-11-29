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
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return true;
    }
};

struct Edge {
    int u,v;
    double w;
    bool operator<(Edge const& o) const { return w < o.w; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n>>m)) return 0;
    vector<long long> A(n), B(m);
    for(int i=0;i<n;i++) cin>>A[i];
    for(int j=0;j<m;j++) cin>>B[j];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vector<Edge> edges;
    for(int i=0;i+1<n;i++){
        edges.push_back({i, i+1, double(llabs(A[i+1]-A[i]))});
    }
    const double SQ2 = sqrt(2.0);
    for(int j=0;j+1<m;j++){
        edges.push_back({n+j, n+j+1, SQ2 * double(llabs(B[j+1]-B[j]))});
    }

    for(int i=0;i<n;i++){
        double target = A[i] / 2.0;
        int idx = lower_bound(B.begin(), B.end(), target) - B.begin();
        if(idx < m){
            double dx = double(A[i] - B[idx]);
            double dy = double(B[idx]);
            double dist = sqrt(dx*dx + dy*dy);
            edges.push_back({i, n+idx, dist});
        }
        if(idx-1 >= 0){
            int t = idx-1;
            double dx = double(A[i] - B[t]);
            double dy = double(B[t]);
            double dist = sqrt(dx*dx + dy*dy);
            edges.push_back({i, n+t, dist});
        }
    }

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

    sort(edges.begin(), edges.end());
    DSU dsu(n + m);
    double ans = 0.0;
    int cnt = 0;
    for(auto &e : edges){
        if(dsu.unite(e.u, e.v)){
            ans += e.w;
            cnt++;
            if(cnt == n + m - 1) break;
        }
    }

    cout << fixed << setprecision(12) << ans << "\n";
    return 0;
}
