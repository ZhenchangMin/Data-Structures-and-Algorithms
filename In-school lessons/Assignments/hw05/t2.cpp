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
            curr_index += 2;
        }
        if (total == 0 || total > 1)
        {
            cout << "! 1" << endl;
            continue;
        }
        int left = hasEdgeBetween[0].first;
        int right = hasEdgeBetween[0].second;
        int leftSmaller = left - 1;
        if (leftSmaller == 0) leftSmaller = n;
        int rightBigger = right + 1;
        if (rightBigger == n + 1) rightBigger = 1;
        int leftBool, rightBool;
        cout << '?' << ' ' << left << ' ' << leftSmaller << endl;
        cin >> leftBool;
        cout << '?' << ' ' << right << ' ' << rightBigger << endl;
        cin >> rightBool;
        if(leftBool == 0 && rightBool ==0){
            cout << "! 1" << endl;
            continue;
        }
        else{
            int root = leftBool == 1 ? left : right;
            if(root == left){
                cout << '?' << ' ' << left << ' ' << rightBigger << endl;
                int res;
                cin >> res;
                if (res){
                    cout << "! 2" << endl;
                    continue;
                }
            }
            else{
                cout << '?' << ' ' << right << ' ' << leftSmaller << endl;
                int res;
                cin >> res;
                if (res)
                {
                    cout << "! 2" << endl;
                    continue;
                }
            }
            cout << "! 1" << endl;
            continue;
        }
    }
    return 0;
}