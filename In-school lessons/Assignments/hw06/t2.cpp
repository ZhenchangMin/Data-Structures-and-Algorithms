#include <iostream>
#include <unordered_map>
using namespace std;
using ll = unsigned long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    unordered_map<ll, int> countX;

    for (int i = 0; i < n; i++) {
        ll x, vx;
        cin >> x >> vx;
        ll product = x * vx;
        countX[product]++;
    }

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ll y, vy;
        cin >> y >> vy;
        ll product = y * vy;
        if (countX.find(product) != countX.end() && product != 0) {
            ans += countX[product];
        }
    }

    cout << ans << '\n';

    return 0;
}