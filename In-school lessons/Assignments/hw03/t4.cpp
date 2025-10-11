#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;

bool canSurvive(const vector<ll> &water, const vector<ll> &consume)
{
    for (int i = 1; i <= water.size() - 1; i++)
    {
        if (water[i] == 0)
            return false;
    }
    return true;
}

void reallocate(vector<ll> &water, const vector<ll> &consume, int min_consume_idx)
{
    ll total_water = accumulate(water.begin() + 1, water.end(), 0LL);
    for (int i = 1; i <= water.size() - 1; i++)
    {
        if (i != min_consume_idx)
        {
            water[i] = consume[i];
            total_water -= water[i];
        }
    }
    water[min_consume_idx] = total_water;
}

bool canSurviveInfinite(const vector<ll> &water, const vector<ll> &consume)
{
    for (int i = 1; i <= water.size() - 1; i++)
    {
        if (consume[i] != 1)
            return false;
        if (water[i] < 1)
            return false;
    }
    return true;
}

vector<ll> shrinkWater(const vector<ll> &water, const vector<ll> &consume)
{
    int n = water.size() - 1;
    vector<ll> newWater(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        newWater[i] = water[i] / consume[i];
    }
    return newWater;
}

int calculateMaxDays(const vector<ll> &a, const vector<ll> &m)
{
    vector<ll> currWater = a;
    ll total_days = 0;
    ll total_water = accumulate(a.begin() + 1, a.end(), 0LL);
    int min_consume_idx = 1;
    for (int i = 2; i <= a.size() - 1; i++)
    {
        if (m[i] < m[min_consume_idx])
        {
            min_consume_idx = i;
        }
    }
    reallocate(currWater, m, min_consume_idx);
    if (canSurviveInfinite(currWater, m))
        return -1;
    if (!canSurvive(currWater, m))
        return 0;
    while (true)
    {
        currWater = shrinkWater(currWater, m);
        if (!canSurvive(currWater, m))
            break;
        else
        {
            total_days++;
            reallocate(currWater, m, min_consume_idx);
            if (canSurviveInfinite(currWater, m))
                return -1;
        }
    }
    return total_days;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1), m(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> m[i];

    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i;
            ll x;
            cin >> i >> x;
            a[i] = x;
        }
        else if (op == 2)
        {
            int i;
            ll x;
            cin >> i >> x;
            m[i] = x;
        }
        else if (op == 3)
        {
            int result = calculateMaxDays(a, m);
            cout << result << '\n';
        }
    }

    return 0;
}