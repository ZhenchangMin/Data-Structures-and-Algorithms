#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ull = unsigned long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull N;
    cin >> N;
    vector<pair<ull, ull>> kids(N);
    for (int i = 0; i < N; i++)
    {
        cin >> kids[i].first >> kids[i].second;
    }

    sort(kids.begin(), kids.end());

    ull total = 0;
    for (auto &p : kids)
        total += p.second;

    ull prefix = 0;
    for (int i = 0; i < N; i++)
    {
        prefix += kids[i].second;
        if (prefix * 2 >= total)
        {
            cout << kids[i].first << "\n";
            return 0;
        }
    }
    return 0;
}
