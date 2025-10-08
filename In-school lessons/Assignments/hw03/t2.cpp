#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

priority_queue<int> max_heap; // max heap to store the x smallest elements, only store x elements and pop the biggest of them
priority_queue<int, vector<int>, greater<int>> min_heap; // min heap to store the rest elements
int x = 0; 

void insert(int val)
{
    // if max heap not full or val smaller than the x smallest element
    if (max_heap.size() < x || val < max_heap.top())
    {
        max_heap.push(val);
        // move the largest to min heap if max heap size exceeds x
        if (max_heap.size() > x)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
    }
    else
    {
        min_heap.push(val);
    }
}

int query()
{
    int result = max_heap.top(); // the x smallest element
    x++;

    // prepare for next query
    if (!min_heap.empty())
    {
        max_heap.push(min_heap.top());// get the x+1 smallest element from the smallest in min_heap
        min_heap.pop();
    }

    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<int> elements(m);
    for (int i = 0; i < m; i++)
    {
        cin >> elements[i];
    }

    vector<int> queries(n);
    for (int i = 0; i < n; i++)
    {
        cin >> queries[i];
    }

    int insert_ptr = 0;
    x = 1;
    for (int i = 0; i < n; i++)
    {
        while (insert_ptr < queries[i])
        {
            insert(elements[insert_ptr]);
            insert_ptr++;
        }
        // query
        cout << query() << '\n';
    }

    return 0;
}