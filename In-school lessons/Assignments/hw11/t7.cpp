#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<long long> a;
	int x;
    while (cin >> x) a.push_back(x);
	if (a.empty()) {
		cout << 0;
		return 0;
	}

	long long sum = accumulate(a.begin(), a.end(), 0LL);
	if (sum % 2) {
		cout << 0;
		return 0;
	}

	long long target = sum / 2; // half of sum, which we want to find
	if (target < 0) {
		cout << 0;
		return 0;
	}

	vector<unsigned char> dp((target) + 1, 0);// dp 代表能不能凑成某个和，1是可以
	dp[0] = 1;
    // 遍历每个v
	for (long long v : a) {
		if (v > target) v = target + 1; // skip inner loop if larger than target
		for (long long s = target; s >= v; --s) {
			if (dp[(s - v)]) dp[(s)] = 1; // 如果 s-v 能凑成，那么 s 也能凑成
		}
	}

	cout << (dp[(target)] ? 1 : 0);
	return 0;
}
