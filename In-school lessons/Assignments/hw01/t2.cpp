#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void execute(string commands[], int n, int k, int &size)
{
    for (int i = 0; i < size; i++)
    {
        if (commands[i][0] == 'e')
        {
            cout << commands[i].substr(5);
        }
        else if (commands[i][0] == 'c' && size < k) // 重要：只有在当前命令数小于k时才执行复制操作
        {
            int m;
            istringstream(commands[i].substr(3)) >> m; // 把字符串转换为整数
            for (int j = 0; j < m; j++)
            {
                if (size < k) // 重要：复制命令时，检查是否超出数组边界，避免越界访问
                {
                    commands[size] = commands[j];
                    size++;
                }
            }
        }
    }
    return;
}

int main()
{
    int n, k;
    cin >> n >> k;
    string commands[k];
    int size = n;
    for (int i = 0; i < n; i++)
    {
        string type, parameter, command;
        cin >> type >> parameter;
        command = type + " " + parameter;
        commands[i] = command;
    }
    execute(commands, n, k, size);
    return 0;
}
