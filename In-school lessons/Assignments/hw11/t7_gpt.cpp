#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

static inline void shift_or(vector<unsigned long long>& bits, int shift, unsigned long long lastMask) {
    if (shift <= 0) return;
    int wordShift = shift / 64;
    int bitShift  = shift % 64;
    const int n = (int)bits.size();

    vector<ull> moved(n, 0ULL);
    for (int i = n - 1; i >= 0; --i) {
        if (bits[i] == 0ULL) continue;
        int j = i + wordShift;
        if (j >= n) continue;
        moved[j] |= (bits[i] << bitShift);
        if (bitShift && j + 1 < n) {
            moved[j + 1] |= (bits[i] >> (64 - bitShift));
        }
    }
    for (int i = 0; i < n; ++i) bits[i] |= moved[i];
    bits.back() &= lastMask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a;
    int x;
    while (cin >> x) a.push_back(x);

    if (a.empty()) {
        cout << 0;
        return 0;
    }

    ull sum = accumulate(a.begin(), a.end(), 0LL);
    if (sum % 2LL) {
        cout << 0;
        return 0;
    }
    int target = (int)(sum / 2LL);

    for (int v : a) if (v > target) { cout << 0; return 0; }

    int totalBits = target + 1;
    int words = (totalBits + 63) / 64;
    vector<ull> bits(words, 0ULL);
    bits[0] = 1ULL;

    unsigned lastMask;
    int lastUsed = totalBits % 64;
    ull mask = (lastUsed == 0) ? ~0ULL : ((1ULL << lastUsed) - 1ULL);

    for (int v : a) {
        shift_or(bits, v, mask);
        if ((bits[target / 64] >> (target % 64)) & 1ULL) {
            cout << 1;
            return 0;
        }
    }

    cout << (((bits[target / 64] >> (target % 64)) & 1ULL) ? 1 : 0);
    return 0;
}
