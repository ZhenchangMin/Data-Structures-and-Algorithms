#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;
using ld = long double;

typedef struct Point
{
    ld x, y;
} point;

int n;
vector<point> points;

ld required_r(ld a, const vector<point> &pts)
{
    ld max_r = 0.0;
    for (const point p : pts)
    {
        ld r = ((p.x - a) * (p.x - a) + p.y * p.y) / (2.0 * p.y);
        if (r > max_r)
            max_r = r;
    }
    return max_r;
}

ld find(ld left, ld right, const vector<point> &pts, int iterations = 120)
{
    while (iterations--)
    {
        ld m1 = left + (right - left) / 3.0;
        ld m2 = right - (right - left) / 3.0;
        ld r1 = required_r(m1, pts);
        ld r2 = required_r(m2, pts);
        if (r1 < r2)
        {
            right = m2;
        }
        else
        {
            left = m1;
        }
    }
    return required_r((left + right) * 0.5, pts);
}

ld solve(int l, int r)
{
    if (r - l + 1 <= 3)
    {
        vector<point> sub(points.begin() + l, points.begin() + r + 1);
        ld best = 1e9;
        ld min_x = 1e9, max_x = -1e9;
        for (const auto &p : sub)
        {
            min_x = min(min_x, p.x);
            max_x = max(max_x, p.x);
        }
        min_x -= 1.0;
        max_x += 1.0;
        return find(min_x, max_x, sub);
    }

    int mid = (l + r) / 2;
    ld r_left = solve(l, mid);
    ld r_right = solve(mid + 1, r);

    ld min_x = 1e9, max_x = -1e9;
    for (int i = l; i <= r; i++)
    {
        min_x = min(min_x, points[i].x);
        max_x = max(max_x, points[i].x);
    }
    min_x -= 1.0;
    max_x += 1.0;

    vector<point> sub(points.begin() + l, points.begin() + r + 1);
    return find(min_x, max_x, sub);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    points.resize(n);
    bool has_positive = false, has_negative = false;
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
        if (points[i].y > 0)
            has_positive = true;
        if (points[i].y < 0)
            has_negative = true;
    }

    if (has_positive && has_negative)
    {
        cout << -1 << '\n';
        return 0;
    }

    if (has_negative)
    {
        for (int i = 0; i < n; i++)
        {
            points[i].y = -points[i].y;
        }
    }

    ld ans = solve(0, n - 1);
    cout << fixed << setprecision(6) << ans << '\n';

    return 0;
}