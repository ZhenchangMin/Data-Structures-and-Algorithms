#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<vector<int>> hasEdge(n + 1, vector<int>(n + 1, 0));
        int curr_index = 1;
        int total = 0;
        vector<pair<int, int>> hasEdgeBetween;
        for (int i = curr_index + 1; i <= n; i += 2)
        {
            cout << '?' << ' ' << curr_index << ' ' << i << endl;
            cin >> hasEdge[curr_index][i];
            total += hasEdge[curr_index][i];
            hasEdgeBetween.push_back({curr_index, i});
            curr_index = i + 1;
        }
        if (total == 0 || total > 1)
        {
            cout << "! 1" << endl;
            continue;
        }
        int left = hasEdgeBetween[0].first;
        int right = hasEdgeBetween[0].second;
        int leftForward = left - 1 > 0 ? left - 1 : n;
        int leftForwardTwo = leftForward - 1 > 0 ? leftForward - 1 : n;
        int rightForward = right + 1 <= n ? right + 1 : 1;
        int rightForwardTwo = rightForward + 1 <= n ? rightForward + 1 : 1;
        cout << '?' << ' ' << leftForward << ' ' << left << endl;
        int leftForwardResult;
        cin >> leftForwardResult;
        cout << '?' << ' ' << rightForward << ' ' << right << endl;
        int rightForwardResult;
        cin >> rightForwardResult;
        if (leftForwardResult == 0 && rightForwardResult == 0)
        {
            cout << "! 1" << endl;
            continue;
        }
        int possibleRoot = leftForwardResult == 1 ? left : right;
        int rootForward = leftForwardResult == 1 ? leftForwardTwo: rightForwardTwo;
        cout << '?' << ' ' << possibleRoot << ' ' << rootForward << endl;
        int rootForwardResult;
        cin >> rootForwardResult;
        if (rootForwardResult == 1)
        {
            cout << "! 2" << endl;
            continue;
        }
        else
        {
            cout << "! 1" << endl;
            continue;
        }
    }
    return 0;
}