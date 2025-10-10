#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
using ll = long long;

void reallocate(vector<ll> &water, const vector<ll> &consume)
{
    int n = water.size() - 1;
    ll total = accumulate(water.begin() + 1, water.end(), 0LL);
    if (total == 0)
        return;

    vector<ll> base(n + 1, 1);
    ll base_total = n;

    if (total < base_total)
    {
        fill(base.begin() + 1, base.end(), 0);
        ll remaining = total;
        for (int i = 1; i <= n && remaining > 0; i++)
        {
            base[i] = 1;
            remaining--;
        }
        water = base;
        return;
    }

    ll extra = total - base_total;
    ll total_m = 0;
    for (int i = 1; i <= n; i++)
    {
        total_m += consume[i];
    }

    if (total_m == 0)
    {
        water = base;
        return;
    }

    vector<ll> extra_dist(n + 1, 0);
    ll remaining_extra = extra;
    for (int i = 1; i <= n; i++)
    {
        extra_dist[i] = (extra * consume[i]) / total_m;
        remaining_extra -= extra_dist[i];
    }
    int max_m_idx = 1;
    for (int i = 2; i <= n; i++)
    {
        if (consume[i] > consume[max_m_idx])
        {
            max_m_idx = i;
        }
    }
    extra_dist[max_m_idx] += remaining_extra;

    for (int i = 1; i <= n; i++)
    {
        water[i] = base[i] + extra_dist[i];
    }
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

vector<ll> shrinkWater(const vector<ll> &water, const vector<ll> &consume, bool &hasZero)
{
    int n = water.size() - 1;
    vector<ll> newWater(n + 1, 0);
    hasZero = false;
    for (int i = 1; i <= n; i++)
    {
        newWater[i] = water[i] / consume[i];
        if (newWater[i] == 0)
        {
            hasZero = true;
        }
    }
    return newWater;
}

ll calculateBatchDays(const vector<ll> &water, const vector<ll> &consume)
{
    int n = water.size() - 1;
    ll max_possible = 1e18;

    for (int i = 1; i <= n; i++)
    {
        ll w = water[i];
        ll c = consume[i];
        if (c == 1)
        {
            continue;
        }
        ll k = 0;
        ll temp_w = w;
        while (true)
        {
            ll next_w = temp_w / c;
            if (next_w == 0)
            {
                break;
            }
            k++;
            if (temp_w == next_w)
            {
                break;
            }
            temp_w = next_w;
        }
        max_possible = min(max_possible, k);
    }

    return max(max_possible, 1LL);
}

int calculateMaxDays(const vector<ll> &a, const vector<ll> &m)
{
    vector<ll> currWater = a;
    ll total_days = 0;

    while (true)
    {
        ll total = accumulate(currWater.begin() + 1, currWater.end(), 0LL);
        if (total == 0)
        {
            break;
        }

        reallocate(currWater, m);

        if (canSurviveInfinite(currWater, m))
        {
            return -1;
        }

        ll batch_days = calculateBatchDays(currWater, m);
        vector<ll> newWater(currWater.size(), 0);
        bool hasZero = false;
        for (int i = 1; i < currWater.size(); i++)
        {
            ll w = currWater[i];
            ll c = m[i];
            ll temp_w = w;
            for (ll d = 0; d < batch_days; d++)
            {
                temp_w /= c;
                if (temp_w == 0)
                {
                    hasZero = true;
                    break;
                }
            }
            newWater[i] = temp_w;
            if (newWater[i] == 0)
            {
                hasZero = true;
            }
        }

        if (hasZero)
        {
            break;
        }

        ll newTotal = accumulate(newWater.begin() + 1, newWater.end(), 0LL);
        if (newTotal == 0)
        {
            break;
        }

        currWater = newWater;
        total_days += batch_days;
    }

    return (int)total_days;
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