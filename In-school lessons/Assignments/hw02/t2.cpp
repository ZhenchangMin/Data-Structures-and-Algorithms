#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long maxCrossingSum(vector<long long> &a, int left, int mid, int right)
{
    // 从中点向左的最大和
    long long leftSum = a[mid], sum = a[mid];
    for (int i = mid - 1; i >= left; i--)
    {
        sum += a[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    // 从中点+1 向右的最大和
    long long rightSum = a[mid + 1];
    sum = a[mid + 1];
    for (int i = mid + 2; i <= right; i++)
    {
        sum += a[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    return leftSum + rightSum;//返回最大的跨中点的值
}

long long maxSubArraySum(vector<long long> &a, int left, int right)
{
    if (left == right)
        return a[left];// base case

    long long mid = left + (right - left) / 2;

    long long leftMax = maxSubArraySum(a, left, mid);
    long long rightMax = maxSubArraySum(a, mid + 1, right);
    long long crossMax = maxCrossingSum(a, left, mid, right);

    return max({leftMax, rightMax, crossMax});
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--){
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        cout << maxSubArraySum(a, 0, n - 1) << '\n';
    }
    return 0;
}
//基本思路：要么在左半边，要么在右半边，要么跨中点，按照这样三个分下去递归，每次返回三个中的最大值，最后就可以得到整个数组的最大子数组和