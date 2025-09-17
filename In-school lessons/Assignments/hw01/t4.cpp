#include <iostream>
#include <vector>
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
        int maxRead = 0;
        for (int i = 0; i < n; i++)
        {
            maxRead = 0;
            minHeight = a[i];
            for (int j = i + 1; j < n; j++)
            {
                minHeight = a[i];//两边更小的那一个楼房高度设为minHeight
                if (a[j] <= minHeight)
                {
                    minHeight = a[j];
                }
                if(a[j-1] > maxRead) {
                    maxRead = a[j-1];
                } 
                if(j == i + 1) {
                    count++;
                    continue;
                }//如果两楼相邻，直接加加
                else if(maxRead != a[i] && maxRead <= minHeight) {
                    count++;
                }//如果两边之间的最大值小于minHeight，加加
                else {
                    continue;
                }
            }
        }
        cout << count << '\n';
    }
    return 0;
}