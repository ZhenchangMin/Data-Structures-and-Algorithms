#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

struct Child
{
    ll a, w;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Child> c(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> c[i].a >> c[i].w;
    }

    sort(c.begin(), c.end(), [](const Child &x, const Child &y)
        { return x.a < y.a; });

    ll total = 0;
    for (auto &x : c)
        total += x.w;

    ll half_lower = total / 2, half_upper = (total + 1) / 2;
    ll preSum = 0, res = -1;
    for (auto x : c)
    {
        ll left = preSum, right = total - left - x.w;
        if (left < half_lower && right <= half_upper)
        {
            res = x.a;
            break;
        }
        preSum += x.w;
    }

    cout << res << '\n';
    return 0;
}