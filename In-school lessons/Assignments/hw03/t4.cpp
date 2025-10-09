#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> min_heap;
vector<ll> a, m;

ll calculate_days(int i)
{
    ll ai = a[i];
    ll mi = m[i];
    if (mi == 1)
    {
        return (ai >= 1) ? -1 : 0; 
    }
    if (ai == 0)
        return 0;
    return (ll)(log(ai) / log(mi));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    a.resize(n+1);
    m.resize(n+1);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> m[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        ll days = calculate_days(i);
        min_heap.emplace(days, i);
    }

    while (q--)
    {
        int query;
        cin >> query;
        switch(query){
            case 1:{
                int i;
                ll k;
                cin >> i >> k;
                a[i] = k;
                ll new_days = calculate_days(i);
                min_heap.emplace(new_days, i);
                break;
            }
            case 2:{
                int i;
                ll k;
                cin >> i >> k;
                m[i] = k;
                ll new_days = calculate_days(i);
                min_heap.emplace(new_days, i);
                break;
            }
            case 3:{
                while (true)
                {
                    auto [top_days, idx] = min_heap.top();
                    ll current_days = calculate_days(idx);
                    if (top_days == current_days)
                    {
                        cout << top_days << '\n';
                        break;
                    }
                    else
                    {
                        min_heap.pop();
                        min_heap.emplace(current_days, idx);
                    }
                }
            }
        }
    }
    return 0;
}