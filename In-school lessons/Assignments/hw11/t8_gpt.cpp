#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s1, s2;
	if (!std::getline(std::cin, s1)) return 0;
	std::getline(std::cin, s2);

	int n = static_cast<int>(s1.size());
	int m = static_cast<int>(s2.size());

	std::vector<int> prev(m + 1), curr(m + 1);
	for (int j = 0; j <= m; ++j) prev[j] = j;

	for (int i = 1; i <= n; ++i) {
		curr[0] = i;
		for (int j = 1; j <= m; ++j) {
			int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
			int del = prev[j] + 1;
			int ins = curr[j - 1] + 1;
			int rep = prev[j - 1] + cost;
			curr[j] = std::min({del, ins, rep});
		}
		std::swap(prev, curr);
	}

	std::cout << prev[m] << '\n';
	return 0;
}
