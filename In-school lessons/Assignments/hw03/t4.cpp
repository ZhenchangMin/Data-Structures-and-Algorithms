#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;
using ll = long long;

inline bool canSurvive(ll total_water, int n)
{
    return total_water >= n;
}

inline bool canSurviveInfinite(ll total_water, ll total_consume, int n)
{
    return n == total_consume && total_water >= total_consume;
}

int calculateMaxDays(ll total_water, ll total_consume, int n, ll min_m)
{
    if (!canSurvive(total_water, n))
        return 0;
    if (canSurviveInfinite(total_water, total_consume, n))
        return -1;

    ll r = min_m;
    ll days = 0;

    if (r == 1)
    {
        ll loss = total_consume - n;
        if (total_water < n)
            return 0;
        if (loss <= 0)
            return -1;
        return (ll)((total_water - n) / loss);
    }

    while (total_water >= n)
    {
        ll next = (total_water - total_consume + r) / r + (n - 1);
        if (next < n)
            break;
        total_water = next;
        days++;
    }

    return (ll)days;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1), m(n + 1);
    ll total_water = 0, total_consume = 0;
    int min_idx = 1;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        total_water += a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> m[i];
        total_consume += m[i];
        if (m[i] < m[min_idx])
            min_idx = i;
    }

    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i;
            ll x;
            cin >> i >> x;
            total_water += x - a[i];
            a[i] = x;
        }
        else if (op == 2)
        {
            int i;
            ll x;
            cin >> i >> x;
            total_consume += x - m[i];
            m[i] = x;
            if (x < m[min_idx])
                min_idx = i;
            else if (i == min_idx)
            {
                min_idx = min_element(m.begin() + 1, m.end()) - m.begin();
            }
        }
        else if (op == 3)
        {
            int ans = calculateMaxDays(total_water, total_consume, n, m[min_idx]);
            cout << ans << '\n';
        }
    }
    return 0;
}
