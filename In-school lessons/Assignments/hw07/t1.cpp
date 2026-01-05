#include <iostream>
#include <string>
#include <vector>

using namespace std;

int parent_[26];

int findp(int x){
    return parent_[x] == x ? x : parent_[x] = findp(parent_[x]);
}
void unite(int a, int b){
    a = findp(a);
    b = findp(b);
    if (a != b) parent_[b] = a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        int n = s1.size();
        for (int i = 0; i < 26; i++) parent_[i] = i;
        for (int i = 0; i < n; i++){
            unite(s1[i]-'a', s2[i]-'a');
        }
        bool same = true;
        for (int i = 0; i < n; i++){
            if (findp(s1[i]-'a') != findp(s3[i]-'a')){
                same = false;
                break;
            }
        }
        cout << (same ? "NO" : "YES") << '\n';
    }
    return 0;
}
