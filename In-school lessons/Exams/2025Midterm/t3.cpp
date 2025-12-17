#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <ctype.h>
#include <iomanip>
using namespace std;
using ll = long long;

struct Pos{
    int x;
    int y;
};

int main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<Pos*> horses(n);
        for(int i = 0; i < n; i++){
            horses[i] = new Pos();
            cin >> horses[i]->x >> horses[i]->y;
        }
        int a, b, c;
        cin >> a >> b >> c;
        double ans = 0;
        ans = abs(horses[0]->x * a + horses[0]->y * b + c);
        ans /= (double)sqrt(pow(a, 2)+pow(b, 2));
        cout<<fixed<<setprecision(10)<<ans<<'\n';
    }
    return 0;
}