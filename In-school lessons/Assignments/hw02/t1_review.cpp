#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

void merge(vector<int> &a, int left, int mid, int right, ll &ans)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k++] = L[i++];
        }
        else
        {
            ans += n1 - i;//这个i大于他，由于是升序，后面的肯定也大于他
            a[k++] = R[j++];
        }
    }

    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
}

void mergeSort(vector<int> &a, int left, int right, ll &ans)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid, ans);
        mergeSort(a, mid + 1, right, ans);
        merge(a, left, mid, right, ans);     // 合并并计算逆序数
    }
}

int main(){
    int T;
    cin >> T;
    while (T--){
        int n;
        cin >> n;
        vector<int> a;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            a.push_back(x);
        }
        ll ans = 0;
        mergeSort(a, 0, n - 1, ans);
        cout << ans <<'\n';
    }
    return 0;
}