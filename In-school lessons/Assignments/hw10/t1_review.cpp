#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, seed, p;
    if (!(cin >> n >> seed >> p)) return 0;

    const int MAXN = 2000;
    vector< bitset<MAXN> > reach(n);

    mt19937 rng(seed);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                reach[i].set(j);
            } else {
                unsigned int x = rng();
                if (p != 0 && (x % (unsigned)p == 0)) reach[i].set(j);
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (reach[i].test(k)) {
                reach[i] |= reach[k];
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i) ans += (long long)reach[i].count();
    cout << ans << '\n';
    return 0;
}