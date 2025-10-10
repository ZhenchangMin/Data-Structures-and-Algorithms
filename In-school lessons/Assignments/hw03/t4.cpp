#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
using ll = long long;

bool canSurvive(const vector<ll> &water, const vector<ll> &consume)
{
    ll total_water = accumulate(water.begin() + 1, water.end(), 0LL);
    ll total_consume = accumulate(consume.begin() + 1, consume.end(), 0LL);
    int n = water.size() - 1;
    if (total_water < total_consume)
        return false;
    for (int i = 1; i <= n; i++)
    {
        if (water[i] == 0)
        {
            return false;
        }
    }
    return true;
}

void reallocate(vector<ll> &water, const vector<ll> &consume)
{
    ll total_water = accumulate(water.begin() + 1, water.end(), 0LL);
    
}

bool canSurviveInfinite(const vector<ll> &water, const vector<ll> &consume)
{
    int n = water.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        if (consume[i] != 1 || water[i] < 1)
        {
            return false;
        }
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
    reallocate(currWater, m);
    if (canSurviveInfinite(currWater, m))
        return -1;
    while (canSurvive(currWater, m))
    {
        reallocate(currWater, m);
        currWater = shrinkWater(currWater, m);
        total_days++;
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