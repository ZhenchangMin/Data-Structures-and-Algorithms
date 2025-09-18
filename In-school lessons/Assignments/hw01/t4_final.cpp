#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i];
        }
        int count = 0;
        int minHeight = a[0];
        int maxMid = 0;
        for (int i = 0; i < n; i++)
        {
            const int heightI = a[i];
            maxMid = 0;
            for (int j = i + 1; j < n; j++)
            {
                minHeight = min(heightI, a[j]); // 两边更小的那一个楼房高度设为minHeight
                if (j == i + 1)
                {
                    count++;
                    maxMid = 0;
                    continue;
                } // 如果两楼相邻，直接加加
                else
                {
                    maxMid = max(maxMid, a[j - 1]);
                    if (maxMid <= minHeight)
                    {
                        count++;
                    } // 如果两边之间的最大值<=minHeight，加加
                    else if (maxMid > minHeight && minHeight == heightI)//如果已经比现在i的楼房高了，直接跳出，节省时间
                    {
                        break;
                    }
                }
            }
        }
        cout << count << '\n';
    }
    return 0;
}