#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;
using ll = long long;

inline bool canSurvive(ll total_water, ll n)
{
    return total_water >= n; // Each day, at least n water is needed to survive, cuz we can allocate every tower to have 1 water.
}

inline bool canSurviveInfinite(ll total_water, ll total_consume, ll n)
{
    return n == total_consume && total_water >= n; // If the total water is enough to survive, and the total consume is equal to n, then it will survive infinitely.
}

ll calculateMaxDays(ll total_water, ll total_consume, ll n, ll min_idx, vector <ll>& m)
{
    if (!canSurvive(total_water, n))
        return 0;
    if (canSurviveInfinite(total_water, total_consume, n))
        return -1;

    ll days = 0;

    if (m[min_idx] == 1)
    {
        ll loss = total_consume - n; // The loss of water each day.
        if (total_water < n)
            return 0;
        if (loss <= 0)
            return -1;
        return (total_water - n) / loss; // The number of days can survive.
    }

    while (total_water >= n)
    {
        ll next = (total_water - total_consume + m[min_idx]) / m[min_idx] + (n - 1); // The total_water left after today pass.
        if (next < n)// Not enough water, definitely at least one tower have 0 water at the end of today, break.
            break;
        total_water = next; // update total_water.
        if (canSurviveInfinite(total_water, total_consume, n))
            return -1;
        days++; // update days.
    }

    return days;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n + 1), m(n + 1);
    ll total_water = 0, total_consume = 0;
    ll min_idx = 1; // index of the tower with minimum m[i]

    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
        total_water += a[i];
    }
    for (ll i = 1; i <= n; i++)
    {
        cin >> m[i];
        total_consume += m[i];
        if (m[i] < m[min_idx])
            min_idx = i; // update min_idx.
    }

    while (q--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll i;
            ll x;
            cin >> i >> x;
            total_water += x - a[i];
            a[i] = x;
        }
        else if (op == 2)
        {
            ll i;
            ll x;
            cin >> i >> x;
            total_consume += x - m[i];
            m[i] = x;
            if (x < m[min_idx])
                min_idx = i; // update min_idx.
            else if (i == min_idx)
            {
                min_idx = min_element(m.begin() + 1, m.end()) - m.begin(); // if change the min_idx, find the new min_idx.
            }
        }
        else if (op == 3)
        {
            ll ans = calculateMaxDays(total_water, total_consume, n, min_idx, m);
            cout << ans << '\n';
        }
    }
    return 0;
}