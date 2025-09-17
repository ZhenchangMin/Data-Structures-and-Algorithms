#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            int minHeight = a[i];
            for (int j = i + 1; j < n; j++)
            {
                if (a[j] <= minHeight)
                {
                    count++;
                    minHeight = a[j];
                }
                else
                {
                    break;
                }
            }
        }
        cout << count << '\n';
    }
    return 0;
}