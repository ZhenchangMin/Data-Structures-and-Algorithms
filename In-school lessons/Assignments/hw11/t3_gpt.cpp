#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	if (!(cin >> T)) return 0;
	while (T--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) cin >> a[i];

		vector<int> st;
		int ans = 0;
		for (int x : a) {
			while (!st.empty() && st.back() > x) st.pop_back();
			if (x == 0) continue;
			if (st.empty() || st.back() < x) {
				st.push_back(x);
				++ans;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
