#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>
#include <string>
using namespace std;
using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<pair<ll, int>> tmp;
    for (int i = 0; i < n; i++)
        tmp.push_back({arr[i], i});
    stable_sort(tmp.begin(), tmp.end());

    vector<int> ranks(n);// ranks[i] is the rank of arr[i]
    int r = 0;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && tmp[i].first != tmp[i - 1].first)
            r++;
        ranks[tmp[i].second] = r;
    }
    int distinct = r + 1;

    int k = 0;
    while ((1LL << k) < distinct)
        k++;
    if (k == 0)
        k = 1;

    deque<int> A, B;
    for (int i = 0; i < n; i++)
        A.push_back(ranks[i]);

    vector<string> ops;

    for (int bit = 0; bit < k; ++bit)
    {
        int cntB = 0;
        for (int i = 0; i < n; i++)
        {
            int x = A.front();
            A.pop_front();
            if ((x & (1LL << bit)) == 0)
            {
                A.push_back(x);
                ops.push_back("A A");
            }
            else
            {
                B.push_back(x);
                ops.push_back("A B");
                cntB++;
            }
        }
        for (int i = 0; i < cntB; i++)
        {
            int x = B.front();
            B.pop_front();
            A.push_back(x);
            ops.push_back("B A");
        }
    }

    cout << ops.size() << "\n";
    for (auto &p : ops)
        cout << p << "\n";

    return 0;
}
