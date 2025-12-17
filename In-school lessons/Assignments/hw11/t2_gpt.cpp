#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static bool feasible(ll S, ll n, ll M) {
	if (S == 0) return M == 0;
	if (M == 0) return false;

	int lowBitM = __builtin_ctzll(M);
	int v2S = __builtin_ctzll(S);
	if (lowBitM > v2S) return false;

	ll rem = S;
	for (int k = 62; k >= 0; --k) {
		if ((M >> k) & 1LL) {
			ll unit = 1LL << k;
			ll can = min(n, rem / unit);
			rem -= can * unit;
			if (rem == 0) break;
		}
	}
	return rem == 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	if (!(cin >> T)) return 0;
	while (T--) {
		ll n;
		cin >> n;
		ll S = 0;
		for (ll i = 0; i < n; ++i) {
			ll a;
			cin >> a;
			S += a;
		}
		if (S == 0) {
			cout << 0 << "\n";
			continue;
		}
		ll lo = 0, hi = (1LL<<62) - 1; // 充足的上界
		ll ans = -1;
		while (lo <= hi) {
			ll mid = (lo + hi) >> 1;
			if (feasible(S, n, mid)) {
				ans = mid;
				hi = mid - 1;
			} else {
				lo = mid + 1;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
