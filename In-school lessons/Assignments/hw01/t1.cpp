#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    queue<string> way;
    while(n--){
        int q;
        cin >> q;
        switch (q)
        {
        case 1:{
            string flight_number;
            cin >> flight_number;
            if (way.size() < m){
                way.push(flight_number);
            }
            else{
                cout << "full" << '\n';
            }
            break;
        }
        case 2:{
            if (way.empty()){
                cout << "empty" << '\n';
            }
            else{
                cout << way.front() << '\n';
                way.pop();
            }
            break;
        }
        case 3:{
            cout << way.size() << '\n';
            break;
        }
        default:
            break;
        }
    }
}