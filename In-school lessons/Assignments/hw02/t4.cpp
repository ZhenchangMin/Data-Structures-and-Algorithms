#include <iostream>
#include <cmath>
using namespace std;
const double Epislon = 1e-15;
using ld = long double;
typedef struct position
{
    int x, y;
} Pos;
// 如果存在可行的圆心坐标，那么所有点到圆心的距离应该小于等于半径
bool existXofCirclePosition(Pos *points, int n, ld r)
{
    ld left = -1e18, right = 1e18; // 这个函数来求圆心的x坐标的范围，看是否存在
    for (int i = 0; i < n; ++i)
    {
        int x = points[i].x;
        int y = points[i].y;
        ld d = 2 * r * y - (ld)y * y; //(x-h)^2 + (y-r)^2 \leq r^2, 化简得到x-h=正负的sqrt(d)
        if (d < 0)
        { // 根号下不能为负
            return false;
        }
        ld sqrt_d = sqrt(d);
        ld curr_left = x - sqrt_d;
        ld curr_right = x + sqrt_d;
        left = max(left, curr_left);
        right = min(right, curr_right);
        if (left > right + Epislon)
        {
            return false;
        }
    }
    return left <= right + Epislon;
}
ld solve(Pos *points, int n)
{
    // firstly check if all points have the same sign of y, or the circle won't exist so return -1
    int sign = points[0].y > 0 ? 1 : -1;
    for (int i = 1; i < n; ++i)
    {
        if ((points[i].y > 0 ? 1 : -1) != sign)
        {
            return -1;
        }
    }

    ld left_r = 0.0;
    ld right_r = 0.0; // r取值的在一个区间内，即[left_r, right_r]
    for (int i = 0; i < n; ++i)
    {
        right_r = max(right_r, (ld)abs(points[i].y));
    }
    right_r = right_r * 2;
    while (right_r - left_r > 1e-10)
    {
        ld mid = (left_r + right_r) / 2;
        if (existXofCirclePosition(points, n, mid))
        {
            right_r = mid;
        }
        else
        {
            left_r = mid;
        }
    }
    return right_r;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Pos *points = new Pos[n];
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }
    ld ans = solve(points, n);
    cout.precision(20);
    cout << ans << '\n';
    delete[] points;
    return 0;
}
