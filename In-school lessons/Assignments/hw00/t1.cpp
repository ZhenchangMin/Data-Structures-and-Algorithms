#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);//这两行代码用来提升输入输出速度
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    long long int result;
    for (int i = 0; i < n; i++)
    {
        result += arr[i];
        std::cout << result - 1 << '\n';//'\n'比endl快，因为不需要刷新缓冲区
    }
    return 0;
}