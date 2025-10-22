#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

ll maxCross(vector<ll> &a, int mid, int left, int right){
    ll left_max = a[mid];
    ll current = a[mid];
    for (int idx = mid - 1; idx >= left; idx--)
    {
        current += a[idx];
        if (current > left_max)
        {
            left_max = current;
        }
    }

    ll right_max = a[mid + 1];
    current = a[mid + 1];
    for (int idx = mid + 2; idx <= right; idx++)
    {
        current += a[idx];
        if (current > right_max)
        {
            right_max = current;
        }
    }

    return left_max + right_max;
}


ll maxSub(vector<ll> &a, ll left, ll right){
    if (left >= right){
        return a[left];
    }
    ll mid = left + (right - left) / 2;
    ll l = maxSub(a, left, mid);
    ll r = maxSub(a, mid + 1, right);
    ll cross = maxCross(a, mid, left, right);
    return max({l, r, cross});
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<ll> a;
        for (int i = 0; i < n; i++){
            ll x;
            cin >> x;
            a.push_back(x);
        }
        ll result = maxSub(a, 0, n - 1);
        cout << result << '\n';
    }
    return 0;
}