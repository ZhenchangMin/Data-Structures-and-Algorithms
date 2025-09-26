// 圆心的坐标是(h, r)，半径为r，
// 如果存在可行的圆心坐标，那么所有点到圆心的距离应该小于等于半径
// 二分半径，对每一个半径检查是否存在合理的h使得圆心存在
// 如果存在，那么半径就是可行的，就再往更小的方向二分看看行不行
// 如果不存在，那么说明半径小了，因为半径越小越有可能存在这样的圆心，所以还需要往更大的方向二分
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
using ld = long double;
typedef struct position
{
    int x, y;
} Pos;
bool existXofCirclePosition(Pos *points, int n, ld r)
{
    ld left = -1e18, right = 1e18; // 这个函数来求圆心的x坐标的范围，看是否存在合理的h使得圆心存在
    for (int i = 0; i < n; ++i)
    {
        int x = points[i].x;
        int y = points[i].y;
        ld d = 2 * r * y - (ld)y * y; //(x-h)^2 + (y-r)^2 \leq r^2, 化简得到x-h=正负的sqrt(d)
        if (d < 0)
        { // 根号下不能为负
            return false;
        }
        if (fabs(d) == 0)
        {
            left = max(left, (ld)x);
            right = min(right, (ld)x);
        }
        else
        {
            ld sqrt_d = sqrt(d);
            ld curr_left = x - sqrt_d;
            ld curr_right = x + sqrt_d;
            left = max(left, curr_left);
            right = min(right, curr_right);
        }

        if (left > right)
        {
            return false;
        }
    }
    return true;
}
ld solve(Pos *points, int n)
{
    // firstly check if all points have the same sign of y, or the circle won't exist so return -1
    bool has_positive = false, has_negative = false;

    for (int i = 0; i < n; i++)
    {
        if (points[i].y > 0)
            has_positive = true;
        if (points[i].y < 0)
            has_negative = true;
    }

    if (has_positive && has_negative)
    {
        return -1.0;
    }

    if (has_negative)
    {
        for (int i = 0; i < n; i++)
        {
            points[i].y = -points[i].y;
        }
    }

    ld max_y = 0.0;
    ld max_abs_y = 0.0;

    for (int i = 0; i < n; i++)
    {
        max_y = max(max_y, (ld)points[i].y);
        max_abs_y = max(max_abs_y, (ld)abs(points[i].y));
    }

    ld left_r = max_y / 2.0;

    int min_x = points[0].x, max_x = points[0].x;
    for (int i = 1; i < n; i++)

    {
        min_x = min(min_x, points[i].x);
        max_x = max(max_x, points[i].x);
    }
    ld right_r = 1e18;// 有可能x很接近但是y很大，因此r的上界要设置的大一些

    int N = 100;
    while (N--)
    {
        ld mid = (left_r + right_r) / 2.0;
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
    cout << fixed << setprecision(6);
    cout << ans << '\n';
    delete[] points;
    return 0;
}
