#include <iostream>
using namespace std;

typedef struct position{
    int x, y;
}Pos;

long double solve(Pos *points, int n){
    int sign = points[0].y;
    for (int i = 1; i < n; i++){
        if (points[i].y != sign){
            return -1;
        }
    }
    
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Pos points[n];
    for (int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        points[i]={x, y};
    }
    long double ans = solve(points, n);
    cout << ans << '\n';
    return 0;
}
