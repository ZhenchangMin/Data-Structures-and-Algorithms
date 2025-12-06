#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2001;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, seed, p;
    cin >> n >> seed >> p;

    mt19937 rng(seed);
    // generate adjacency matrix
    bitset<MAXN> adj[MAXN]; // bitset<2001> means that we can store up to 2001 bits

    for (int i = 0; i < n; ++i) {
        adj[i].set(i); // to set the i-th bit of adj[i] to 1, that means i can reach i
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            uint32_t rand_num = rng();
            if (rand_num % p == 0) {
                adj[i].set(j); // to set the j-th bit of adj[i] to 1, that means i can reach j
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (adj[i].test(k)) { // if the k-th bit of adj[i] is 1, means i can reach k
                adj[i] |= adj[k]; // if i can reach k, and k can reach some other nodes, then i can also reach those nodes
                // so we do a bitwise OR operation between adj[i] and adj[k]
            }
        }
    }

    int total = 0;
    for (int i = 0; i < n; ++i) {
        total += adj[i].count(); // count the number of bits that are set to 1, that means the number of nodes that i can reach
    }

    cout << total << "\n";
    return 0;
}
