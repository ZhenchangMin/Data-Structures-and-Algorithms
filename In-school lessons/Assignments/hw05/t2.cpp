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
        bool hasEdge = false;

        vector<int> nodes;
        for (int i = 1; i <= min(n, 6); i++)
            nodes.push_back(i);

        for (int i = 1; i <= nodes.size() && !hasEdge; i++)
        {
            for (int j = i + 1; j <= nodes.size() && !hasEdge; j++)
            {
                int ans;
                cout << '?' << ' ' << nodes[i] << ' ' << nodes[j] << endl;
                cin >> ans;
                if (ans == 1)
                    hasEdge = true;
            }
        }

        if (hasEdge)
            cout << "! 1" << endl;
        else
            cout << "! 2" << endl;
    }
    return 0;
}