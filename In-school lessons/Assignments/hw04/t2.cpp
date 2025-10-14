#include <iostream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;
using ui = unsigned int;
using ull = unsigned long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ui n, seed;
    cin >> n >> seed;
    vector<ui> a(n);
    mt19937 mt(seed);
    for (size_t i = 0; i < n; ++i)
    {
        a[i] = static_cast<ui>(mt()) % 100000U;
    }

    vector<int> buckets(100000, 0);
    for (ui i = 0; i < n; i++)
    {
        buckets[a[i]]++;
    }
    vector<ui> sorted;
    sorted.reserve(n);
    for (int i = 0; i < 100000; i++)
    {
        if (buckets[i] > 0)
        {
            for (int j = 0; j < buckets[i]; j++)
            {
                sorted.push_back(i);
            }
        }
    }
    ull answer = 0;
    const ull NUMBER = 998244353;
    ull power = 100000; // calculate step by step to avoid overflow, and remember to start from 100000^1
    for (ui i = 0; i < n; i++)
    {
        ull temp = (static_cast<ull>(sorted[i]) * power) % NUMBER;
        answer = (answer + temp) % NUMBER;
        power = (power * 100000ULL) % NUMBER;
    }
    cout << answer << "\n";
    return 0;
}