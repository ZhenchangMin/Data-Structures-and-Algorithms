#include <iostream>
#include <map>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<ll, ll> left; // l->r
    map<ll, ll> right; // r->l map是按照键自动排序的，所以left和right都是有序的

    while (n--) {
        char op;
        cin >> op;

        if (op == 'A') {
            ll l, r;
            cin >> l >> r;

            int removed = 0;
            // 在right map中查找所有右端点 >= l 的候选线段，
            // 因为如果一条线段的右端点 < l，那么它肯定在新区间的左边，不相交
            auto it = right.lower_bound(l);
            
            while (it != right.end()) {
                ll seg_l = it->second; // 候选线段的左端点
                ll seg_r = it->first; // 候选线段的右端点
                // 相交的充分必要条件：
                // 1. 候选线段的右端点 >= l (由lower_bound保证)
                // 2. 候选线段的左端点 <= r
                // 如果候选线段的左端点 > r，说明它在新区间的右边，不相交，直接break

                if (seg_l > r) break;
                
                // 执行删除操作：这个候选线段与新区间相交
                removed++;
                left.erase(seg_l); // 从left map中删除
                it = right.erase(it);  // 从right map中删除，并获取下一个迭代器
            }
            // 添加这个线段
            left[l] = r;
            right[r] = l;

            cout << removed << '\n';
        } 
        else if (op == 'B') {
            cout << left.size() << '\n';
        }
    }

    return 0;
}