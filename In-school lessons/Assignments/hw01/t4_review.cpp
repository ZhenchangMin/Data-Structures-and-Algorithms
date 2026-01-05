#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int compute(const vector<int> &a)
{
    int ans = 0;
    for (int i = 0; i < a.size() - 1; i++)
    {
        int maxBetween = a[i + 1];
        for (int j = i + 1; j < a.size(); j++)
        {
            int minEdge = a[i];
            if (a[j] < minEdge)
                minEdge = a[j];
            if (j - i == 1)
            {
                ans++;
                continue;
            }
            if (maxBetween <= minEdge){
                ans++;
            }
            maxBetween = max(maxBetween, a[j]);
            if (minEdge == a[i] && maxBetween > minEdge){// Important: if i already shortest and have max bigger between, break immediately to save time.
                break;
            }
        }
    }
    return ans;
}

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
        vector<int> a;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            a.push_back(x);
        }
        cout << compute(a) << '\n';
    }
    return 0;
}