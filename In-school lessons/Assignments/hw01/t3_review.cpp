#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void execute(deque<int> &a, int k)
{
    deque<int> temp;
    for (int i = 0; i < k; i++)
    {
        if (i % 2 == 1)
        {
            temp.push_back(a[i]);
        }
    }
    for (int i = 0; i < k; i++)
    {
        a.pop_front();
    }
    for (int i = 0; i < temp.size(); i++)
    {
        a.push_front(temp[i]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n, q;
        cin >> n >> q;
        deque<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        while (q--)
        {
            int k;
            cin >> k;
            execute(a, k);
        }
        for (int i = 0; i < a.size(); i++)
        {
            cout << a[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}