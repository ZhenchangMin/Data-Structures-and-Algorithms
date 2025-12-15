#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef struct Resident{
    ll a, b;
    ll diff;
    int type; // 0 means higher when adjacent, 1 means lower when adjacent
} resident;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        ll n, m;
        cin >> n >> m;
        vector<resident> people(n);
        ll independent_ppl = 0, adjacent_ppl = 0;
        for (int i = 0; i < n; i++){
            cin >> people[i].a >> people[i].b;
            people[i].diff = abs(people[i].a - people[i].b);
            people[i].type = (people[i].a > people[i].b) ? 0 : 1;
            if (people[i].type) independent_ppl++;
            else adjacent_ppl++;
        }
        ll independent_houses = (m - 1) / 2;
        

        
    }
    return 0;
}