#include <iostream>
#include <vector>
using namespace std;
int getCount(vector<int>& a){
    int n = a.size();
    int count = 0;
    
    return count;
}
int main()
{
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int count = 0;
        count = getCount(a);
        cout << count << '\n';
    }
    return 0;
}