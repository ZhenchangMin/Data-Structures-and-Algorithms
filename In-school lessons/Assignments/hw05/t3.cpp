#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdio>
#include <cstdlib>
#define getchar_unlocked getchar
using namespace std;

using ull = unsigned long long;

struct Child
{
    ull a, w;
};

inline void fast_read(ull &x)
{
    x = 0;
    int c = getchar_unlocked();
    while (c < '0' || c > '9')
        c = getchar_unlocked();
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull N;
    fast_read(N);
    vector<Child> children(N);
    for (int i = 0; i < N; i++)
    {
        fast_read(children[i].a);
        fast_read(children[i].w);
    }

    sort(children.begin(), children.end(), [](const Child &x, const Child &y)
        { return x.a < y.a; });

    ull total = 0;
    for (auto &x : children)
        total += x.w;

    ull half_lower = total / 2, half_upper = (total + 1) / 2;
    ull preSum = 0, res = -1;
    for (auto x : children)
    {
        if (preSum < half_lower && total - preSum - x.w <= half_upper)
        {
            res = x.a;
            break;
        }
        preSum += x.w;
    }

    cout << res << '\n';
    return 0;
}