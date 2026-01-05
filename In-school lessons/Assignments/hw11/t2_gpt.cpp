#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	if (!(cin >> T)) return 0;
	while (T--) {
		long long n;
		cin >> n;
		unsigned long long S = 0;
		for (long long i = 0; i < n; ++i) {
			unsigned long long a;
			cin >> a;
			S += a;
		}

		if (S == 0) {
			cout << 0 << "\n";
			continue;
		}

		unsigned long long rem = S;
		unsigned long long M = 0;
		for (int k = 62; k >= 0; --k) {
			unsigned long long unit = 1ULL << k;
			__int128 cap_lower = (__int128)n * (unit - 1ULL);
			if ((__int128)rem > cap_lower) {
				M |= unit;
				unsigned long long can = (unsigned long long)min<unsigned long long>((unsigned long long)n, rem / unit);
				rem -= can * unit;
			}
		}
		cout << (unsigned long long)M << "\n";
	}
	return 0;
}
