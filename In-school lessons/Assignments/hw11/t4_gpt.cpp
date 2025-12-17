#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long n, m, k, w;
        cin >> n >> m >> k >> w;
        vector<long long> req(n), forb(m);
        for (int i = 0; i < n; ++i) cin >> req[i];
        for (int i = 0; i < m; ++i) cin >> forb[i];

        sort(req.begin(), req.end());
        sort(forb.begin(), forb.end());

        bool impossible = false;
        {
            int i = 0, j = 0;
            while (i < n && j < m) {
                if (req[i] == forb[j]) { impossible = true; break; }
                if (req[i] < forb[j]) ++i; else ++j;
            }
        }

        if (impossible) {
            cout << -1 << '\n';
            continue;
        }

        vector<pair<long long, long long>> ranges;
        if (m == 0) {
            ranges.emplace_back(1LL, w);
        } else {
            if (forb[0] > 1) ranges.emplace_back(1LL, forb[0] - 1);
            for (int i = 0; i + 1 < m; ++i) {
                long long L = forb[i] + 1;
                long long R = forb[i + 1] - 1;
                if (L <= R) ranges.emplace_back(L, R);
            }
            if (forb[m - 1] < w) ranges.emplace_back(forb[m - 1] + 1, w);
        }

        long long totalCourses = 0;
        int p = 0;

        for (auto &[L, R] : ranges) {
            while (p < n && req[p] < L) ++p;
            
            vector<long long> pts;
            int q = p;
            while (q < n && req[q] <= R) {
                pts.push_back(req[q]);
                ++q;
            }
            
            if (pts.empty()) {
                p = q;
                continue;
            }
            
            long long len = R - L + 1;
            long long maxCourses = len / k;
            
            long long minCourses = 0;
            {
                size_t idx = 0;
                while (idx < pts.size()) {
                    ++minCourses;
                    long long endCover = pts[idx] + k - 1;
                    while (idx < pts.size() && pts[idx] <= endCover) ++idx;
                }
            }
            
            if (minCourses > maxCourses) {
                impossible = true;
                break;
            }
            
            auto canCover = [&](long long c) -> bool {
                size_t i = 0;
                long long used = 0;
                while (i < pts.size()) {
                    ++used;
                    if (used > c) return false;

                    long long minStart = L + (used - 1) * k;
                    long long maxStart = R - (c - used + 1) * k + 1;
                    if (minStart > maxStart) return false;
                    while (i < pts.size() && maxStart + k - 1 < pts[i]) {
                        ++used;
                        if (used > c) return false;
                        minStart = L + (used - 1) * k;
                        maxStart = R - (c - used + 1) * k + 1;
                        if (minStart > maxStart) return false;
                    }

                    if (pts[i] < minStart) return false;

                    long long sLow = max(minStart, pts[i] - k + 1);
                    long long sHigh = min(maxStart, pts[i]);
                    if (sLow > sHigh) return false;

                    long long s = sHigh;
                    long long endPos = s + k - 1;
                    while (i < pts.size() && pts[i] <= endPos) ++i;
                }
                return true;
            };
            
            long long lo = minCourses, hi = maxCourses, best = -1;
            while (lo <= hi) {
                long long mid = (lo + hi) / 2;
                if (canCover(mid)) {
                    best = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            
            if (best < 0) {
                impossible = true;
                break;
            }
            
            totalCourses += best;
            p = q;
        }

        if (impossible) cout << -1 << '\n';
        else cout << totalCourses * k << '\n';
    }

    return 0;
}