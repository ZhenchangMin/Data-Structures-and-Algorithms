// 整体思路：先把大于等于2的度数都用自环消耗掉，然后把剩下的度数为1的点两两配对连接。
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> deg(n + 1);
    long long sum = 0;

    for (int i = 1; i <= n; i++) {
        cin >> deg[i];
        sum += deg[i];
    }

    if (sum % 2 != 0) {
        cout << -1 << "\n";
        return 0;
    }

    vector<pair<int,int>> edges;

    for (int i = 1; i <= n; i++) {
        while (deg[i] >= 2) {
            edges.emplace_back(i, i);
            deg[i] -= 2;
        }
    }

    vector<int> ones;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) ones.push_back(i);
    }

    if (ones.size() % 2 != 0) {
        cout << -1 << "\n";
        return 0;
    }

    for (int i = 0; i < (int)ones.size(); i += 2) {
        edges.emplace_back(ones[i], ones[i+1]);
    }

    cout << edges.size() << "\n";
    for (auto &e : edges) {
        cout << e.first << " " << e.second << "\n";
    }

    return 0;
}
