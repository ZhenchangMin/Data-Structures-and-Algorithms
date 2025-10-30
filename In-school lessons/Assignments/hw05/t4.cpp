#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100005;

struct Node {
    int left, right, parent;
} tree[MAXN];

int n;

int ask(int u, int v) {
    cout << "? " << u << " " << v << endl;
    cout.flush();
    int res;
    cin >> res;
    return res;
}

void solve() {
    vector<int> candidates;
    for (int i = 1; i <= n; i++) {
        candidates.push_back(i);
    }
    
    while (candidates.size() > 1) {
        int u = candidates[0];
        int v = candidates[1];
        int res = ask(u, v);
        if (res == 0) {
            candidates.erase(candidates.begin() + 1);
        } else if (res == 2) {
            candidates.erase(candidates.begin());
        } else {
            candidates.erase(candidates.begin());
        }
    }
    
    cout << "! " << candidates[0] << endl;
    cout.flush();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> tree[i].left >> tree[i].right;
        }
        solve();
    }
    
    return 0;
}