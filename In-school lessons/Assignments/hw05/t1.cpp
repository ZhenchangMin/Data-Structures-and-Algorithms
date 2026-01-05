#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
using ll = long long;

struct Node
{
    ll val;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
};

ll dfs(Node *node, ll k)
{
    if (node == nullptr)
        return 0;

    ll left_sum = dfs(node->left, k);
    ll right_sum = dfs(node->right, k);
    ll total_sum = left_sum + right_sum + node->val;

    if (total_sum == k)
    {
        return 0;
    }

    return total_sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        ll n, k;
        cin >> n >> k;

        vector<Node *> nodes(n + 1);
        for (int i = 1; i <= n; i++)
        {
            nodes[i] = new Node();
        }

        for (int i = 1; i <= n; i++)
        {
            ll left_index, right_index;
            cin >> left_index >> right_index;
            if (left_index != 0)
            {
                nodes[i]->left = nodes[left_index];
                nodes[left_index]->parent = nodes[i];
            }
            if (right_index != 0)
            {
                nodes[i]->right = nodes[right_index];
                nodes[right_index]->parent = nodes[i];
            }
        }

        Node *root = nodes[1];// find the root
        for (int i = 1; i <= n; i++)
        {
            if (nodes[i]->parent == nullptr)
            {
                root = nodes[i];
                break;
            }
        }

        ll total_sum = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> nodes[i]->val;
            total_sum += nodes[i]->val;
        }

        if (total_sum % k != 0)
        {
            cout << "NO\n";
        }
        else
        {
            if (dfs(root, k) == 0)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
    return 0;
}