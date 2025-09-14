/*这个题是用来教你使用交互题的。请注意刷新缓冲区，否则将会出错。

输入格式
首先是一个不大于 10 的数字n，代表复读的次数。接下来每次你需要输入一个int类型的整数a，你只需要在每次输入之后直接输出它并且换行即可。
*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int a;
        cin >> a;
        cout << a << endl;
    }
    return 0;
}