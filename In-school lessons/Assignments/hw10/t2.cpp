#include <iostream>
#include <vector>
#include <climits>
using namespace std;
using ll = long long;

const ll MAX_DIST = 9e18;

struct Transition {
    int from, to;
    ll profit;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int card_count, rule_count;
    cin >> card_count >> rule_count;
    vector<Transition> transitions;
    transitions.reserve(rule_count);
    
    for (int i = 0; i < rule_count; ++i) {
        int u, v;
        ll val;
        cin >> u >> v >> val;
        transitions.push_back({u - 1, v - 1, val});
    }

    int risky_starts = 0;
    for (int start = 0; start < card_count; ++start) {
        vector<ll> max_gain(card_count, MAX_DIST);
        max_gain[start] = 0;
        bool updated;

        for (int step = 0; step < card_count - 1; ++step) {
            updated = false;
            for (const auto& t : transitions) {
                if (max_gain[t.from] != MAX_DIST && max_gain[t.from] + t.profit < max_gain[t.to]) {
                    max_gain[t.to] = max_gain[t.from] + t.profit;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        bool has_infinite_loss = false;
        for (const auto& t : transitions) {
            if (max_gain[t.from] != MAX_DIST && max_gain[t.from] + t.profit < max_gain[t.to]) {
                has_infinite_loss = true;
                break;
            }
        }

        if (has_infinite_loss) {
            risky_starts++;
        }
    }

    cout << risky_starts << endl;
    return 0;
}