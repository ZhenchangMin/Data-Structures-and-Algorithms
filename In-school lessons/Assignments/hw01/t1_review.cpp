#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    deque<string> planes;
    while (n--)
    {
        int op;
        cin >> op;
        switch (op)
        {
        case 1:
        {
            string number;
            cin >> number;// 必须先把number读进来，不然会乱
            if (planes.size() < m)
            {
                planes.push_back(number);
            }
            else
            {
                cout << "full" << '\n';
            }
            break;
        }
        case 2:
        {
            if (planes.empty())
            {
                cout << "empty" << '\n';
            }
            else
            {
                string fly = planes[0];
                planes.pop_front();
                cout << fly << '\n';
            }
            break;
        }
        case 3:
        {
            cout << planes.size() << '\n';
            break;
        }
        }
    }
    return 0;
}