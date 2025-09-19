#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        deque<int> numbers;
        for (int i = 0; i < n; i++) {
            int num;
            cin >> num;
            numbers.push_back(num);
        }
        vector<int> ops(q);
        for (int i = 0; i < q; i++) {
            cin >> ops[i];
        }
        for (int k : ops) {
            deque<int> temp;//把前k个要处理的元素取出来
            for (int i = 0; i < k; i++) {
                temp.push_back(numbers.front());
                numbers.pop_front();
            }
            deque<int> evenIndices;
            for (int i = 1; i <= k; i++) {
                if (i % 2 == 0) { 
                    evenIndices.push_back(temp[i-1]);
                }
            }
            deque<int> reversedEven;
            while (!evenIndices.empty()) {
                reversedEven.push_back(evenIndices.back());
                evenIndices.pop_back();
            }
            int idx = 0;
            for (int i = 1; i <= k; ++i) {
                if (i % 2 == 0) {
                    numbers.push_front(reversedEven.back());
                    reversedEven.pop_back();
                }
            }
        }
        
        while (!numbers.empty()) {
            cout << numbers.front() << " ";
            numbers.pop_front();
        }
        cout << '\n';
    }
    return 0;
}