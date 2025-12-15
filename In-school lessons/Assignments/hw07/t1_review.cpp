#include <bits/stdc++.h>
using namespace std;

char find_parent(char a, unordered_map<char, char> &parents){
    if (parents[a] == a) return a;
    else{
        parents[a] = find_parent(parents[a], parents);
        return parents[a];
    }
}
bool unite(char a, char b, unordered_map<char, char> &parents){
    char A = find_parent(a, parents);
    char B = find_parent(b, parents);
    if (A == B) return true;
    else{
        parents[B] = A;
        return false;
    }
}

int main(){
    int T;
    cin >> T;
    while (T--){
        unordered_map<char, char> parents(26);
        for (int i = 0; i < 26; i++){
            parents[(char)(i + 'a')] = (char)(i + 'a');
        }
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        int n = s1.length();
        for (int i = 0; i < n; i++){
            unite(s1[i], s2[i], parents);
        }
        bool same = true;
        for (int i = 0; i < n; i++){
            if (!unite(s1[i], s3[i], parents)) {
                same = false;
                break;
            }
        }
        cout << (same ? "NO" : "YES") << '\n';
        }
    return 0;
}