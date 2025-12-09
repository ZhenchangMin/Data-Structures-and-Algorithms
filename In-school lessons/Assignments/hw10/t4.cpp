#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int NSTATE = 16;
const LL INF = (LL)4e18;

struct Op { int mask; LL cost; };
Op ops[9];
LL distMat[NSTATE][NSTATE];
LL dp_all[(1<<16)][16];
LL ansMask[1<<16];

inline int encodeGrid(const string &r0, const string &r1) {
    int x = ((r0[0]-'0')<<3)|((r0[1]-'0')<<2)|((r1[0]-'0')<<1)|(r1[1]-'0');
    return x ^ 0b1111;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    LL a0,a1,a2,a3;
    cin >> T >> a0 >> a1 >> a2 >> a3;

    ops[0] = {0b1000, a0};
    ops[1] = {0b0100, a0};
    ops[2] = {0b0010, a0};
    ops[3] = {0b0001, a0};
    ops[4] = {0b1100, a1};
    ops[5] = {0b0011, a1};
    ops[6] = {0b1010, a2};
    ops[7] = {0b0101, a2};
    ops[8] = {0b1111, a3};

    for (int i = 0; i < NSTATE; ++i)
        for (int j = 0; j < NSTATE; ++j)
            distMat[i][j] = (i==j?0:INF);

    for (int u = 0; u < NSTATE; ++u)
        for (int i = 0; i < 9; ++i) {
            int v = u ^ ops[i].mask;
            if (ops[i].cost < distMat[u][v]) distMat[u][v] = ops[i].cost;
        }

    for (int k = 0; k < NSTATE; ++k)
        for (int i = 0; i < NSTATE; ++i)
            if (distMat[i][k] < INF)
                for (int j = 0; j < NSTATE; ++j)
                    if (distMat[k][j] < INF)
                        if (distMat[i][k] + distMat[k][j] < distMat[i][j])
                            distMat[i][j] = distMat[i][k] + distMat[k][j];

    const int FULL = 1<<NSTATE;
    for (int mask = 0; mask < FULL; ++mask)
        for (int v = 0; v < NSTATE; ++v)
            dp_all[mask][v] = INF;

    for (int v = 0; v < NSTATE; ++v)
        if (distMat[0][v] < INF) dp_all[1<<v][v] = distMat[0][v];

    for (int mask = 1; mask < FULL; ++mask)
        for (int last = 0; last < NSTATE; ++last) {
            if (!(mask & (1<<last))) continue;
            LL cur = dp_all[mask][last];
            if (cur >= INF) continue;
            for (int nxt = 0; nxt < NSTATE; ++nxt) {
                if (mask & (1<<nxt)) continue;
                LL w = distMat[last][nxt];
                if (w >= INF) continue;
                int nm = mask | (1<<nxt);
                LL cand = cur + w;
                if (cand < dp_all[nm][nxt]) dp_all[nm][nxt] = cand;
            }
        }

    ansMask[0] = 0;
    for (int mask = 1; mask < FULL; ++mask) {
        LL best = INF;
        for (int v = 0; v < NSTATE; ++v)
            if (mask & (1<<v))
                if (dp_all[mask][v] < best) best = dp_all[mask][v];
        ansMask[mask] = (best >= INF ? -1 : best);
    }

    while (T--) {
        int m;
        cin >> m;
        int mask = 0;
        string s0, s1;
        for (int i = 0; i < m; ++i) {
            cin >> s0 >> s1;
            int st = encodeGrid(s0, s1);
            mask |= (1<<st);
        }
        cout << ansMask[mask] << '\n';
    }

    return 0;
}
