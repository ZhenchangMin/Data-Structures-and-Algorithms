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
        int maxRead = 0;
        for (int i = 0; i < n; i++)
        {
            maxRead = a[i];
            for (int j = i + 1; j < n; j++)
            {
                if(j == i + 1) {
                    count++;
                    continue;
                }
                else if(a[j] >= maxRead) {
                    count++;
                    maxRead = a[j];
                } else {
                    continue;
                }
            }
        }
        cout << count << '\n';
    }
    return 0;
}