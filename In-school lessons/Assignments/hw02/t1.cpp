//注意用long long！否则会溢出，导致错误
#include <iostream>
#include <vector>

using namespace std;

long long mergeSort(vector<int> &a, vector<int> &temp, int left, int right)
{
    if (left >= right)
        return 0;

    long long mid = left + (right - left) / 2;
    long long count = mergeSort(a, temp, left, mid) + mergeSort(a, temp, mid + 1, right);

    // 左边的逆序数加上右边的，但是还有跨左右的，因为分两边了就可以先排序，不影响逆序数的计算，这样大的数列的逆序数就可以分成两半，只要最后再合并的时候再计算一下跨左右的逆序数就可以了
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            count += mid - i + 1;//由于左右都已经是有序的，所以如果这时候a[i]比较大，那左半边剩下的数也肯定比a[j]大，因为我们更新了j所以这个值要算上，而不是简单的让count++
            temp[k++] = a[j++];
        }
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= right)
        temp[k++] = a[j++];

    copy(temp.begin() + left, temp.begin() + right + 1, a.begin() + left);
    return count;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
        long long count = 0;
        vector<int> temp(n);
        count = mergeSort(a, temp, 0, n - 1);
        cout << count << '\n';
    }
    return 0;
}
// 总体的思想是每次只能交换绝对值相差为1的两个数字，能达到升序排列最少的交换次数会等于逆序数。
// 为什么？
// 因为每次交换都能减少一个逆序数，所以最少的交换次数会等于逆序数。每次相邻交换只能消除一个逆序对。
// 对于任何排列，通过相邻交换排序的最小次数等于该排列的逆序数。