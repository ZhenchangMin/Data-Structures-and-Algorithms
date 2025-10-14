#include <iostream>
#include <vector>
using namespace std;
using ull = unsigned long long;

vector<ull> mergeSort(vector<ull> a, ull left, ull right){
    if (left >= right) {
        return {a[left]}; // Return single element as vector
    }

    ull mid = left + (right - left) / 2;
    vector<ull> leftPart = mergeSort(a, left, mid);
    vector<ull> rightPart = mergeSort(a, mid + 1, right);
    // merge
    vector<ull> temp;
    temp.reserve(leftPart.size() + rightPart.size());
    ull i = 0, j = 0, k = 0;
    while (i < leftPart.size() && j < rightPart.size()) {
        cout << "? " << leftPart[i] << ' ' << rightPart[j] << '\n';
        char res;
        cin >> res;
        if (res == '<') {
            temp[k++] = leftPart[i++];
        } else {
            temp[k++] = rightPart[j++];
        }
    }
    while (i < leftPart.size()) {
        temp[k++] = leftPart[i++];
    }
    while (j < rightPart.size()) {
        temp[k++] = rightPart[j++];
    }
    return temp;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<ull> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        a = mergeSort(a, 0, n - 1);
        cout << '!' << '\n';
        for(const auto &x : a){
            cout << x << ' ';
        }
        cout << '\n';
    }
    return 0;
}