#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int calPairs(vector<char> a, ll n){
    int ans = 0;
    // for (int i = 0; i < n - 1; i++){
    //     if(a[i] != '1') continue;
    //     for (int j = i + 1; j < n; j++){
    //         if (a[j] == '0') ans++;
    //     }
    // }
    if (a[n-1] == '0'){
        a.push_back('1');
        n++;
    }
    vector<int> posIndex;
    int cur = 1;
    for(int i=0; i<n; i++){
        if (a[i] == '1') posIndex.push_back(i);
    }
    for (int i = 0; i < posIndex.size() - 1; i++){
        ans += (posIndex[i + 1] - posIndex[i] - 1) * cur;
        cur++;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        ll n;
        cin >> n;
        vector<char> bits(n);
        for (int i = 0; i < n; i++){
            cin >> bits[i];
        }
        //input over
        ll mid = n / 2;
        for (int i = 0; i < mid; i++){
            if (bits[i] == '?') bits[i] = '1';
        }
        for (int i = mid; i < n; i++){
            if (bits[i] == '?') bits[i] = '0';
        }
        cout << calPairs(bits, n) << '\n';
    }
    return 0;
}