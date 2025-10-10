#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    long long value;
    int index;
    int left, right;
    bool removed;
    int version; // 添加版本号来检测是否过时

    bool operator<(const Node &other) const
    {
        if (value != other.value)
        {
            return value > other.value;
        }
        return index > other.index;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Node> nodes(n);
    priority_queue<Node> queue;

    // initialize
    for (int i = 0; i < n; i++)
    {
        cin >> nodes[i].value;
        nodes[i].index = i;
        nodes[i].left = i - 1;
        nodes[i].right = i + 1;
        nodes[i].removed = false;
        nodes[i].version = 0;
        queue.push(nodes[i]);
    }

    // boundary cases
    nodes[0].left = -1;
    nodes[n - 1].right = -1;

    vector<int> current_version(n, 0);

    // remove process
    for (int i = 0; i < k; i++)
    {
        // find the next valid min node
        Node current;
        while (true)
        {
            current = queue.top();
            queue.pop();
            int idx = current.index;
            if (!nodes[idx].removed && current.version == current_version[idx])
            {
                break;
            }
        }

        int crt_index = current.index;

        // update the value of adjacent nodes
        if (nodes[crt_index].left != -1)
        {
            int left_idx = nodes[crt_index].left;
            nodes[left_idx].value += nodes[crt_index].value;
            current_version[left_idx]++;
            nodes[left_idx].version = current_version[left_idx];
            queue.push(nodes[left_idx]);
        }
        if (nodes[crt_index].right != -1)
        {
            int right_idx = nodes[crt_index].right;
            nodes[right_idx].value += nodes[crt_index].value;
            current_version[right_idx]++; 
            nodes[right_idx].version = current_version[right_idx];
            queue.push(nodes[right_idx]);
        }

        if (nodes[crt_index].left != -1)
        {
            nodes[nodes[crt_index].left].right = nodes[crt_index].right;
        }
        if (nodes[crt_index].right != -1)
        {
            nodes[nodes[crt_index].right].left = nodes[crt_index].left;
        }

        nodes[crt_index].removed = true;
    }

    for (int i = 0; i < n; i++)
    {
        if (!nodes[i].removed)
        {
            cout << nodes[i].value << " ";
        }
    }
    cout << '\n';

    return 0;
}